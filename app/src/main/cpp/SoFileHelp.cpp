//-----------------------------------------------------------------------
#include "SoFileHelp.h"
#include "AnFileAsset.h"
#include "AnFileInternal.h"
#include "AnFileExternal.h"
//-----------------------------------------------------------------------
SoFile* SoFileHelp::CreateFile(const char* szFileName, const char* szOpMode)
{
	if (szFileName == 0 || szFileName[0] == 0)
	{
		return 0;
	}
	if (szOpMode == 0)
	{
		return 0;
	}

#if (SoTargetPlatform == SoPlatform_Windows)
	SoFile* pFile = new SoFile();
#elif (SoTargetPlatform == SoPlatform_Android)
    SoFile* pFile = new AnFileAsset();
#endif

	if (pFile)
	{
		if (pFile->InitFile(szFileName, szOpMode) == false)
		{
			DeleteFile(pFile);
			pFile = 0;
		}
	}
	return pFile;
}
//-----------------------------------------------------------------------
SoFile* SoFileHelp::CreateFileAsset(const char* szFileName)
{
    if (szFileName == 0 || szFileName[0] == 0)
    {
        return 0;
    }

    SoFile* pFile = new AnFileAsset();
    if (pFile)
    {
        if (pFile->InitFile(szFileName, "") == false)
        {
            DeleteFile(pFile);
            pFile = 0;
        }
    }
    return pFile;
}
//-----------------------------------------------------------------------
SoFile* SoFileHelp::CreateFileInternal(const char* szFileName, const char* szOpMode)
{
    if (szFileName == 0 || szFileName[0] == 0)
    {
        return 0;
    }
    if (szOpMode == 0)
    {
        return 0;
    }

    SoFile* pFile = new AnFileInternal();
    if (pFile)
    {
        if (pFile->InitFile(szFileName, szOpMode) == false)
        {
            DeleteFile(pFile);
            pFile = 0;
        }
    }
    return pFile;
}
//-----------------------------------------------------------------------
SoFile* SoFileHelp::CreateFileExternal(const char* szFileName, const char* szOpMode)
{
    if (szFileName == 0 || szFileName[0] == 0)
    {
        return 0;
    }
    if (szOpMode == 0)
    {
        return 0;
    }

    SoFile* pFile = new AnFileExternal();
    if (pFile)
    {
        if (pFile->InitFile(szFileName, szOpMode) == false)
        {
            DeleteFile(pFile);
            pFile = 0;
        }
    }
    return pFile;
}
//-----------------------------------------------------------------------
void SoFileHelp::DeleteFile(SoFile*& pFile)
{
	if (pFile)
	{
		pFile->ClearFile();
		delete pFile;
		pFile = 0;
	}
}
//-----------------------------------------------------------------------
