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
#define GGUILogInfo(_Desc_)  { SoIDEOutputLogInfo("%s", _Desc_); }
#define GGUILogInfof(...)    { const char* _Desc_ = SoStrFmt(__VA_ARGS__); SoIDEOutputLogInfo("%s", _Desc_); }
#define GGUILogError(_Desc_) { SoIDEOutputLogError("%s", _Desc_); SoMessageBox("GGUI", _Desc_); }
#define GGUILogErrorf(...)   { const char* _Desc_ = SoStrFmt(__VA_ARGS__); SoIDEOutputLogError("%s", _Desc_); SoMessageBox("GGUI", _Desc_); }
//------------------------------------------------------------
#endif //_GGUILogHelp_h_
//------------------------------------------------------------
