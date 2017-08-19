//----------------------------------------------------------------
#include "GGUIImagesetManager.h"
//----------------------------------------------------------------
GGUIImagesetManager* GGUIImagesetManager::ms_pInstance = 0;
//----------------------------------------------------------------
bool GGUIImagesetManager::CreateUIImagesetManager()
{
	bool br = true;
	if (ms_pInstance == 0)
	{
		ms_pInstance = new GGUIImagesetManager;
		if (ms_pInstance && ms_pInstance->InitUIImagesetManager())
		{
			br = true;
		}
		else
		{
			br = false;
		}
	}
	return br;
}
//----------------------------------------------------------------
void GGUIImagesetManager::ReleaseUIImagesetManager()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = 0;
	}
}
//----------------------------------------------------------------
GGUIImagesetManager::GGUIImagesetManager()
{

}
//----------------------------------------------------------------
GGUIImagesetManager::~GGUIImagesetManager()
{
	ClearUIImagesetManager();
}
//----------------------------------------------------------------
bool GGUIImagesetManager::InitUIImagesetManager()
{
	if (m_kImagesetArray.InitArray(sizeof(GGUIImageset*), 50, 20) == false)
	{
		return false;
	}
	return true;
}
//----------------------------------------------------------------
void GGUIImagesetManager::ClearUIImagesetManager()
{
	const int nCount = m_kImagesetArray.GetCapacity();
	GGUIImageset* pImageset = 0;
	for (int i = 0; i < nCount; ++i)
	{
		pImageset = GetImagesetByID(i);
		if (pImageset)
		{
			SoDelete pImageset;
		}
	}
	m_kImagesetArray.ClearArray();
	m_kName2IndexMap.clear();
}
//----------------------------------------------------------------
GGUIImageset* GGUIImagesetManager::CreateImageset(const stImagesetParam* pParam)
{
	int nImagesetID = GetImagesetIDByName(pParam->kName);
	if (nImagesetID != -1)
	{
		GGUILogErrorf("GGUIImagesetManager::CreateImageset : kName[%s] is already exist!", pParam->kName.GetValue());
		return (GGUIImageset*)GetImagesetByID(nImagesetID);
	}

	GGUIImageset* pImageset = SoNew GGUIImageset;
	if (pImageset == 0)
	{
		return NULL;
	}

	pImageset->InitImageset(pParam);
	nImagesetID = m_kImagesetArray.FillAt(-1, &pImageset);
	m_kName2IndexMap.insert(std::make_pair(pParam->kName, nImagesetID));
	return pImageset;
}
//----------------------------------------------------------------
GGUIImageset* GGUIImagesetManager::GetImagesetByID(int nImagesetID)
{
	void* pElement = m_kImagesetArray.GetAt(nImagesetID);
	if (pElement)
	{
		return (*((GGUIImageset**)pElement));
	}
	else
	{
		return NULL;
	}
}
//----------------------------------------------------------------
GGUIImageset* GGUIImagesetManager::GetImagesetByName(const SoTinyString& kName)
{
	int nIndex = GetImagesetIDByName(kName);
	if (nIndex != -1)
	{
		return GetImagesetByID(nIndex);
	}
	else
	{
		return NULL;
	}
}
//----------------------------------------------------------------
int GGUIImagesetManager::GetImagesetIDByName(const SoTinyString &kName)
{
	mapName2Index::iterator it = m_kName2IndexMap.find(kName);
	if (it != m_kName2IndexMap.end())
	{
		return it->second;
	}
	else
	{
		return -1;
	}
}
//----------------------------------------------------------------
