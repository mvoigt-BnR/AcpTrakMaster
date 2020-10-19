
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
			if(secAddShuttle.Busy){
				secAddShuttle.Execute = 0;
			
				axis = secAddShuttle.Axis;
				
				routedMoveVel.Axis = &axis;
				routedMoveVel.Velocity = 1;
				routedMoveVel.Acceleration = 10;
				routedMoveVel.Deceleration = 10;
				routedMoveVel.Sector = &secMain;
				routedMoveVel.Position = 0;
				routedMoveVel.Execute = 1;
			
				state = 30;
			}
	}
	MC_BR_AsmPowerOn_AcpTrak(&asmPowerOn);
	MC_BR_SecAddShuttle_AcpTrak(&secAddShuttle);
	MC_BR_RoutedMoveVel_AcpTrak(&routedMoveVel);
     
}
