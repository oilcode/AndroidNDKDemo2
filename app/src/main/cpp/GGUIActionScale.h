//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionScale_h_
#define _GGUIActionScale_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionScale : public GGUIActionBase
{
	friend class GGUIActionFactory;

public:
	void InitActionScale(float fDeltaScaleX, float fDeltaScaleY, float fTime);
	virtual void UpdateAction(float fDeltaTime);

protected:
    GGUIActionScale();
    virtual ~GGUIActionScale();
    virtual void ClearAction();

protected:
	float m_fSpeedX;
	float m_fSpeedY;
	float m_fRemainTime;
};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionScale_h_
//--------------------------------------------------------------------------------------------------
