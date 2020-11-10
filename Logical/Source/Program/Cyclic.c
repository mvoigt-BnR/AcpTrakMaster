/*********************************************************************************
 * Copyright: B&R Industrial Automation GmbH 
 * Author:    trostelc 
 * Created:   October 16, 2020/5:04 PM 
 *********************************************************************************/ 

#include <bur/plctypes.h>
	
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void GetIndex(){
	char buf[2];
	//Get a substring of the first 3 characters
	brdkStrSubStr(&buf,&selectedId,0,3);
	//Look at the start of the selectedID, if it starts with #ID then we know a shuttle has been clicked
	if(0 == brsstrcmp(&buf,&"#ID")){
		Selected = 1;
	}
	else{
		Selected = 0;
	}
}
void _CYCLIC ProgramCyclic(void)
{
	//Build the SVG transform string
	//Start by adding the svg viewbox
	//Loop through the shuttle mon, if the shuttle is enabled, you'll take the X/Y/Z/rot and use it to build a <g> in the svg
	
	TrackMasterCore.Assembly = &gAssembly_1;
	TrackMasterCore.ShuttleMon = &gShuttleMon;
	
	ShControl.Handle = TrackMasterCore.Handle;
	ShControl.Parameters = &shPars;
	brdkStrCpy(&ShControl.SelectedElem,&selectedId);
	
	tmCore(&TrackMasterCore);
	tmShuttleControl(&ShControl);
	
	//GetIndex();
}

