//--------------------------------------------------------------------------------------------------
#include "GGUIActionWait.h"
//--------------------------------------------------------------------------------------------------
GGUIActionWait::GGUIActionWait()
:m_fRemainTime(-1.0f)
{
	m_eActionType = GGUIAction_Wait;
}
//--------------------------------------------------------------------------------------------------
GGUIActionWait::~GGUIActionWait()
{

}
//--------------------------------------------------------------------------------------------------
void GGUIActionWait::InitActionWait(float fTime)
{
	// fTime must not be zero
	if (-0.01f < fTime && fTime < 0.01f )
	{
		fTime = 0.01f;
	}

	m_fRemainTime = fTime;
    m_eLifeStep = ActionLife_Running;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionWait::UpdateAction(float fDeltaTime)
{
	if (m_fRemainTime < 0.0f)
	{
		//already finished
		return;
	}

	if (m_fRemainTime > fDeltaTime)
	{
        m_fRemainTime -= fDeltaTime;
	}
	else
	{
		m_fRemainTime = -1.0f;
        m_eLifeStep = ActionLife_Finished;
	}
}
//--------------------------------------------------------------------------------------------------
void GGUIActionWait::ClearAction()
{
    GGUIActionBase::ClearAction();
    m_fRemainTime = -1.0f;
}
//--------------------------------------------------------------------------------------------------
