//----------------------------------------------------------------
#include "GGUIImagesetIO.h"
#include "GGUIFileGGM.h"
#include "GGUIImagesetManager.h"
#include "GLTextureManager.h"
//----------------------------------------------------------------
bool GGUIImagesetIO::Read(const char* szImagesetName, GGUIImagesetType eType)
{
	if (szImagesetName == 0 || szImagesetName[0] == 0)
	{
		return false;
	}
	if (GGUIImagesetManager::Get() == 0)
	{
		return false;
	}
	if (GLTextureManager::Get() == 0)
	{
		return false;
	}

	GGUIFileGGM kFile;
	if (kFile.ReadGgmFile(szImagesetName) == false)
	{
		return false;
	}

	const int nRectCount = kFile.GetImageRectCount();
	if (nRectCount == 0)
	{
		return false;
	}

	std::string strTextureName;
	if (kFile.GetTextureName(strTextureName) == false)
	{
		return false;
	}

    const char* szFullImageName = SoStrFmt("uitexture/%s", strTextureName.c_str());
	GLTexture* pTexture = GLTextureManager::Get()->CreateUITextureFromFile(szFullImageName);
	if (pTexture == 0)
	{
		return false;
	}

	GGUIImageset* pImageset = NULL;
	GGUIImagesetFont* pImagesetFont = NULL;

	const int nDotIndex = SoStrRChr(strTextureName.c_str(), '.');
    const char* szShortName = SoSubStr(strTextureName.c_str(), 0, nDotIndex-1);

	if (eType == GGUIImagesetType_Normal)
	{
		stImagesetParam kParam;
		kParam.kName = szShortName;
		kParam.nInitRectCount = nRectCount;
		kParam.pTexture = pTexture;

		pImageset = GGUIImagesetManager::Get()->CreateImageset(&kParam);
		if (pImageset == NULL)
		{
			return false;
		}
	}
	else
	{
		stImagesetFontParam kParam;
		kParam.kName = szShortName;
		kParam.nInitRectCount = nRectCount;
		kParam.pTexture = pTexture;
        kParam.fFontSize = kFile.GetFontSize();
        kParam.fFontHeight = kFile.GetFontHeight();

		pImagesetFont = GGUIImagesetManager::Get()->CreateImagesetFont(&kParam);
		if (pImagesetFont == NULL)
		{
			return false;
		}
	}

	SoTinyString kRectName;
	stImageRect kRectData;
	stImageFontRect kFontRect;
	for (int i = 0; i < nRectCount; ++i)
	{
		if (eType == GGUIImagesetType_Normal)
		{
			if (kFile.GetNextImageRect(kRectName, kRectData))
			{
				pImageset->AddRect(kRectName, kRectData);
			}
			else
			{
				break;
			}
		}
		else
		{
			if (kFile.GetNextImageFontRect(kRectName, kFontRect))
			{
				pImagesetFont->AddRect(kRectName.GetValue(), kFontRect);
			}
			else
			{
				break;
			}
		}
	}

	return true;
}
//----------------------------------------------------------------
