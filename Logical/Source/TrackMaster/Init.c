
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
}