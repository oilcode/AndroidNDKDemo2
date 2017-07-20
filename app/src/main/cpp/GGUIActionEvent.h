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
	virtual void UpdateAction(float fDeltaTime);
	virtual bool IsActionFinished() const;

	void InitActionEvent(int nEventId);

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
inline bool GGUIActionEvent::IsActionFinished() const
{
	return (m_nEventId < 0);
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionEvent_h_
//--------------------------------------------------------------------------------------------------
