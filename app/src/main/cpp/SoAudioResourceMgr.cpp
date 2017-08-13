//----------------------------------------------------------------
#include "SoAudioResourceMgr.h"
#include "SoStringHelp.h"
#include "SoMessageBox.h"
//----------------------------------------------------------------
SoAudioResourceMgr* SoAudioResourceMgr::ms_pInstance = NULL;
//----------------------------------------------------------------
bool SoAudioResourceMgr::CreateAudioResourceMgr()
{
    bool br = true;
    if (ms_pInstance == NULL)
    {
        ms_pInstance = SoNew SoAudioResourceMgr;
        if (ms_pInstance && ms_pInstance->InitAudioResourceMgr())
        {
            br = true;
        }
        else
        {
            ReleaseAudioResourceMgr();
            br = false;
        }
    }
    return br;
}
//----------------------------------------------------------------
void SoAudioResourceMgr::ReleaseAudioResourceMgr()
{
    if (ms_pInstance)
    {
        ms_pInstance->ClearAudioResourceMgr();
        SoDelete ms_pInstance;
        ms_pInstance = NULL;
    }
}
//----------------------------------------------------------------
SoAudioResourceMgr::SoAudioResourceMgr()
{

}
//----------------------------------------------------------------
SoAudioResourceMgr::~SoAudioResourceMgr()
{

}
//----------------------------------------------------------------
bool SoAudioResourceMgr::InitAudioResourceMgr()
{
    if (m_kResourceArray.InitArray(sizeof(SoAudioResource*), 20, 20) == false)
    {
        return false;
    }
	return true;
}
//----------------------------------------------------------------
void SoAudioResourceMgr::ClearAudioResourceMgr()
{
    const int nCount = m_kResourceArray.GetCapacity();
    SoAudioResource* pResource = NULL;
    for (int i = 0; i < nCount; ++i)
    {
        pResource = GetAudioResource(i);
        if (pResource)
        {
            SoDelete pResource;
        }
    }
    m_kResourceArray.ClearArray();
    m_kResourceMap.clear();
}
//----------------------------------------------------------------
SoAudioResource* SoAudioResourceMgr::CreateAudioResource(const SoTinyString& kResourceName)
{
	mapName2ID::iterator it = m_kResourceMap.find(kResourceName);
	if (it != m_kResourceMap.end())
	{
		return GetAudioResource(it->second);
	}

    SoAudioResource* pResource = SoNew SoAudioResource;
	if (pResource == NULL)
	{
		return NULL;
	}

    const int nResourceId = m_kResourceArray.FillAt(-1, &pResource);
    pResource->SetResourceID(nResourceId);

    std::pair<mapName2ID::iterator, bool> insertResult = m_kResourceMap.insert(std::make_pair(kResourceName, nResourceId));
    if (insertResult.second == false)
    {
        m_kResourceArray.ClearAt(nResourceId);
        SoDelete pResource;
        pResource = NULL;
        return NULL;
    }

    mapName2ID::iterator& it2 = insertResult.first;
    const char* fileName = it2->first.GetValue();
    pResource->SetResourceName(fileName);

    if (pResource->InitAudioResource() == false)
    {
        m_kResourceMap.erase(it2);
        m_kResourceArray.ClearAt(nResourceId);
        SoDelete pResource;
        pResource = NULL;
        return NULL;
    }

	return pResource;
}
//----------------------------------------------------------------
SoAudioResource* SoAudioResourceMgr::GetAudioResource(int nResourceId)
{
    void* pElement = m_kResourceArray.GetAt(nResourceId);
    if (pElement)
    {
        return (*((SoAudioResource**)pElement));
    }
    else
    {
        return NULL;
    }
}
//----------------------------------------------------------------
int SoAudioResourceMgr::GetAudioResourceID(const SoTinyString& kResourceName)
{
    int nId = -1;
    mapName2ID::iterator it = m_kResourceMap.find(kResourceName);
    if (it != m_kResourceMap.end())
    {
        nId = it->second;
    }
    return nId;
}
//----------------------------------------------------------------
