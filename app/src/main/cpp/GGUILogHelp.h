//------------------------------------------------------------
#ifndef _GGUILogHelp_h_
#define _GGUILogHelp_h_
//------------------------------------------------------------
#include "SoStringHelp.h"
#include "SoIDEOutputLog.h"
#include "SoMessageBox.h"
//------------------------------------------------------------
/*
class GGUILogHelp
{
public:
    static void Print(const char* szDesc);
    static void Printf(const char* szFormat, ...);
};
//------------------------------------------------------------
#define GGUILogInfo  GGUILogHelp::Print
#define GGUILogf GGUILogHelp::Printf
*/
//------------------------------------------------------------
#define GGUILogInfo   SoIDEOutputLog
#define GGUILogInfof  SoIDEOutputLogf

#ifdef SoMessageBoxEnable
#define GGUILogError(_Desc_)  { SoIDEOutputLog(_Desc_); SoMessageBox("GGUI", _Desc_); }
#define GGUILogErrorf(...)    { const char* _Desc_ = SoStrFmt(__VA_ARGS__); SoIDEOutputLog(_Desc_); SoMessageBox("GGUI", _Desc_); }
#else
#define GGUILogError   SoIDEOutputLog
#define GGUILogErrorf  SoIDEOutputLogf
#endif
//------------------------------------------------------------
#endif //_GGUILogHelp_h_
//------------------------------------------------------------
