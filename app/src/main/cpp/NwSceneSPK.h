//--------------------------------------------------------------------------------------------------
#ifndef _NwSceneSPK_h_
#define _NwSceneSPK_h_
//--------------------------------------------------------------------------------------------------
#include "NwBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class NwUISPK;
class NwSPKLogic;
class NwSPKProcedure;
class NwSPKJudge;
class NwSPKData;
//--------------------------------------------------------------------------------------------------
class NwSceneSPK
{
public:
	static bool CreateSceneSPK();
	static void ReleaseSceneSPK();
	static NwSceneSPK* Get();

	void StartSPK();
	void UpdateSceneSPK(float fDeltaTime);

	NwUISPK* GetUISPK();
	NwSPKLogic* GetSPKLogic();
	NwSPKProcedure* GetSPKProcedure();
    NwSPKJudge* GetSPKJudge();
    NwSPKData* GetSPKData();

private:
	NwSceneSPK();
	~NwSceneSPK();
	bool InitSceneSPK();
	void ClearSceneSPK();

	bool CreateUISPK();
	void ReleaseUISPK();
	bool CreateSPKLogic();
	void ReleaseSPKLogic();
	bool CreateSPKProcedure();
	void ReleaseSPKProcedure();
    bool CreateSPKJudge();
    void ReleaseSPKJudge();
    bool CreateSPKData();
    void ReleaseSPKData();

private:
	static NwSceneSPK* ms_pInstance;
	NwUISPK* m_pUISPK;
	NwSPKLogic* m_pSPKLogic;
	NwSPKProcedure* m_pSPKProcedure;
	NwSPKJudge* m_pSPKJudge;
    NwSPKData* m_pSPKData;
};
//--------------------------------------------------------------------------------------------------
inline NwSceneSPK* NwSceneSPK::Get()
{
	return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
inline NwUISPK* NwSceneSPK::GetUISPK()
{
	return m_pUISPK;
}
//--------------------------------------------------------------------------------------------------
inline NwSPKLogic* NwSceneSPK::GetSPKLogic()
{
	return m_pSPKLogic;
}
//--------------------------------------------------------------------------------------------------
inline NwSPKProcedure* NwSceneSPK::GetSPKProcedure()
{
	return m_pSPKProcedure;
}
//--------------------------------------------------------------------------------------------------
inline NwSPKJudge* NwSceneSPK::GetSPKJudge()
{
    return m_pSPKJudge;
}
//--------------------------------------------------------------------------------------------------
inline NwSPKData* NwSceneSPK::GetSPKData()
{
    return m_pSPKData;
}
//--------------------------------------------------------------------------------------------------
#endif //_NwSceneSPK_h_
//--------------------------------------------------------------------------------------------------
