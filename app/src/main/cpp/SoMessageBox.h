//--------------------------------------------------------------------------------------------------
#ifndef _SoMessageBox_h_
#define _SoMessageBox_h_
//--------------------------------------------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//--------------------------------------------------------------------------------------------------
#define SoMessageBoxEnable
//--------------------------------------------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)

#include <Windows.h>
#define SoMessageBox(szTitle, szMessage)  MessageBoxA(NULL, szTitle, szMessage, MB_OK)

#elif (SoTargetPlatform == SoPlatform_Android)

#include "AnJava2CppStaticFunction.h"
#define SoMessageBox(szTitle, szMessage)  AnJava2CppStaticFunction::ShowMessageBox(szTitle, szMessage)

#endif
//--------------------------------------------------------------------------------------------------
#endif //_SoMessageBox_h_
//--------------------------------------------------------------------------------------------------
