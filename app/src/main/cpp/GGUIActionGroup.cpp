//--------------------------------------------------------------------------------------------------
#include "GGUIActionGroup.h"
#include "GGUIActionLine.h"
#include "GGUIActionFactory.h"
//--------------------------------------------------------------------------------------------------
GGUIActionGroup::GGUIActionGroup()
{
	m_eActionType = GGUIAction_Group;
	m_kLineArray.InitArray(sizeof(GGUIActionLine*), 10, 10);
}
//--------------------------------------------------------------------------------------------------
GGUIActionGroup::~GGUIActionGroup()
{

}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::AddActionLine(GGUIActionLine* pLine)
{
	if (pLine)
	{
        pLine->SetDestWindow(m_pDestWindow);
		m_kLineArray.PushBack(&pLine);
        m_eLifeStep = ActionLife_Running;
	}
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::RemoveAllAction()
{
    const int nCount = m_kLineArray.GetSize();
    for (int i = 0; i < nCount; ++i)
    {
        GGUIActionLine* pLine = *(GGUIActionLine**)m_kLineArray.GetAt(i);
        GGUIActionFactory::Get()->DeleteUIAction(pLine->GetActionID());
    }
    m_kLineArray.ClearArray();
    m_eLifeStep = ActionLife_Finished;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::UpdateAction(float fDeltaTime)
{
	if (m_eLifeStep == ActionLife_Finished)
	{
		return;
	}

    const int nCount = m_kLineArray.GetSize();
	GGUIActionLine* pLine = NULL;
	int nIndex = 0;
	// excute action
	for (int i = 0; i < nCount; ++i)
	{
		pLine = *(GGUIActionLine**)m_kLineArray.GetAt(nIndex);
		pLine->UpdateAction(fDeltaTime);
		// remove the finished action
		if (pLine->IsActionFinished())
		{
            GGUIActionFactory::Get()->DeleteUIAction(pLine->GetActionID());
			m_kLineArray.RemoveAt(nIndex);
		}
		else
		{
			++nIndex;
		}
	}

    if (m_kLineArray.GetSize() == 0)
    {
        m_eLifeStep = ActionLife_Finished;
    }

    GGUIActionFactory::Get()->DispatchActionEvent(m_pDestWindow);
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::ClearAction()
{
    //first RemoveAllAction() second ClearAction()
    //then m_eLifeStep is the correct value
    RemoveAllAction();
	GGUIActionBase::ClearAction();
}
//--------------------------------------------------------------------------------------------------
