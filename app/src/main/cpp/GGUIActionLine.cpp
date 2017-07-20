//--------------------------------------------------------------------------------------------------
#include "GGUIActionLine.h"
#include "GGUIActionBase.h"
#include "GGUIActionFactory.h"
//--------------------------------------------------------------------------------------------------
GGUIActionLine::GGUIActionLine()
:m_pActionGroup(NULL)
{
	m_kActionArray.InitArray(sizeof(GGUIActionBase*), 10, 10);
}
//--------------------------------------------------------------------------------------------------
GGUIActionLine::~GGUIActionLine()
{
	ClearAllAction();
	m_pActionGroup = NULL;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionLine::AddAction(GGUIActionBase* pAction)
{
	if (pAction)
	{
        pAction->SetActionLine(this);
		m_kActionArray.PushBack(&pAction);
	}
}
//--------------------------------------------------------------------------------------------------
void GGUIActionLine::UpdateActionLine(float fDeltaTime)
{
    if (m_kActionArray.GetSize() == 0)
    {
        return;
    }

    GGUIActionBase* pBase = *(GGUIActionBase**)m_kActionArray.GetAt(0);
    pBase->UpdateAction(fDeltaTime);
    // remove the finished action
    if (pBase->IsActionFinished())
    {
        GGUIActionFactory::Get()->DeleteUIAction(pBase->GetActionID());
        m_kActionArray.RemoveAt(0);
    }

    /*
	const int nCount = m_kActionArray.GetSize();
	GGUIActionBase* pBase = NULL;
	int nIndex = 0;
	// excute action
	for (int i = 0; i < nCount; ++i)
	{
		pBase = *(GGUIActionBase**)m_kActionArray.GetAt(nIndex);
		pBase->UpdateAction(fDeltaTime);
		// remove the finished action
		if (pBase->IsActionFinished())
		{
			SoDelete pBase;
			m_kActionArray.RemoveAt(nIndex);
		}
		else
		{
			++nIndex;
		}
	}
    */
}
//--------------------------------------------------------------------------------------------------
void GGUIActionLine::ClearAllAction()
{
	const int nCount = m_kActionArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		GGUIActionBase* pBase = *(GGUIActionBase**)m_kActionArray.GetAt(i);
        GGUIActionFactory::Get()->DeleteUIAction(pBase->GetActionID());
	}
	m_kActionArray.ClearArray();
}
//--------------------------------------------------------------------------------------------------
