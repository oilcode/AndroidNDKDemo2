//-----------------------------------------------------------------------
#ifndef _SoFileHelp_h_
#define _SoFileHelp_h_
//-----------------------------------------------------------------------
#include "SoFile.h"
//-----------------------------------------------------------------------
class SoFileHelp
{
public:
    static SoFile* CreateFile(const char* szFileName, const char* szOpMode);

#if (SoTargetPlatform == SoPlatform_Android)
    static SoFile* CreateFileAsset(const char* szFileName);
    static SoFile* CreateFileInternal(const char* szFileName, const char* szOpMode);
    static SoFile* CreateFileExternal(const char* szFileName, const char* szOpMode);
#endif

    static void DeleteFile(SoFile*& pFile);
};
//-----------------------------------------------------------------------
#endif //_SoFileHelp_h_
//-----------------------------------------------------------------------
