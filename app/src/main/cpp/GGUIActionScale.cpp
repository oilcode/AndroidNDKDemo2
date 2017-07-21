//--------------------------------------------------------------------------------------------------
#include "GGUIActionScale.h"
//--------------------------------------------------------------------------------------------------
GGUIActionScale::GGUIActionScale()
:m_fSpeedX(0.0f)
,m_fSpeedY(0.0f)
,m_fRemainTime(-1.0f)
{
	m_eActionType = GGUIAction_Scale;
}
//--------------------------------------------------------------------------------------------------
GGUIActionScale::~GGUIActionScale()
{

}
//--------------------------------------------------------------------------------------------------
void GGUIActionScale::ClearAction()
{
	GGUIActionBase::ClearAction();
	m_fSpeedX = 0.0f;
	m_fSpeedY = 0.0f;
	m_fRemainTime = -1.0f;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionScale::UpdateAction(float fDeltaTime)
{
	if (m_fRemainTime < 0.0f)
	{
		//already finished
		return;
	}

	float fDeltaX = 0.0f;
	float fDeltaY = 0.0f;

	if (m_fRemainTime > fDeltaTime)
	{
		fDeltaX = m_fSpeedX * fDeltaTime;
		fDeltaY = m_fSpeedY * fDeltaTime;
        m_fRemainTime -= fDeltaTime;
	}
	else
	{
        fDeltaX = m_fRemainTime * fDeltaTime;
        fDeltaY = m_fRemainTime * fDeltaTime;
		m_fRemainTime = -1.0f;
	}

	GetDestWindow()->ScaleDelta(fDeltaX, fDeltaY);
}
//--------------------------------------------------------------------------------------------------
void GGUIActionScale::InitActionScale(float fDeltaScaleX, float fDeltaScaleY, float fTime)
{
	// fTime must not be zero
	if (-0.01f < fTime && fTime < 0.01f )
	{
		fTime = 0.01f;
	}

	m_fSpeedX = fDeltaScaleX / fTime;
	m_fSpeedY = fDeltaScaleY / fTime;
    m_fRemainTime = fTime;
}
//--------------------------------------------------------------------------------------------------
