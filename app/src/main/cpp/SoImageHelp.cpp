//------------------------------------------------------------
#include "SoImageHelp.h"
#include "SoImagePNG.h"
//------------------------------------------------------------
bool SoImageHelp::LoadImageFile(const char* pszFileName, SoImageFileInfo* pImageInfo)
{
	if (pszFileName == 0)
	{
		return false;
	}
	if (pImageInfo == 0)
	{
		return false;
	}
	//
	SoImageFileType theFileType = CheckFileType(pszFileName);
	if (theFileType == SoImageFile_Invalid)
	{
		return false;
	}
	else if (theFileType == SoImageFile_PNG)
	{
		return SoImagePNG::LoadFromFile(pszFileName, pImageInfo);
	}

	return false;
}
//------------------------------------------------------------
SoImageFileType SoImageHelp::CheckFileType(const char* pszFileName)
{
	if (pszFileName == 0)
	{
		return SoImageFile_Invalid;
	}

	int nLen = 0;
    while (pszFileName[nLen])
    {
        ++nLen;
    }

    if (nLen < 4)
    {
        return SoImageFile_Invalid;
    }

	//判断是否为PNG图片
	if (pszFileName[nLen-3] == 'p' || pszFileName[nLen-3] == 'P')
	{
		if (pszFileName[nLen-2] == 'n' || pszFileName[nLen-2] == 'N')
		{
			if (pszFileName[nLen-1] == 'g' || pszFileName[nLen-1] == 'G')
			{
				return SoImageFile_PNG;
			}
		}
	}

	return SoImageFile_Invalid;
}
//------------------------------------------------------------
