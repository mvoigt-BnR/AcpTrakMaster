
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	brsmemset(&svgContent,0,sizeof(svgContent));
	brsmemset(&svgTransform,0,sizeof(svgTransform));
}
