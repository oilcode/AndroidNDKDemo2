//--------------------------------------------------------------------------------------------------
#include "GGUIActionGroup.h"
#include "GGUIActionLine.h"
#include "GGUIActionFactory.h"
//--------------------------------------------------------------------------------------------------
GGUIActionGroup::GGUIActionGroup()
:m_pDestWindow(NULL)
{
	m_eActionType = GGUIAction_Group;
	m_kLineArray.InitArray(sizeof(GGUIActionLine*), 10, 10);
}
//--------------------------------------------------------------------------------------------------
GGUIActionGroup::~GGUIActionGroup()
{

}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::ClearAction()
{
    GGUIActionBase::ClearAction();
    ClearAllAction();
	m_pDestWindow = NULL;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::AddActionLine(GGUIActionLine* pLine)
{
	if (pLine)
	{
        pLine->SetActionLine(pLine);
        pLine->SetActionGroup(this);
		m_kLineArray.PushBack(&pLine);
	}
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::ClearAllAction()
{
    const int nCount = m_kLineArray.GetSize();
    for (int i = 0; i < nCount; ++i)
    {
        GGUIActionLine* pLine = *(GGUIActionLine**)m_kLineArray.GetAt(i);
        GGUIActionFactory::Get()->DeleteUIAction(pLine->GetActionID());
    }
    m_kLineArray.ClearArray();
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::UpdateActionGroup(float fDeltaTime)
{
	if (m_kLineArray.GetSize() == 0)
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
		pLine->UpdateActionLine(fDeltaTime);
		// remove the finished action
		if (pLine->IsActionLineFinished())
		{
            GGUIActionFactory::Get()->DeleteUIAction(pLine->GetActionID());
			m_kLineArray.RemoveAt(nIndex);
		}
		else
		{
			++nIndex;
		}
	}

    GGUIActionFactory::Get()->DispatchActionEvent(m_pDestWindow);
}
//--------------------------------------------------------------------------------------------------
