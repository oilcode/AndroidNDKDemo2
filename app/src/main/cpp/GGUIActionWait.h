//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionWait_h_
#define _GGUIActionWait_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionWait : public GGUIActionBase
{
	friend class GGUIActionFactory;

public:
    void InitActionWait(float fTime);
	virtual void UpdateAction(float fDeltaTime);

protected:
	GGUIActionWait();
    virtual ~GGUIActionWait();
    virtual void ClearAction();

protected:
	float m_fRemainTime;
};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionWait_h_
//--------------------------------------------------------------------------------------------------
