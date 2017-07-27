//--------------------------------------------------------------------------------------------------
#ifndef _NwActorDataManager_h_
#define _NwActorDataManager_h_
//--------------------------------------------------------------------------------------------------
#include "NwActorData.h"
//--------------------------------------------------------------------------------------------------
class NwActorDataManager
{
public:
    static bool CreateActorDataManager();
    static void ReleaseActorDataManager();
    static NwActorDataManager* Get();

private:
    NwActorDataManager();
    ~NwActorDataManager();
    bool InitActorDataManager();
    void ClearActorDataManager();

private:
    static NwActorDataManager* ms_pInstance;

};
//--------------------------------------------------------------------------------------------------
inline NwActorDataManager* NwActorDataManager::Get()
{
    return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
#endif //_NwActorDataManager_h_
//--------------------------------------------------------------------------------------------------
