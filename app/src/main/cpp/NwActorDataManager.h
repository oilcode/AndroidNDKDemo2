//--------------------------------------------------------------------------------------------------
#ifndef _NwActorDataManager_h_
#define _NwActorDataManager_h_
//--------------------------------------------------------------------------------------------------
#include "NwActorData.h"
#include "SoArray.h"
//--------------------------------------------------------------------------------------------------
class NwActorDataManager
{
public:
    static bool CreateActorDataManager();
    static void ReleaseActorDataManager();
    static NwActorDataManager* Get();

    void SetMainPlayerID(int nId);
    int GetMainPlayerID();

    void AddActorData(const NwActorData& kData);
    void RemoveActorData(int nActorId);
    const NwActorData* GetActorData(int nActorId);

    void AddActorSPKData(const NwActorSPKData& kData);
    void RemoveActorSPKData(int nActorId);
    const NwActorSPKData* GetActorSPKData(int nActorId);

private:
    NwActorDataManager();
    ~NwActorDataManager();
    bool InitActorDataManager();
    void ClearActorDataManager();
    void CreateDefaultData();
    NwActorSPKData* GetActorSPKData_Modify(int nActorId);

private:
    static NwActorDataManager* ms_pInstance;
    SoArray m_kActorDataArray;
    SoArray m_kActorSPKDataArray;
    int m_nMainPlayerId;
};
//--------------------------------------------------------------------------------------------------
inline NwActorDataManager* NwActorDataManager::Get()
{
    return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
inline void NwActorDataManager::SetMainPlayerID(int nId)
{
	m_nMainPlayerId = nId;
}
//--------------------------------------------------------------------------------------------------
inline int NwActorDataManager::GetMainPlayerID()
{
	return m_nMainPlayerId;
}
//--------------------------------------------------------------------------------------------------
#endif //_NwActorDataManager_h_
//--------------------------------------------------------------------------------------------------
