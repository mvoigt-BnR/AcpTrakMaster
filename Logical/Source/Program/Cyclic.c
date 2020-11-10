/*********************************************************************************
 * Copyright: B&R Industrial Automation GmbH 
 * Author:    trostelc 
 * Created:   October 16, 2020/5:04 PM 
 *********************************************************************************/ 

#include <bur/plctypes.h>
	
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif
void BuildStr(){
	LREAL width;
	LREAL length;
	width = gShuttleMon.Shuttle[idx].Width / 1000.0;
	length = (gShuttleMon.Shuttle[idx].ExtentToBack + gShuttleMon.Shuttle[idx].ExtentToFront)/ 1000.0;
	
	snprintf2(tmp,150,"<g id=\"Shuttle\">");
	brsstrcat(&svgContent,&tmp);
	
	snprintf2(tmp,150,"<polygon id=\"box\" x=\"%f\" y=\"%f\" points=\"0,0 %0f,0 , %f,%f %f,%f 0,%f\" style=\"fill:rgb(0,255,0);\"/>",
		-gShuttleMon.Shuttle[idx].ExtentToBack / 1000.0,
		-width,
		(length-width/2.0),
		length,
		width/2.0,
		(length-width/2.0),
		width,
		width);
	brsstrcat(&svgContent,&tmp);	
	
	snprintf2(tmp,150,"<text x=\"%f\" y=\"%f\" font-weight=\"bold\" font-size=\"0.035px\">%d</text>",
		length * 0,
		width * 3.0 / 4.0,
		gShuttleMon.Shuttle[idx].Index);
	brsstrcat(&svgContent,&tmp);
	
	//Create an invisible bounding rectangle to handle the click event. "Invisible" by using the alpha channel, if you use the 
	//Vibisility property, the click event will not fire for the SVG
	snprintf2(tmp,150,"<rect id=\"ID%d\" width=\".05\" height=\"0.05\" style=\"fill:rgba(0,0,255,0)\"/>",
		gShuttleMon.Shuttle[idx].Index,
		length ,
		width);
	brsstrcat(&svgContent,&tmp);
	
	
	brsstrcat(&svgContent,&"</g>");
}
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
	
	if(testEnable){
		//Reset the entire SVG additional content
		brsmemset(&svgContent,0,sizeof(svgContent));
		brsmemset(&svgTransform,0,sizeof(svgTransform));
		
		brsstrcat(&svgContent,&"<svg viewBox=\"-3.37558 -0.745 4.11115 0.86\">");
		for (idx = 0; idx < 9; idx++){
			if(gShuttleMon.Shuttle[idx].Available){
				
				
				BuildStr();			
				
				
				snprintf2(tmp,150,"[{\"select\":\"#Shuttle\",\"duration\":100,\"display\":true,\"translate\":[%f,%f]}]",
					gShuttleMon.Shuttle[idx].Position.X / 1000.0 - gShuttleMon.Shuttle[idx].ExtentToBack / 1000.0,
					-gShuttleMon.Shuttle[idx].Position.Y / 1000.0 - gShuttleMon.Shuttle[idx].Width / 2000.0);
				brsstrcat(&svgTransform,&tmp);
				
			}
		}
		brsstrcat(&svgContent,&"</svg>");
	}
	GetIndex();
}

