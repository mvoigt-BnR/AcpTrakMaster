
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
//Verify that the two string lengths do not exceed a length
plcbit CheckStrLen(char* dest,char* source,UDINT length){
	if(brdkStrLen(dest) + brdkStrLen(source) >= length){
		return FALSE;
	}
	else{
		return TRUE;
	}
}
//This function loops through the assembly monitor data and builds a SVG string + SVG Transform. Will return 0 if succesful
//Will monitor to make sure the string lengths are not exceeded
DINT BuildStrings(struct McAcpTrakAssemblyMonData* mon,char* svgContent,char* svgTransform,struct tmCoreViewBoxCfgTyp* viewBox){
	USINT i;
	USINT transCounter;
	transCounter = 0;
	char tmp[150];
	brsmemset(svgContent,0,sizeof(svgContent));
	brsmemset(svgTransform,0,sizeof(svgTransform));
	
	snprintf2(tmp,150,"<svg viewBox=\"%f %f %f %f\">",
		viewBox->MinX,
		viewBox->MinY,
		viewBox->Width,
		viewBox->Height);
	if(CheckStrLen(svgContent,&tmp,tmCORE_MAX_STR_LEN)){
		brsstrcat(svgContent,&tmp);
	}
	else 
		return tmCORE_ERR_STR_LEN_EXCEEDED;
	brsstrcat(svgTransform,&"[");
	
	for (i = 0; i < tmMAX_SHUTTLE_COUNT; i++){
		if(mon->Shuttle[i].Available){
			brsmemset(&tmp,0,sizeof(tmp));
		
			LREAL width;
			LREAL length;
			LREAL shCenterX;
			LREAL shCenterY;
			
			width = mon->Shuttle[i].Width / 1000.0;
			length = (mon->Shuttle[i].ExtentToBack + mon->Shuttle[i].ExtentToFront)/ 1000.0;
			shCenterX = mon->Shuttle[i].Position.X / 1000.0 - mon->Shuttle[i].ExtentToBack / 1000.0;
			shCenterY = -(mon->Shuttle[i].Position.Y / 1000.0 + width / 2.0);
	
			snprintf2(tmp,150,"<g id=\"Shuttle%d\">",mon->Shuttle[i].Index);
			if(CheckStrLen(svgContent,&tmp,tmCORE_MAX_STR_LEN)){
				brsstrcat(svgContent,&tmp);
			}
			else 
				return tmCORE_ERR_STR_LEN_EXCEEDED;
			
	
			snprintf2(tmp,150,"<polygon id=\"sh%d\" points=\"0,0 %0f,0 , %f,%f %f,%f 0,%f\" style=\"fill:rgb(0,255,0);\"/>",
				mon->Shuttle[i].Index,	//polygon index
				(length-width/2.0),//p1.x
				length,	//p1.y
				width/2.0, //p2.x
				(length-width/2.0),//p2.y
				width,//p2.x
				width); //p3.y
			if(CheckStrLen(svgContent,&tmp,tmCORE_MAX_STR_LEN)){
				brsstrcat(svgContent,&tmp);
			}
			else 
				return tmCORE_ERR_STR_LEN_EXCEEDED;
	
			snprintf2(tmp,150,"<text x=\"%f\" y=\"%f\" font-weight=\"bold\" font-size=\"0.035px\">%d</text>",
				mon->Shuttle[i].ExtentToBack / 2000.0,
				width * 3.0 / 4.0,
				mon->Shuttle[i].Index);
			if(CheckStrLen(svgContent,&tmp,tmCORE_MAX_STR_LEN)){
				brsstrcat(svgContent,&tmp);
			}
			else 
				return tmCORE_ERR_STR_LEN_EXCEEDED;
	
			
			//Create an invisible bounding rectangle to handle the click event. "Invisible" by using the alpha channel, if you use the 
			//Vibisility property, the click event will not fire for the SVG
			snprintf2(tmp,150,"<rect id=\"ID%d\" width=\"%f\" height=\"%f\" style=\"fill:rgba(0,0,0,0)\"/>",
				mon->Shuttle[i].Index,
				length,
				width);
			if(CheckStrLen(svgContent,&tmp,tmCORE_MAX_STR_LEN)){
				brsstrcat(svgContent,&tmp);
			}
			else 
				return tmCORE_ERR_STR_LEN_EXCEEDED;
			
			
			if(CheckStrLen(svgContent,&"</g>",tmCORE_MAX_STR_LEN)){
				brsstrcat(svgContent,&"</g>");
			}
			else 
				return tmCORE_ERR_STR_LEN_EXCEEDED;
		
			
			//Check to see if we've had more transforms to add a comma between the units
			if(transCounter>0){
				if(CheckStrLen(svgTransform,&",",tmCORE_MAX_STR_LEN)){
					brsstrcat(svgTransform,&",");
				}
				else 
					return tmCORE_ERR_STR_LEN_EXCEEDED;	
			}
			//Preform translation
			snprintf2(tmp,150,"{\"select\":\"#Shuttle%d\",\"duration\":100,\"display\":true,\"translate\":[%f,%f]},",
				mon->Shuttle[i].Index,
				shCenterX,
				shCenterY,
				-mon->Shuttle[i].Orientation.Angle1,
				length/2.0,
				width/2.0);
			if(CheckStrLen(svgTransform,&tmp,tmCORE_MAX_STR_LEN)){
				brsstrcat(svgTransform,&tmp);
			}
			else 
				return tmCORE_ERR_STR_LEN_EXCEEDED;
			//Preform rotation
			snprintf2(tmp,150,"{\"select\":\"#sh%d\",\"duration\":100,\"display\":true,\"spin\":[%f,%f,%f]}",
				mon->Shuttle[i].Index,
				-mon->Shuttle[i].Orientation.Angle1, //Spin amount
				length/2.0,	//Spin center x
				width/2.0); //Spin center y
			if(CheckStrLen(svgTransform,&tmp,tmCORE_MAX_STR_LEN)){
				brsstrcat(svgTransform,&tmp);
			}
			else 
				return tmCORE_ERR_STR_LEN_EXCEEDED;	
			transCounter++;
		}
		
	}
	if(CheckStrLen(svgContent,&"</svg>",tmCORE_MAX_STR_LEN)){
		brsstrcat(svgContent,&"</svg>");
	}
	else 
		return tmCORE_ERR_STR_LEN_EXCEEDED;
	if(CheckStrLen(svgTransform,&"]",tmCORE_MAX_STR_LEN)){
		brsstrcat(svgTransform,&"]");
	}
	else 
		return tmCORE_ERR_STR_LEN_EXCEEDED;
	
	//No Error, finished everything return OK
	return tmCORE_ERR_OK;
}

