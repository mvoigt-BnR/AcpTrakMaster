/*********************************************************************************
 * Copyright: B&R Industrial Automation GmbH 
 * Author:    trostelc 
 * Created:   October 16, 2020/5:04 PM 
 *********************************************************************************/ 

#include <bur/plctypes.h>
	
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	//Build the SVG transform string
	//Start by adding the svg viewbox
	//Loop through the shuttle mon, if the shuttle is enabled, you'll take the X/Y/Z/rot and use it to build a <g> in the svg
	
	switch (state){
		case 0:
			if(start || gPowered){
				TrackMasterCore.Assembly = &gAssembly_1;
				TrackMasterCore.ShuttleMon = &gShuttleMon;
				TrackMasterCore.Enable = 1;
				
				//Set parameters for View box (this comes from the automatically generated SVG)
				TrackMasterCore.ViewBoxCfg.MinX = -3.37558;
				TrackMasterCore.ViewBoxCfg.MinY = -0.745;
				TrackMasterCore.ViewBoxCfg.Width = 4.11115;
				TrackMasterCore.ViewBoxCfg.Height = 0.86;
				
			
				state = 10;
			}
			break;
		case 10:
			if(TrackMasterCore.Active){
				ShControl.Enable = 1;
				ShControl.Handle = TrackMasterCore.Handle;
				ShControl.Parameters = &shPars;
			
				state = 20;
			}
			break;
		case 20:
			break;

	}
     
	brdkStrCpy(&ShControl.SelectedElem,&selectedId);
	
	tmCore(&TrackMasterCore);
	tmShuttleControl(&ShControl);
	
	//GetIndex();
}

