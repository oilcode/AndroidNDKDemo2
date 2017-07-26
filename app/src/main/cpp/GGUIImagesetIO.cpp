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
	if (kFile.ReadFcfFile(szImagesetName) == false)
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

	GLTexture* pTexture = GLTextureManager::Get()->CreateUITextureFromFile(strTextureName.c_str());
	if (pTexture == 0)
	{
		return false;
	}

	GGUIImageset* pImageset = NULL;
	GGUIImagesetFont* pImagesetFont = NULL;

	const int nDotIndex = SoStrRChr(szImagesetName, '.');

	if (eType == GGUIImagesetType_Normal)
	{
		stImagesetParam kParam;
		kParam.kName = SoSubStr(szImagesetName, 0, nDotIndex-1);
		kParam.nInitRectCount = nRectCount;
		kParam.pTexture = pTexture;

		pImageset = GGUIImagesetManager::Get()->CreateImageset(kParam);
		if (pImageset == NULL)
		{
			return false;
		}
	}
	else
	{
		stImagesetFontParam kParam;
		kParam.kName = SoSubStr(szImagesetName, 0, nDotIndex-1);
		kParam.nInitRectCount = nRectCount;
		kParam.pTexture = pTexture;

		pImagesetFont = GGUIImagesetManager::Get()->CreateImagesetFont(kParam);
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
