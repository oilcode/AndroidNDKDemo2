//--------------------------------------------------------------------------------------------------
#include "GGUIActionEvent.h"
#include "GGUIActionFactory.h"
//--------------------------------------------------------------------------------------------------
GGUIActionEvent::GGUIActionEvent()
:m_nEventId(-1)
{
	m_eActionType = GGUIAction_Event;
}
//--------------------------------------------------------------------------------------------------
GGUIActionEvent::~GGUIActionEvent()
{

}
//--------------------------------------------------------------------------------------------------
void GGUIActionEvent::ClearAction()
{
	GGUIActionBase::ClearAction();
    m_nEventId = -1;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionEvent::UpdateAction(float fDeltaTime)
{
	if (m_nEventId < 0)
	{
		//already finished
		return;
	}

    GGUIActionFactory::Get()->AddActionEvent(m_nEventId);
    m_nEventId = -1;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionEvent::InitActionEvent(int nEventId)
{
	m_nEventId = nEventId;
}
//--------------------------------------------------------------------------------------------------
