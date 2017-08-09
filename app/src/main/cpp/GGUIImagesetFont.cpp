//----------------------------------------------------------------
#include "GGUIImagesetFont.h"
#include "GLTexture.h"
//----------------------------------------------------------------
GGUIImagesetFont::GGUIImagesetFont()
:m_pTexture(NULL)
,m_fFontSize(24.0f)
,m_fFontHeight(32.0f)
{
	m_eImagesetType = GGUIImagesetType_Font;
}
//----------------------------------------------------------------
GGUIImagesetFont::~GGUIImagesetFont()
{
	ClearImagesetFont();
}
//----------------------------------------------------------------
bool GGUIImagesetFont::InitImagesetFont(const stImagesetFontParam* pParam)
{
	if (m_kRectArray.InitArray(sizeof(stImageFontRect), pParam->nInitRectCount, 40) == false)
	{
		return false;
	}

	m_pTexture = pParam->pTexture;
	if (m_pTexture)
	{
		m_pTexture->TextureAddRef();
	}

	m_fFontSize = pParam->fFontSize;
	m_fFontHeight = pParam->fFontHeight;
	return true;
}
//----------------------------------------------------------------
void GGUIImagesetFont::ClearImagesetFont()
{
	m_kRectArray.ClearArray();
	m_kIDMap.clear();
	if (m_pTexture)
	{
		m_pTexture->TextureRemoveRef();
		m_pTexture = NULL;
	}
}
//----------------------------------------------------------------
void GGUIImagesetFont::AddRect(const char* szChar, const stImageFontRect& kRect)
{
	const souint32 Number = GenerateCharNumber((const souint8*)szChar);
	if (GetIndexByCharNumber(Number) != -1)
	{
		GGUILogErrorf("GGUIImagesetFont::AddRect : kName[%s] is already exist!", szChar);
		return;
	}

	int nIndex = m_kRectArray.FillAt(-1, &kRect);
	m_kIDMap.insert(std::make_pair(Number, nIndex));
}
//----------------------------------------------------------------
const stImageFontRect* GGUIImagesetFont::GetRect(const char* szChar) const
{
	const souint32 Number = GenerateCharNumber((const souint8*)szChar);
	int nIndex = GetIndexByCharNumber(Number);
	if (nIndex == -1)
	{
		return NULL;
	}

	void* pElement = m_kRectArray.GetAt(nIndex);
	if (pElement)
	{
		return (stImageFontRect*)pElement;
	}
	else
	{
		return NULL;
	}
}
//----------------------------------------------------------------
void GGUIImagesetFont::CalculateStringGlyphSize(const char* szString, int nCharCount, float* pStringWidth, float* pStringHeight) const
{
    SoIDEOutputLogInfo("ImagesetFontCalculate : %s", szString);
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

        const stImageFontRect* pRect = GetRect(szSingleWord);
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
souint32 GGUIImagesetFont::GenerateCharNumber(const souint8* szChar) const
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
int GGUIImagesetFont::GetIndexByCharNumber(souint32 Number) const
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
souint32 GGUIImagesetFont::GetTexResourceID() const
{
	if (m_pTexture)
	{
		return m_pTexture->GetResourceID();
	}
	else
	{
		return 0;
	}
}
//----------------------------------------------------------------
float GGUIImagesetFont::GetTextureWidth() const
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
float GGUIImagesetFont::GetTextureHeight() const
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
