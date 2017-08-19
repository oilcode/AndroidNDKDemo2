//----------------------------------------------------------------
#include "GGUIImageset.h"
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
#include "SoD3DTexture.h"
#elif (SoTargetPlatform == SoPlatform_Android)
#include "GLTexture.h"
#endif
//----------------------------------------------------------------
GGUIImageset::GGUIImageset()
:m_fFontSize(24.0f)
,m_fFontHeight(32.0f)
,m_pTexture(NULL)
{

}
//----------------------------------------------------------------
GGUIImageset::~GGUIImageset()
{
	ClearImageset();
}
//----------------------------------------------------------------
bool GGUIImageset::InitImageset(const stImagesetParam* pParam)
{
	if (m_kRectArray.InitArray(sizeof(stImageRect), pParam->nInitRectCount, 40) == false)
	{
		return false;
	}

#if (SoTargetPlatform == SoPlatform_Windows)
    m_pTexture = (SoD3DTexture*)pParam->pTexture;
#elif (SoTargetPlatform == SoPlatform_Android)
    m_pTexture = (GLTexture*)pParam->pTexture;
#endif

	if (m_pTexture)
	{
		m_pTexture->TextureAddRef();
	}

	m_fFontSize = pParam->fFontSize;
	m_fFontHeight = pParam->fFontHeight;
	return true;
}
//----------------------------------------------------------------
void GGUIImageset::ClearImageset()
{
	m_kRectArray.ClearArray();
	m_kName2IDMap.clear();
    m_kIDMap.clear();
	if (m_pTexture)
	{
		m_pTexture->TextureRemoveRef();
		m_pTexture = 0;
	}
}
//----------------------------------------------------------------
void GGUIImageset::AddRect(const SoTinyString& kName, const stImageRect& kRect)
{
	if (GetRectID(kName) != -1)
	{
		GGUILogErrorf("GGUIImageset::AddRect : kName[%s] is already exist!", kName.GetValue());
		return;
	}

	int nID = m_kRectArray.FillAt(-1, &kRect);
	m_kName2IDMap.insert(std::make_pair(kName, nID));
}
//----------------------------------------------------------------
int GGUIImageset::GetRectID(const SoTinyString& kName) const
{
	mapName2ID::const_iterator it = m_kName2IDMap.find(kName);
	if (it != m_kName2IDMap.end())
	{
		return it->second;
	}
	else
	{
		return -1;
	}
}
//----------------------------------------------------------------
const stImageRect* GGUIImageset::GetRectByID(int nID) const
{
	void* pElement = m_kRectArray.GetAt(nID);
	if (pElement)
	{
		return (stImageRect*)pElement;
	}
	else
	{
		return NULL;
	}
}
//----------------------------------------------------------------
const stImageRect* GGUIImageset::GetRectByName(const SoTinyString& kName) const
{
	int nID = GetRectID(kName);
	if (nID == -1)
	{
		return NULL;
	}
	return GetRectByID(nID);
}
//----------------------------------------------------------------
void GGUIImageset::AddFontRect(const char* szChar, const stImageRect& kRect)
{
    const souint32 Number = GenerateCharNumber((const souint8*)szChar);
    if (GetRectIDByCharNumber(Number) != -1)
    {
        GGUILogErrorf("GGUIImagesetFont::AddRect : kName[%s] is already exist!", szChar);
        return;
    }

    int nIndex = m_kRectArray.FillAt(-1, &kRect);
    m_kIDMap.insert(std::make_pair(Number, nIndex));
}
//----------------------------------------------------------------
const stImageRect* GGUIImageset::GetFontRect(const char* szChar) const
{
    const souint32 Number = GenerateCharNumber((const souint8*)szChar);
    int nIndex = GetRectIDByCharNumber(Number);
    if (nIndex == -1)
    {
        return NULL;
    }

    void* pElement = m_kRectArray.GetAt(nIndex);
    if (pElement)
    {
        return (stImageRect*)pElement;
    }
    else
    {
        return NULL;
    }
}
//----------------------------------------------------------------
void GGUIImageset::CalculateStringGlyphSize(const char* szString, int nCharCount, float* pStringWidth, float* pStringHeight) const
{
    float fWidth = 0.0f;

    int nAccIndex = 0;
    int nSingleWordCharCount = 0;
    const char* szSingleWord = "";

    while (true)
    {
        szSingleWord = SoGetOneCharacterFromUtf8String(szString, nCharCount, nAccIndex, &nSingleWordCharCount);
        if (nSingleWordCharCount == 0)
        {
            break;
        }

        const stImageRect* pRect = GetFontRect(szSingleWord);
        if (pRect)
        {
            fWidth += pRect->advanceX;
        }

        nAccIndex += nSingleWordCharCount;
        nSingleWordCharCount = 0;
    }

    *pStringWidth = fWidth;
    *pStringHeight = m_fFontHeight;
}
//----------------------------------------------------------------
souint64 GGUIImageset::GetTexResource() const
{
    souint64 theRes = 0;
	if (m_pTexture)
	{
#if (SoTargetPlatform == SoPlatform_Windows)
        theRes = (souint64)m_pTexture->GetTextureSRV();
#elif (SoTargetPlatform == SoPlatform_Android)
        theRes = m_pTexture->GetResourceID();
#endif
	}
    return theRes;
}
//----------------------------------------------------------------
float GGUIImageset::GetTextureWidth() const
{
	if (m_pTexture)
	{
		return (float)m_pTexture->GetTextureWidth();
	}
	else
	{
		//可能会作为除数；除数不能是0。
		return 1.0f;
	}
}
//----------------------------------------------------------------
float GGUIImageset::GetTextureHeight() const
{
	if (m_pTexture)
	{
		return (float)m_pTexture->GetTextureHeight();
	}
	else
	{
		//可能会作为除数；除数不能是0。
		return 1.0f;
	}
}
//----------------------------------------------------------------
souint32 GGUIImageset::GenerateCharNumber(const souint8* szChar) const
{
    souint32 nNum = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (szChar[i])
        {
            nNum |= (szChar[i]) << (8*i);
        }
        else
        {
            break;
        }
    }
    return nNum;
}
//----------------------------------------------------------------
int GGUIImageset::GetRectIDByCharNumber(souint32 Number) const
{
    mapCharNumber2ID::const_iterator it = m_kIDMap.find(Number);
    if (it != m_kIDMap.end())
    {
        return it->second;
    }
    else
    {
        return -1;
    }
}
//----------------------------------------------------------------
