//--------------------------------------------------------------------------------------------------
#include "GGUIActionLine.h"
#include "GGUIActionFactory.h"
//--------------------------------------------------------------------------------------------------
GGUIActionLine::GGUIActionLine()
{
    m_eActionType = GGUIAction_Line;
	m_kActionArray.InitArray(sizeof(GGUIActionBase*), 10, 10);
}
//--------------------------------------------------------------------------------------------------
GGUIActionLine::~GGUIActionLine()
{

}
//--------------------------------------------------------------------------------------------------
void GGUIActionLine::AddAction(GGUIActionBase* pAction)
{
    if (m_pDestWindow == NULL)
    {
#ifdef SoMessageBoxEnable
        SoMessageBox("GGUIActionLine::AddAction Error", "m_pDestWindow == NULL! GGUIActionLine should be added to Group, then add Action");
#endif
        return;
    }

	if (pAction)
	{
        pAction->SetDestWindow(m_pDestWindow);
		m_kActionArray.PushBack(&pAction);
        m_eLifeStep = ActionLife_Running;
	}
}
//--------------------------------------------------------------------------------------------------
void GGUIActionLine::UpdateAction(float fDeltaTime)
{
    if (m_eLifeStep != ActionLife_Running)
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

    if (m_kActionArray.GetSize() == 0)
    {
        m_eLifeStep = ActionLife_Finished;
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
void GGUIActionLine::ClearAction()
{
    GGUIActionBase::ClearAction();
    //
    const int nCount = m_kActionArray.GetSize();
    for (int i = 0; i < nCount; ++i)
    {
        GGUIActionBase* pBase = *(GGUIActionBase**)m_kActionArray.GetAt(i);
        GGUIActionFactory::Get()->DeleteUIAction(pBase->GetActionID());
    }
    m_kActionArray.ClearArray();
}
//--------------------------------------------------------------------------------------------------
