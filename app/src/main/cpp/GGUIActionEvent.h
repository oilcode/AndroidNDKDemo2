//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionEvent_h_
#define _GGUIActionEvent_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionEvent : public GGUIActionBase
{
	friend class GGUIActionFactory;

public:
    void InitActionEvent(int nEventId);
	virtual void UpdateAction(float fDeltaTime);

protected:
    GGUIActionEvent();
    virtual ~GGUIActionEvent();
    virtual void ClearAction();

protected:
	// the EventID is user defined number
    // EventID >= 0 is valid, when < 0 is invalid
	int m_nEventId;
};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionEvent_h_
//--------------------------------------------------------------------------------------------------
