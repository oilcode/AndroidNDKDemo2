//--------------------------------------------------------------------------------------------------
#ifndef _SoIDEOutputLog_h_
#define _SoIDEOutputLog_h_
//--------------------------------------------------------------------------------------------------
#include "SoPlatformDefine.h"
#include "AnIDEOutputLog.h"
//--------------------------------------------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
#define SoIDEOutputLogInfo AnIDEOutputLogInfo
#define SoIDEOutputLogError AnIDEOutputLogError
#endif
//--------------------------------------------------------------------------------------------------
#endif //_SoIDEOutputLog_h_
//--------------------------------------------------------------------------------------------------
