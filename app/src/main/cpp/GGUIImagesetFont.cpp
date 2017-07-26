//----------------------------------------------------------------
#include "GGUIImagesetFont.h"
#include "GLTexture.h"
//----------------------------------------------------------------
GGUIImagesetFont::GGUIImagesetFont()
:m_pTexture(NULL)
{
	m_eImagesetType = GGUIImagesetType_Font;
}
//----------------------------------------------------------------
GGUIImagesetFont::~GGUIImagesetFont()
{
	ClearImagesetFont();
}
//----------------------------------------------------------------
bool GGUIImagesetFont::InitImagesetFont(int nInitRectCount)
{
	if (m_kRectArray.InitArray(sizeof(stImageFontRect), nInitRectCount, 40) == false)
	{
		return false;
	}
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
		m_pTexture = 0;
	}
}
//----------------------------------------------------------------
void GGUIImagesetFont::SetTexture(GLTexture* pTexture)
{
	if (m_pTexture)
	{
		m_pTexture->TextureRemoveRef();
		m_pTexture = 0;
	}
	m_pTexture = pTexture;
	if (m_pTexture)
	{
		m_pTexture->TextureAddRef();
	}
}
//----------------------------------------------------------------
void GGUIImagesetFont::AddRect(const char* szChar, const stImageFontRect& kRect)
{
	const souint32 Number = GenerateCharNumber((const souint8*)szChar);
	if (GetIndexByCharNumber(Number) != -1)
	{
		GGUILogf("GGUIImagesetFont::AddRect : kName[%s] is already exist!", szChar);
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
    char szChar[2] = {0};
    float fWidth = 0.0f;
    float fHeight = 56.0f;

    for (int i = 0; i < nCharCount; ++i)
    {
        szChar[0] = szString[i];
        const stImageFontRect* pRect = GetRect(szChar);
        if (pRect == NULL)
        {
            continue;
        }

        fWidth += pRect->advanceX;
    }

    *pStringWidth = fWidth;
    *pStringHeight = fHeight;
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
        return 0.0f;
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
        return 0.0f;
    }
}
//----------------------------------------------------------------
