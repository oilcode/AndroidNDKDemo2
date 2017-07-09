//------------------------------------------------------------
#ifndef _GGUILogHelp_h_
#define _GGUILogHelp_h_
//------------------------------------------------------------
class GGUILogHelp
{
public:
    static void Print(const char* szDesc);
    static void Printf(const char* szFormat, ...);
};
//------------------------------------------------------------
#define GGUILog  GGUILogHelp::Print
#define GGUILogf GGUILogHelp::Printf
//------------------------------------------------------------
#endif //_GGUILogHelp_h_
//------------------------------------------------------------
