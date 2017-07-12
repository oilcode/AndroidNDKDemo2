//----------------------------------------------------------------
#include "GGUIImageset.h"
#include "GLTexture.h"
//----------------------------------------------------------------
GGUIImageset::GGUIImageset()
:m_pTexture(0)
{

}
//----------------------------------------------------------------
GGUIImageset::~GGUIImageset()
{
	ClearImageset();
}
//----------------------------------------------------------------
bool GGUIImageset::InitImageset(int nInitRectCount)
{
	if (m_kRectArray.InitArray(sizeof(GGUIRect), nInitRectCount, 10) == false)
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
void GGUIImageset::AddRect(const SoTinyString& kName, const GGUIRect& kRect)
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
const GGUIRect& GGUIImageset::GetRect(int nID) const
{
	void* pElement = m_kRectArray.GetAt(nID);
	if (pElement)
	{
		return (*((GGUIRect*)pElement));
	}
	else
	{
		return GGUIRect_Empty;
	}
}
//----------------------------------------------------------------
int GGUIImageset::GetRectCount() const
{
	return m_kRectArray.GetUsingElementCount();
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
