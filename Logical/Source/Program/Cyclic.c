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
		brsmemset(&svgTransform,0,sizeof(svgTransform));
		
		brsstrcat(&svgContent,&"<svg viewBox=\"-3.37558 -0.745 4.11115 0.86\">");
		for (idx = 0; idx < 9; idx++){
			if(gShuttleMon.Shuttle[idx].Available){
				snprintf2(tmp,150,"<g id=\"Shuttle\">");
				brsstrcat(&svgContent,&tmp);
				snprintf2(tmp,150,"<rect id=\"box\" x=\"%f\" y=\"%f\" width=\"%0f\" height=\"%1f\" style=\"fill:rgb(0,255,0);\"/>",
					-gShuttleMon.Shuttle[idx].ExtentToFront / 1000.0,
					-gShuttleMon.Shuttle[idx].ExtentToFront / 1000.0,
					(gShuttleMon.Shuttle[idx].ExtentToBack + gShuttleMon.Shuttle[idx].ExtentToFront)/ 1000.0,
					gShuttleMon.Shuttle[idx].Width / 1000.0);
				brsstrcat(&svgContent,&tmp);				
				snprintf2(tmp,150,"<text x=\"%f\" y=\"%f\">Shuttle %d</text>",
					-gShuttleMon.Shuttle[idx].ExtentToFront / 1000.0,
					-gShuttleMon.Shuttle[idx].ExtentToFront / 1000.0,
					gShuttleMon.Shuttle[idx].Index);
				brsstrcat(&svgContent,&tmp);
				brsstrcat(&svgContent,&"</g>");
				
				snprintf2(tmp,150,"[{\"select\":\"#Shuttle\",\"duration\":100,\"display\":true,\"translate\":[%f,%f]}]",
					gShuttleMon.Shuttle[idx].Position.X / 1000.0,
					-gShuttleMon.Shuttle[idx].Position.Y / 1000.0);
				brsstrcat(&svgTransform,&tmp);
				
			}
		}
		brsstrcat(&svgContent,&"</svg>");
	}
}

