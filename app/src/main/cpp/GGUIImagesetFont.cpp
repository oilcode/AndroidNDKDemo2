//----------------------------------------------------------------
#include "GGUIImagesetFont.h"
#include "GLTexture.h"
//----------------------------------------------------------------
stImagesetFontRect ImagesetFontRect_Empty;
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
	if (m_kRectArray.InitArray(sizeof(stImagesetFontRect), nInitRectCount, 40) == false)
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
void GGUIImagesetFont::AddRect(const char* szChar, const stImagesetFontRect& kRect)
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
const stImagesetFontRect& GGUIImagesetFont::GetRect(const char* szChar)
{
	const souint32 Number = GenerateCharNumber((const souint8*)szChar);
	int nIndex = GetIndexByCharNumber(Number);
	if (nIndex == -1)
	{
		return ImagesetFontRect_Empty;
	}

	void* pElement = m_kRectArray.GetAt(nIndex);
	if (pElement)
	{
		return (*((stImagesetFontRect*)pElement));
	}
	else
	{
		return ImagesetFontRect_Empty;
	}
}
//----------------------------------------------------------------
const stImagesetFontRect* GGUIImagesetFont::GetRectP(const char* szChar)
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
		return (stImagesetFontRect*)pElement;
	}
	else
	{
		return NULL;
	}
}
//----------------------------------------------------------------
souint32 GGUIImagesetFont::GenerateCharNumber(const souint8* szChar)
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
