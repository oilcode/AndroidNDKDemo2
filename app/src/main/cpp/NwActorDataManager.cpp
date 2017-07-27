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
{

}
//--------------------------------------------------------------------------------------------------
NwActorDataManager::~NwActorDataManager()
{

}
//--------------------------------------------------------------------------------------------------
bool NwActorDataManager::InitActorDataManager()
{
    return true;
}
//--------------------------------------------------------------------------------------------------
void NwActorDataManager::ClearActorDataManager()
{

}
//--------------------------------------------------------------------------------------------------
