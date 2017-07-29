//--------------------------------------------------------------------------------------------------
#include "NwActorDataManager.h"
//--------------------------------------------------------------------------------------------------
NwActorDataManager* NwActorDataManager::ms_pInstance = NULL;
//--------------------------------------------------------------------------------------------------
bool NwActorDataManager::CreateActorDataManager()
{
    bool br = true;
    if (ms_pInstance == 0)
    {
        ms_pInstance = SoNew NwActorDataManager;
        if (ms_pInstance && ms_pInstance->InitActorDataManager())
        {
            br = true;
        }
        else
        {
            ReleaseActorDataManager();
            br = false;
        }
    }
    return br;
}
//--------------------------------------------------------------------------------------------------
void NwActorDataManager::ReleaseActorDataManager()
{
    if (ms_pInstance)
    {
        ms_pInstance->ClearActorDataManager();
        SoDelete ms_pInstance;
        ms_pInstance = 0;
    }
}
//--------------------------------------------------------------------------------------------------
NwActorDataManager::NwActorDataManager()
:m_nMainPlayerId(-1)
{

}
//--------------------------------------------------------------------------------------------------
NwActorDataManager::~NwActorDataManager()
{

}
//--------------------------------------------------------------------------------------------------
bool NwActorDataManager::InitActorDataManager()
{
    if (m_kActorDataArray.InitArray(sizeof(NwActorData*), 10, 30) == false)
    {
        return false;
    }
    if (m_kActorSPKDataArray.InitArray(sizeof(NwActorSPKData*), 10, 30) == false)
    {
        return false;
    }
    return true;
}
//--------------------------------------------------------------------------------------------------
void NwActorDataManager::ClearActorDataManager()
{
    NwActorData* pData = 0;
    int nCount = m_kActorDataArray.GetSize();
    for (int i = 0; i < nCount; ++i)
    {
        pData = *(NwActorData**)m_kActorDataArray.GetAt(i);
        SoDelete pData;
    }
    m_kActorDataArray.ClearArray();
    //
    NwActorSPKData* pSPKData = 0;
    nCount = m_kActorSPKDataArray.GetSize();
    for (int i = 0; i < nCount; ++i)
    {
        pSPKData = *(NwActorSPKData**)m_kActorSPKDataArray.GetAt(i);
        SoDelete pSPKData;
    }
    m_kActorSPKDataArray.ClearArray();
    //
    m_nMainPlayerId = -1;
}
//--------------------------------------------------------------------------------------------------
void NwActorDataManager::AddActorData(const NwActorData& kData)
{

}
//--------------------------------------------------------------------------------------------------
void NwActorDataManager::RemoveActorData(int nActorId)
{

}
//--------------------------------------------------------------------------------------------------
const NwActorData* NwActorDataManager::GetActorData(int nActorId)
{
    return NULL;
}
//--------------------------------------------------------------------------------------------------
void NwActorDataManager::AddActorSPKData(const NwActorSPKData& kData)
{
    NwActorSPKData* pSPKData = GetActorSPKData_Modify(kData.m_nActorId);
    if (pSPKData)
    {
        //already exist
        *pSPKData = kData;
        return;
    }

    NwActorSPKData* newSPKData = SoNew NwActorSPKData;
    if (newSPKData == NULL)
    {
        return;
    }

    *newSPKData = kData;
    m_kActorSPKDataArray.PushBack(&newSPKData);
}
//--------------------------------------------------------------------------------------------------
void NwActorDataManager::RemoveActorSPKData(int nActorId)
{
    NwActorSPKData* pSPKData = GetActorSPKData_Modify(nActorId);
    if (pSPKData)
    {
        pSPKData->ClearAll();
    }
}
//--------------------------------------------------------------------------------------------------
const NwActorSPKData* NwActorDataManager::GetActorSPKData(int nActorId)
{
    return GetActorSPKData_Modify(nActorId);
}
//--------------------------------------------------------------------------------------------------
NwActorSPKData* NwActorDataManager::GetActorSPKData_Modify(int nActorId)
{
    NwActorSPKData* pResult = NULL;
    NwActorSPKData* pSPKData = NULL;
    const int nCount = m_kActorSPKDataArray.GetSize();
    for (int i = 0; i < nCount; ++i)
    {
        pSPKData = *(NwActorSPKData**)m_kActorSPKDataArray.GetAt(i);
        if (pSPKData->m_nActorId == nActorId)
        {
            pResult = pSPKData;
            break;
        }
    }
    return pResult;
}
//--------------------------------------------------------------------------------------------------
void NwActorDataManager::CreateDefaultData()
{

}
//--------------------------------------------------------------------------------------------------
