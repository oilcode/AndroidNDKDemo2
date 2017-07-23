//--------------------------------------------------------------------
#ifndef _SoCodeBaseInclude_h_
#define _SoCodeBaseInclude_h_
//--------------------------------------------------------------------
#define SoPlatform_Windows  1
#define SoPlatform_Android  2
//--------------------------------------------------------------------
#ifdef WIN32
#define SoTargetPlatform  SoPlatform_Windows
#else
#define SoTargetPlatform  SoPlatform_Android
#endif
//--------------------------------------------------------------------
#define SoAppBit_32  1
#define SoAppBit_64  2
//--------------------------------------------------------------------
#define SoTargetAppBit  SoAppBit_32
//--------------------------------------------------------------------
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <string>
#include <map>
//--------------------------------------------------------------------
#define SoMalloc malloc
#define SoFree free
#define SoNew new
#define SoDelete delete
//--------------------------------------------------------------------
#define SODLL
//--------------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
typedef __int8  soint8;
typedef __int16 soint16;
typedef __int32 soint32;
typedef __int32 soint;
typedef __int64 soint64;
typedef unsigned __int8  souint8;
typedef unsigned __int16 souint16;
typedef unsigned __int32 souint32;
typedef unsigned __int32 souint;
typedef unsigned __int64 souint64;
typedef float sofloat;
typedef double sodouble;
#else
typedef int8_t  soint8;
typedef int16_t soint16;
typedef int32_t soint32;
typedef int32_t soint;
typedef int64_t soint64;
typedef uint8_t  souint8;
typedef uint16_t souint16;
typedef uint32_t souint32;
typedef uint32_t souint;
typedef uint64_t souint64;
typedef float sofloat;
typedef double sodouble;
#endif
//--------------------------------------------------------------------
#endif //_SoCodeBaseInclude_h_
//--------------------------------------------------------------------
