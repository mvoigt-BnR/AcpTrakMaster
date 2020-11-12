
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	switch (state){
		case 0:
			if(start){
				asmPowerOn.Assembly = &gAssembly_1;
				asmPowerOn.Execute = 1;
				
				state = 10;
			}
			break;
		case 10:
			if(asmPowerOn.Done){
				secAddShuttle.Execute = 1;
				secAddShuttle.Sector = &secMain;
				secAddShuttle.Position = 0;
				
				state = 20;
			}
			break;
		case 20:
			if(secAddShuttle.Done){
				secAddShuttle.Execute = 0;
				count++;
				if(count < maxShuttle){
					state = 21;
					secAddShuttle.Position = 0.1 * count;
				}
				else{
					state = 30;
				}
			}
			break;
		case 21:
			secAddShuttle.Execute = 1;
			state = 20;
			break;
		case 30:
			gPowered = 1;
			
			break;
	}
	MC_BR_AsmPowerOn_AcpTrak(&asmPowerOn);
	MC_BR_SecAddShuttle_AcpTrak(&secAddShuttle);
	MC_BR_RoutedMoveVel_AcpTrak(&routedMoveVel);
     
}
