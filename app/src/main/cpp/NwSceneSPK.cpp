//--------------------------------------------------------------------------------------------------
#include "NwSceneSPK.h"
#include "NwUISPK.h"
#include "NwSPKLogic.h"
#include "NwSPKProcedure.h"
//--------------------------------------------------------------------------------------------------
NwSceneSPK* NwSceneSPK::ms_pInstance = NULL;
//--------------------------------------------------------------------------------------------------
bool NwSceneSPK::CreateSceneSPK()
{
	bool br = true;
	if (ms_pInstance == NULL)
	{
		ms_pInstance = SoNew NwSceneSPK;
		if (ms_pInstance && ms_pInstance->InitSceneSPK())
		{
			br = true;
		}
		else
		{
			ReleaseSceneSPK();
			br = false;
		}
	}
	return br;
}
//--------------------------------------------------------------------------------------------------
void NwSceneSPK::ReleaseSceneSPK()
{
	if (ms_pInstance)
	{
		ms_pInstance->ClearSceneSPK();
		SoDelete ms_pInstance;
		ms_pInstance = NULL;
	}
}
//--------------------------------------------------------------------------------------------------
NwSceneSPK::NwSceneSPK()
:m_pUISPK(NULL)
,m_pSPKLogic(NULL)
,m_pSPKProcedure(NULL)
{

}
//--------------------------------------------------------------------------------------------------
NwSceneSPK::~NwSceneSPK()
{

}
//--------------------------------------------------------------------------------------------------
bool NwSceneSPK::InitSceneSPK()
{
	if (CreateUISPK() == false)
	{
		return false;
	}
	if (CreateSPKLogic() == false)
	{
		return false;
	}
	if (CreateSPKProcedure() == false)
	{
		return false;
	}
	return true;
}
//--------------------------------------------------------------------------------------------------
void NwSceneSPK::ClearSceneSPK()
{
	ReleaseUISPK();
	ReleaseSPKLogic();
	ReleaseSPKProcedure();
}
//--------------------------------------------------------------------------------------------------
void NwSceneSPK::StartSPK()
{
	m_pSPKLogic->ResetSPKLogic();
	m_pSPKProcedure->StartSPKProcedure();
}
//--------------------------------------------------------------------------------------------------
void NwSceneSPK::UpdateSceneSPK(float fDeltaTime)
{
	m_pSPKProcedure->UpdateSPKProcedure(fDeltaTime);
}
//--------------------------------------------------------------------------------------------------
bool NwSceneSPK::CreateUISPK()
{
	bool br = true;
	if (m_pUISPK == NULL)
	{
		m_pUISPK = SoNew NwUISPK;
		if (m_pUISPK && m_pUISPK->InitUISPK())
		{
			br = true;
		}
		else
		{
			ReleaseUISPK();
			br = false;
		}
	}
	return br;
}
//--------------------------------------------------------------------------------------------------
void NwSceneSPK::ReleaseUISPK()
{
	if (m_pUISPK)
	{
		m_pUISPK->ClearUISPK();
		SoDelete m_pUISPK;
		m_pUISPK = NULL;
	}
}
//--------------------------------------------------------------------------------------------------
bool NwSceneSPK::CreateSPKLogic()
{
	bool br = true;
	if (m_pSPKLogic == NULL)
	{
		m_pSPKLogic = SoNew NwSPKLogic;
		if (m_pSPKLogic == NULL)
		{
			br = false;
		}
	}
	return br;
}
//--------------------------------------------------------------------------------------------------
void NwSceneSPK::ReleaseSPKLogic()
{
	if (m_pSPKLogic)
	{
		SoDelete m_pSPKLogic;
		m_pSPKLogic = NULL;
	}
}
//--------------------------------------------------------------------------------------------------
bool NwSceneSPK::CreateSPKProcedure()
{
	bool br = true;
	if (m_pSPKProcedure == NULL)
	{
		m_pSPKProcedure = SoNew NwSPKProcedure;
		if (m_pSPKProcedure == NULL)
		{
			br = false;
		}
	}
	return br;
}
//--------------------------------------------------------------------------------------------------
void NwSceneSPK::ReleaseSPKProcedure()
{
	if (m_pSPKProcedure)
	{
		SoDelete m_pSPKProcedure;
		m_pSPKProcedure = NULL;
	}
}
//--------------------------------------------------------------------------------------------------

