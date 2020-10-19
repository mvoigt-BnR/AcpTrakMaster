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
	
	if(testEnable){
		//Reset the entire SVG additional content
		brsmemset(&svgContent,0,sizeof(svgContent));
		
		brsstrcat(&svgContent,&"<svg viewBox=\"-0.735577 -0.745 4.11115 1.52\">");
		for (idx = 0; idx < 9; idx++){
			if(gShuttleMon.Shuttle[idx].Available){
				brsstrcat(&svgContent,&"<rect x=\"");
				brsftoa((REAL)-gShuttleMon.Shuttle[idx].Position.X / 1000.0,&tmp);
				brsstrcat(&svgContent,&tmp);
				brsstrcat(&svgContent,&"\" y=\"");
				brsftoa((REAL)gShuttleMon.Shuttle[idx].Position.Y / 1000.0,&tmp);
				brsstrcat(&svgContent,&tmp);
				brsstrcat(&svgContent,&"\" width=\"");
				brsftoa((REAL)(gShuttleMon.Shuttle[idx].ExtentToBack + gShuttleMon.Shuttle[idx].ExtentToFront)/ 1000.0,&tmp);
				brsstrcat(&svgContent,&tmp);
				brsstrcat(&svgContent,&"\" height=\"");
				brsftoa((REAL)gShuttleMon.Shuttle[idx].Width / 1000.0,&tmp);
				brsstrcat(&svgContent,&tmp);
				brsstrcat(&svgContent,&"\" style=\"fill:rgb(0,255,0)\"/>");
			}
		}
		brsstrcat(&svgContent,&"</svg>");
	}
		
	
}

