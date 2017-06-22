//--------------------------------------------------------------------
#ifndef _SoCodeBaseInclude_h_
#define _SoCodeBaseInclude_h_
//--------------------------------------------------------------------
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdarg>
//--------------------------------------------------------------------
#include "SoIntType.h"
#include "SoPlatformDefine.h"
//--------------------------------------------------------------------
#define SoMalloc malloc
#define SoFree free
#define SoNew new
#define SoDelete delete
//--------------------------------------------------------------------
#define SODLL
//--------------------------------------------------------------------
//remove build warning
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //_CRT_SECURE_NO_WARNINGS
//--------------------------------------------------------------------
#endif //_SoCodeBaseInclude_h_
//--------------------------------------------------------------------
