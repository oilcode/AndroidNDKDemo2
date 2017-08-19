//--------------------------------------------------------------------------------------------------
#ifndef _SoIDEOutputLog_h_
#define _SoIDEOutputLog_h_
//--------------------------------------------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//--------------------------------------------------------------------------------------------------
#define SoIDEOutputLogEnable
//--------------------------------------------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)

#include <Windows.h>
#include "SoStringHelp.h"
#define SoIDEOutputLog(_Desc_)  ::OutputDebugStringA(_Desc_)
#define SoIDEOutputLogf(...)    { const char* _Desc_ = SoStrFmt(__VA_ARGS__); ::OutputDebugStringA(_Desc_); }

#elif (SoTargetPlatform == SoPlatform_Android)

#include "AnIDEOutputLog.h"
#define SoIDEOutputLog   AnIDEOutputLog
#define SoIDEOutputLogf  AnIDEOutputLogf

#endif
//--------------------------------------------------------------------------------------------------
#endif //_SoIDEOutputLog_h_
//--------------------------------------------------------------------------------------------------
