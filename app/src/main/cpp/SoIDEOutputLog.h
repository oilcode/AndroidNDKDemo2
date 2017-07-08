//--------------------------------------------------------------------------------------------------
#ifndef _SoIDEOutputLog_h_
#define _SoIDEOutputLog_h_
//--------------------------------------------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//--------------------------------------------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)

#include "AnIDEOutputLog.h"
#define SoIDEOutputLogInfo AnIDEOutputLogInfo
#define SoIDEOutputLogError AnIDEOutputLogError

#endif
//--------------------------------------------------------------------------------------------------
#endif //_SoIDEOutputLog_h_
//--------------------------------------------------------------------------------------------------
