
#include <bur/plctypes.h>

#define TRUE 1
#define FALSE 0

#ifdef __cplusplus
	extern "C"
	{
#endif
#include "TrkMst.h"
#ifdef __cplusplus
	};
#endif

plcbit CheckValidity(char* selectedElem){
	char buf[2];
	//Get a substring of the first 3 characters
	brdkStrSubStr(&buf,selectedElem,0,3);
	//Look at the start of the selectedID, if it starts with #ID then we know a shuttle has been clicked
	if(0 == brsstrcmp(&buf,&"#ID")){
		return TRUE;
	}
	else{
		return FALSE;
	}
}
USINT GetIndex(char* selectedElem){
	char buf[3];
	brdkStrSubStr(&buf,selectedElem,3,brdkStrLen(selectedElem) - 3);
	return (USINT)brdkStrAToUdint(&buf,BRDK_STR_CONVERT_DECIMAL);
}
/* Function block for handling a shuttle control provided from the paper element's selected element ID. Must be paired with the tmCore FB */
void tmShuttleControl(struct tmShuttleControl* inst)
{
	if(inst->Valid){
		inst->ShInfo = inst->Internal.Fbs.ShGetInfo.ShuttleInfo;
	}
	switch (inst->Internal.State){
		case tmSH_CONTROL_OFF:
			//******************************************************************************** Off state
			if(inst->Enable){
				if(inst->Handle == 0){
					inst->Error = TRUE;
					inst->ErrorID = tmSH_CONTROL_ERR_INVALID_HANDLE;
					
					inst->Internal.State = tmSH_CONTROL_ERROR;
				}
				else{
					inst->Internal.CoreInt = (tmCoreInternalTyp*)inst->Handle;
					if(inst->Internal.CoreInt->TypeID != tmCORE_CORE_TYPE_ID){
						inst->Error = TRUE;
						inst->ErrorID = tmSH_CONTROL_ERR_INVALID_HANDLE;
						
						inst->Internal.State = tmSH_CONTROL_ERROR;
					}
					else{
						inst->Active = TRUE;
						
						inst->Internal.State = tmSH_CONTROL_INIT;
					}
				}
			}
			break;
		case tmSH_CONTROL_INIT:
			//******************************************************************************** Init state
			if(CheckValidity(&inst->SelectedElem)){	//Checking for the validity of the selected element format
				inst->Internal.Idx = GetIndex(&inst->SelectedElem);	//Pulling the index from the string
				if(inst->Internal.CoreInt->Axes[inst->Internal.Idx].Present){ //Verifying that index has a valid access in it
					inst->ErrorID = tmSH_CONTROL_ERR_OK;
					inst->Valid = TRUE;
					inst->Internal.CurrentAxis = inst->Internal.CoreInt->Axes[inst->Internal.Idx].Axis;
					
					inst->Internal.Fbs.ShGetInfo.Axis = &inst->Internal.CurrentAxis;
					inst->Internal.Fbs.ShGetInfo.Enable = TRUE;
					
					inst->Internal.State = tmSH_CONTROL_IDLE;
				}
				else{
					inst->ErrorID = tmSH_CONTROL_WARN_SH_NOT_AVAIL;
				}
			}
			else{
				inst->ErrorID = tmSH_CONTROL_WARN_NO_ELEM_FND;
			}
        	
			break;
		case tmSH_CONTROL_IDLE:
			//******************************************************************************** Get Shuttle state
			//Need to check for if the selected element has changed
			inst->Internal.LastIdx = inst->Internal.Idx;
			if(CheckValidity(&inst->SelectedElem)){
				inst->Internal.Idx = GetIndex(&inst->SelectedElem);
			
				if(inst->Internal.Idx != inst->Internal.LastIdx){
					//We've changed indecies need to head back to init to reset the sh status
					inst->Valid = FALSE;
					inst->Internal.Fbs.ShGetInfo.Enable = FALSE;
			
					inst->Internal.State = tmSH_CONTROL_INIT;
				}
				else{
					//Here we can start parsing commands
					if(inst->ElasticMoveAbs){
						//Setup the elastic move absolute block and execute it
						inst->Internal.Fbs.ElMoveAbs.Axis = &inst->Internal.CurrentAxis;
						inst->Internal.Fbs.ElMoveAbs.Position = inst->Parameters->Position;
						inst->Internal.Fbs.ElMoveAbs.Velocity = inst->Parameters->Vel;
						inst->Internal.Fbs.ElMoveAbs.Acceleration = inst->Parameters->Accel;
						inst->Internal.Fbs.ElMoveAbs.Deceleration = inst->Parameters->Decel;
				
						inst->Internal.Fbs.ElMoveAbs.Execute = TRUE;
			
						inst->Internal.State = tmSH_CONTROL_EL_MOVE_ABS;
					}
				}
			
			}
			else{//We've received an invalid selection, need to reset the flags and Sh Status
				inst->Valid = FALSE;
				inst->Internal.Fbs.ShGetInfo.Enable = FALSE;
			
				inst->Internal.State = tmSH_CONTROL_INIT;
			}
			
			
			break;
		case tmSH_CONTROL_EL_MOVE_ABS:
			if(inst->Internal.Fbs.ElMoveAbs.Error){
				inst->Error = TRUE;
				inst->ErrorID = tmSH_CONTROL_ERR_EL_MOVE;
				
				inst->Internal.State = tmSH_CONTROL_ERROR;
			}
			else if(inst->Internal.Fbs.ElMoveAbs.Active){
				inst->MovementActive = TRUE;
			}
			else if(inst->Internal.Fbs.ElMoveAbs.Done){
				inst->Internal.Fbs.ElMoveAbs.Execute = FALSE;
				inst->MovementActive = FALSE;
				inst->MovementDone = TRUE;
				
				inst->Internal.State = tmSH_CONTROL_MOVE_DONE;
			}
			break;
		case tmSH_CONTROL_MOVE_DONE:
			if(!inst->ElasticMoveAbs){
				inst->MovementDone = FALSE;
				
				inst->Internal.State = tmSH_CONTROL_IDLE;
			}
		case tmSH_CONTROL_ERROR:
			
			break;
	}
	//FB calls
	
	MC_BR_ShReadInfo_AcpTrak(&inst->Internal.Fbs.ShGetInfo);
	MC_BR_ElasticMoveAbs_AcpTrak(&inst->Internal.Fbs.ElMoveAbs);
}

