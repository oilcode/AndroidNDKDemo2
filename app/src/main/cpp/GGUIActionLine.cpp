//--------------------------------------------------------------------------------------------------
#include "GGUIActionLine.h"
#include "GGUIActionMove.h"
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
	const int nCount = m_kActionArray.GetSize();
	GGUIActionMove* pBase = NULL;
	int nIndex = 0;
	// excute action
	for (int i = 0; i < nCount; ++i)
	{
		pBase = *(GGUIActionMove**)m_kActionArray.GetAt(nIndex);
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
}
//--------------------------------------------------------------------------------------------------
void GGUIActionLine::ClearAllAction()
{
	const int nCount = m_kActionArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		GGUIActionBase* pBase = *(GGUIActionBase**)m_kActionArray.GetAt(i);
		SoDelete pBase;
	}
	m_kActionArray.ClearArray();
}
//--------------------------------------------------------------------------------------------------