/* Core Track Master function blocks. Handles the building of the SVG string */
void tmCore(struct tmCore* inst)
{
	switch (inst->Internal.State){
		case tmCORE_OFF:
			//******************************************************************************** Off state
			if(inst->Enable){
				inst->Internal.TypeID = tmCORE_CORE_TYPE_ID;
				inst->Handle = &inst->Internal;
				
				inst->Internal.Fbs.AsmGetShuttle.Assembly = inst->Assembly;
				inst->Internal.Fbs.AsmGetShuttle.Enable = TRUE;
				inst->Active = TRUE;
				inst->Internal.State = tmCORE_INIT;
			}
			break;
		case tmCORE_INIT:
			//Reset the lookup array just for safety
			brsmemset(&inst->Internal.Axes,0,sizeof(inst->Internal.Axes));
			
        	inst->Internal.State = tmCORE_GET_SH;
			break;
		case tmCORE_GET_SH:
			//******************************************************************************** Get Shuttle state
			if(inst->Internal.Fbs.AsmGetShuttle.Error){
				inst->Error = TRUE;
				inst->ErrorID = tmCORE_ERR_INVALID_ASSEMBLY;
				
				inst->Internal.State = tmCORE_ERROR;
			}
			else if(inst->Internal.Fbs.AsmGetShuttle.Valid){
				if(inst->Internal.Fbs.AsmGetShuttle.TotalCount >= tmMAX_SHUTTLE_COUNT 
				|| inst->Internal.Fbs.AsmGetShuttle.AdditionalInfo.ShuttleID >= tmMAX_SHUTTLE_COUNT){
					
					inst->Error = TRUE;
					inst->ErrorID = tmCORE_ERR_SH_COUNT_EXCEEDED;
					
					inst->Internal.State = tmCORE_ERROR;
				}
				else{
					inst->Internal.Axes[inst->Internal.Fbs.AsmGetShuttle.AdditionalInfo.ShuttleID].Present = TRUE;
					inst->Internal.Axes[inst->Internal.Fbs.AsmGetShuttle.AdditionalInfo.ShuttleID].Axis = inst->Internal.Fbs.AsmGetShuttle.Axis;
					inst->Internal.Fbs.AsmGetShuttle.Next = FALSE;
					
					if(inst->Internal.Fbs.AsmGetShuttle.RemainingCount == 0){
						//Done populating the lookup array, moving on
						inst->Internal.Fbs.AsmGetShuttle.Enable = FALSE;
						
						inst->Internal.State = tmCORE_RUNNING;
					}
					else{
						inst->Internal.ShCount++;
						
						inst->Internal.State = tmCORE_GET_NEXT;
					}
				}
			}
			break;
		case tmCORE_GET_NEXT:
			//******************************************************************************** Get next shuttle state
			inst->Internal.Fbs.AsmGetShuttle.Next = TRUE;
			inst->Internal.State = tmCORE_GET_SH;
			break;
		case tmCORE_RUNNING:
			inst->ErrorID = BuildStrings(inst->ShuttleMon,&inst->SvgContent,&inst->SvgTransform,&inst->ViewBoxCfg);
			inst->StrLengths.ContentLength = brdkStrLen(&inst->SvgContent);
			inst->StrLengths.TransformLength = brdkStrLen(&inst->SvgTransform);
			
			if(inst->ErrorID != tmCORE_ERR_OK){
				inst->Error = TRUE;
				
				inst->Internal.State = tmCORE_ERROR;
			}
			break;
		case tmCORE_RESET:
        	//Try and recover by resetting any blocks
			
			break;
		case tmCORE_ERROR:
			if(inst->ErrorRest){
				inst->Error = FALSE;
				inst->ErrorID = tmCORE_ERR_OK;
				
				inst->Internal.State = tmCORE_OFF;
			}
			break;
	}
	//FB calls
	MC_BR_AsmGetShuttle_AcpTrak(&inst->Internal.Fbs.AsmGetShuttle);
}

