//----------------------------------------------------------------
#include "GGUIImageset.h"
#include "GLTexture.h"
//----------------------------------------------------------------
GGUIImageset::GGUIImageset()
:m_pTexture(0)
{
	m_eImagesetType = GGUIImagesetType_Normal;
}
//----------------------------------------------------------------
GGUIImageset::~GGUIImageset()
{
	ClearImageset();
}
//----------------------------------------------------------------
bool GGUIImageset::InitImageset(int nInitRectCount)
{
	if (m_kRectArray.InitArray(sizeof(stImageRect), nInitRectCount, 10) == false)
	{
		return false;
	}
	return true;
}
//----------------------------------------------------------------
void GGUIImageset::ClearImageset()
{
	m_kRectArray.ClearArray();
	m_kName2IDMap.clear();
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
		GGUILogf("GGUIImageset::AddRect : kName[%s] is already exist!", kName.GetValue());
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
souint32 GGUIImageset::GetTexResourceID() const
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
float GGUIImageset::GetTextureWidth() const
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
float GGUIImageset::GetTextureHeight() const
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
void GGUIImageset::SetTexture(GLTexture* pTexture)
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
