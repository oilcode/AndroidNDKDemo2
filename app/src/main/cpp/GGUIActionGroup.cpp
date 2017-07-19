//--------------------------------------------------------------------------------------------------
#include "GGUIActionGroup.h"
#include "GGUIActionBase.h"
#include "GGUIActionLine.h"
//--------------------------------------------------------------------------------------------------
GGUIActionGroup::GGUIActionGroup(GGUIWindowBase* pDestWindow)
:m_pDestWindow(pDestWindow)
{
	m_kLineArray.InitArray(sizeof(GGUIActionLine*), 10, 10);
}
//--------------------------------------------------------------------------------------------------
GGUIActionGroup::~GGUIActionGroup()
{
	ClearAllActionLine();
	m_pDestWindow = NULL;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::AddActionLine(GGUIActionLine* pLine)
{
	if (pLine)
	{
        pLine->SetActionGroup(this);
		m_kLineArray.PushBack(&pLine);
	}
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::UpdateActionGroup(float fDeltaTime)
{
	const int nCount = m_kLineArray.GetSize();
	if (nCount == 0)
	{
		return;
	}

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
			SoDelete pLine;
			m_kLineArray.RemoveAt(nIndex);
		}
		else
		{
			++nIndex;
		}
	}
}
//--------------------------------------------------------------------------------------------------
void GGUIActionGroup::ClearAllActionLine()
{
	const int nCount = m_kLineArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		GGUIActionLine* pLine = *(GGUIActionLine**)m_kLineArray.GetAt(i);
		SoDelete pLine;
	}
	m_kLineArray.ClearArray();
}
//--------------------------------------------------------------------------------------------------
