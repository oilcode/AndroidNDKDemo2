//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionMove_h_
#define _GGUIActionMove_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionMove : public GGUIActionBase
{
public:
	GGUIActionMove();
	virtual ~GGUIActionMove();
	virtual void UpdateAction(float fDeltaTime);
	virtual bool IsActionFinished() const;

	void InitActionMove(float fStartX, float fStartY, float fDestX, float fDestY, float fTime);

protected:
	float m_fCurrentX;
	float m_fCurrentY;
	float m_fDestX;
	float m_fDestY;
	float m_fSpeedX;
	float m_fSpeedY;
	float m_fMaxTime;
	float m_fAccTime;
};
//--------------------------------------------------------------------------------------------------
inline bool GGUIActionMove::IsActionFinished() const
{
	return (m_fAccTime > m_fMaxTime);
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionMove_h_
//--------------------------------------------------------------------------------------------------
