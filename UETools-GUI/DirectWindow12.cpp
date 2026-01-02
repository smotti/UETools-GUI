#include "DirectWindow12.h"






void DirectWindow12::Create()
{
#ifdef INACTIVE_ZERO_SIZE
    /*
    * Windows 11 24H2
    * Set ImGui overlay to size of zero on both axis (X - Width & Y - Height) when menu isn't active.
    * We'll rely on such a stupid compromise until solution for updated Desktop Window Manager (DWM) is discovered.
    *
    * Developer of Lossless Scaling (https://store.steampowered.com/app/993090/Lossless_Scaling/) did run
    * into similar issue and was able to find a workaround, although it took a few weeks if not months.
    */
#endif
	return;
}