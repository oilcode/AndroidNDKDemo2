//--------------------------------------------------------------------------------------------------
#include "GGUIActionMove.h"
#include "GGUIActionLine.h"
//--------------------------------------------------------------------------------------------------
GGUIActionMove::GGUIActionMove()
:m_fCurrentX(0.0f)
,m_fCurrentY(0.0f)
,m_fDestX(0.0f)
,m_fDestY(0.0f)
,m_fSpeedX(0.0f)
,m_fSpeedY(0.0f)
,m_fMaxTime(0.0f)
,m_fAccTime(1.0f) // bigger than m_fMaxTime
{

}
//--------------------------------------------------------------------------------------------------
GGUIActionMove::~GGUIActionMove()
{

}
//--------------------------------------------------------------------------------------------------
void GGUIActionMove::UpdateAction(float fDeltaTime)
{
	if (m_fAccTime > m_fMaxTime)
	{
		//already finished
		return;
	}

	m_fAccTime += fDeltaTime;

	if (m_fAccTime < m_fMaxTime)
	{
		m_fCurrentX += m_fSpeedX * fDeltaTime;
		m_fCurrentY += m_fSpeedY * fDeltaTime;
	}
	else
	{
		// finish, m_fAccTime is bigger than m_fMaxTime
		m_fAccTime = m_fMaxTime + 1.0f;
		m_fCurrentX = m_fDestX;
		m_fCurrentY = m_fDestY;
	}

	GetDestWindow()->SetFullRectDeltaPos(m_fCurrentX, m_fCurrentY);
}
//--------------------------------------------------------------------------------------------------
void GGUIActionMove::InitActionMove(float fStartX, float fStartY, float fDestX, float fDestY, float fTime)
{
	// fTime must not be zero
	if (-0.01f < fTime && fTime < 0.01f )
	{
		fTime = 0.01f;
	}

	m_fCurrentX = fStartX;
	m_fCurrentY = fStartY;
	m_fDestX = fDestX;
	m_fDestY = fDestY;
	m_fSpeedX = (fDestX - fStartX) / fTime;
	m_fSpeedY = (fDestY - fStartY) / fTime;
	m_fMaxTime = fTime;
	m_fAccTime = 0.0f;
}
//--------------------------------------------------------------------------------------------------
