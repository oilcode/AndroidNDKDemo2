//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionMove_h_
#define _GGUIActionMove_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionMove : public GGUIActionBase
{
	friend class GGUIActionFactory;

public:
    void InitActionMove(float fDeltaX, float fDeltaY, float fTime);
	virtual void UpdateAction(float fDeltaTime);

protected:
    GGUIActionMove();
    virtual ~GGUIActionMove();
    virtual void ClearAction();

protected:
	float m_fSpeedX;
	float m_fSpeedY;
	float m_fRemainTime;
};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionMove_h_
//--------------------------------------------------------------------------------------------------
