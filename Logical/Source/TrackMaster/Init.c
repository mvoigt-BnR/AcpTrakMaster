
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	brsmemset(&selectedId,0,sizeof(selectedId));
	shPars.Accel = 10;
	shPars.Decel = 10;
	shPars.Vel = 1;
	coreOptions.Color.Enabled = 1;
	coreOptions.Color.Offsets.Red = 0;
	coreOptions.Color.Offsets.Green = 1;
	coreOptions.Color.Offsets.Blue = 2;
	TrackMasterCore.Options = &coreOptions;
}
