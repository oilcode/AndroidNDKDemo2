//------------------------------------------------------------
#include "GGUIWindowContainer.h"
#include "GGUIWindowFactory.h"
//------------------------------------------------------------
GGUIWindowContainer::GGUIWindowContainer()
{
	m_eType = GGUIWindow_Container;
	m_kWindowArray.InitArray(sizeof(GGUIWindowBase*), 10, 10);
}
//------------------------------------------------------------
GGUIWindowContainer::~GGUIWindowContainer()
{
	
}
//----------------------------------------------------------------
void GGUIWindowContainer::ClearWindow()
{
	GGUIWindowBase::ClearWindow();
	RemoveAllChild();
}
//----------------------------------------------------------------
void GGUIWindowContainer::UpdateWindow(float fDeltaTime)
{
	GGUIWindowBase* pChild = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		pChild = GetChildByIndex(i);
		// 下面这个if判断务必保留，GetVisible()是内联函数，起到快速过滤的作用，
		// 不可见的窗口不会跳转到UpdateWindow()。
		if (pChild->GetVisible() == false)
		{
			continue;
		}
		pChild->UpdateWindow(fDeltaTime);
	}
}
//----------------------------------------------------------------
void GGUIWindowContainer::RenderWindow()
{
	if (GetVisible() == false)
	{
		return;
	}
	//
	GGUIWindowBase* pChild = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		pChild = GetChildByIndex(i);
		// 下面这个if判断务必保留，GetVisible()是内联函数，起到快速过滤的作用，
		// 不可见的窗口不会跳转到RenderWindow()。
		if (pChild->GetVisible() == false)
		{
			continue;
		}
		pChild->RenderWindow();
	}
}
//----------------------------------------------------------------
bool GGUIWindowContainer::InputWindow(GGUIInputMsg* pInputMsg)
{
	if (GetVisible() == false)
	{
		//派生类不要再处理input。
		return true;
	}
	if (GetInputEnable() == false)
	{
		//派生类不要再处理input。
		return true;
	}

	//先让子窗口处理input，再让自己处理input。
	//注意，子窗口的排序是倒序，即越靠近屏幕越优先处理。
	GGUIWindowBase* pChild = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = nCount-1; i >= 0; --i)
	{
		pChild = GetChildByIndex(i);
		// 下面这个if判断务必保留，GetVisible()是内联函数，起到快速过滤的作用，
		// 不可见的窗口不会跳转到InputWindow()。
		if (pChild->GetVisible() == false || pChild->GetInputEnable() == false)
		{
			continue;
		}
		pChild->InputWindow(pInputMsg);
		if (pInputMsg->bSwallowed == true)
		{
			break;
		}
	}
	//
	if (pInputMsg->bSwallowed == false)
	{
		return GGUIWindowBase::InputWindow(pInputMsg);
	}
	else
	{
		//派生类不要再处理input。
		return true;
	}
}
//------------------------------------------------------------
void GGUIWindowContainer::AddChild(GGUIWindowBase* pChild)
{
	if (pChild == 0)
	{
		return;
	}
	if (GetChildByID(pChild->GetID()) != 0)
	{
		//already exist
		return;
	}
	//
	m_kWindowArray.PushBack(&pChild);
	pChild->SetParentID(m_nID);
	pChild->OnParentRectChanged(m_kRectInAbsCoord);
	pChild->SetVisibleByReason(GGUIReasonUnvisible_Parent, GetVisible());
	pChild->SetUIEventHandler(m_pUIEventHandler);
}
//------------------------------------------------------------
void GGUIWindowContainer::RemoveChildByIndex(int nIndex)
{
	GGUIWindowBase* pChild = GetChildByIndex(nIndex);
	if (pChild)
	{
		DoRemoveChild(pChild);
		m_kWindowArray.RemoveAt(nIndex);
	}
}
//------------------------------------------------------------
void GGUIWindowContainer::RemoveChildByID(int nWindowID)
{
	const int nIndex = GetIndexByID(nWindowID);
	if (nIndex != -1)
	{
		RemoveChildByIndex(nIndex);
	}
}
//------------------------------------------------------------
void GGUIWindowContainer::RemoveAllChild()
{
	GGUIWindowFactory* pFactory = GGUIWindowFactory::Get();
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		GGUIWindowBase* pChild = GetChildByIndex(i);
		if (pChild)
		{
			DoRemoveChild(pChild);
		}
	}
	m_kWindowArray.ClearArray();
}
//------------------------------------------------------------
void GGUIWindowContainer::DoRemoveChild(GGUIWindowBase* pChild)
{
	pChild->SetParentID(-1);
	GGUIWindowFactory::Get()->DeleteUIWindow(pChild->GetID());
}
//------------------------------------------------------------
void GGUIWindowContainer::SwapChild(int nIndexA, int nIndexB)
{
	m_kWindowArray.SwapAt(nIndexA, nIndexB);
}
//------------------------------------------------------------
GGUIWindowBase* GGUIWindowContainer::GetChildByIndex(int nIndex) const
{
	void* pElement = m_kWindowArray.GetAt(nIndex);
	if (pElement)
	{
		return *((GGUIWindowBase**)pElement);
	}
	else
	{
		return 0;
	}
}
//------------------------------------------------------------
GGUIWindowBase* GGUIWindowContainer::GetChildByID(int nWindowID) const
{
	GGUIWindowBase* pWindow = 0;
	GGUIWindowBase* tempWindow = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		tempWindow = GetChildByIndex(i);
		if (tempWindow)
		{
			if (tempWindow->GetID() == nWindowID)
			{
				pWindow = tempWindow;
				break;
			}
		}
	}
	return pWindow;
}
//------------------------------------------------------------
GGUIWindowBase* GGUIWindowContainer::GetChildByName(const char* szName) const
{
	GGUIWindowBase* pWindow = 0;
	GGUIWindowBase* tempWindow = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		tempWindow = GetChildByIndex(i);
		if (tempWindow)
		{
			if (SoStrCmp(tempWindow->GetName().GetValue(), szName) == 0)
			{
				pWindow = tempWindow;
				break;
			}
		}
	}
	return pWindow;
}
//------------------------------------------------------------
GGUIWindowBase* GGUIWindowContainer::FindWindowByID(int nWindowID) const
{
	if (GetID() == nWindowID)
	{
		return (GGUIWindowBase*)this;
	}
	//
	GGUIWindowBase* pWindow = 0;
	GGUIWindowBase* tempWindow = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		tempWindow = GetChildByIndex(i);
		if (tempWindow)
		{
			if (tempWindow->GetID() == nWindowID)
			{
				pWindow = tempWindow;
				break;
			}
			if (tempWindow->GetType() == GGUIWindow_Container)
			{
				GGUIWindowContainer* pContainer = (GGUIWindowContainer*)tempWindow;
				GGUIWindowBase* pChild = pContainer->FindWindowByID(nWindowID);
				if (pChild)
				{
					pWindow = pChild;
					break;
				}
			}
		}
	}
	return pWindow;
}
//------------------------------------------------------------
GGUIWindowBase* GGUIWindowContainer::FindWindowByName(const char* szName) const
{
	if (SoStrCmp(GetName().GetValue(), szName) == 0)
	{
		return (GGUIWindowBase*)this;
	}
	//
	GGUIWindowBase* pWindow = 0;
	GGUIWindowBase* tempWindow = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		tempWindow = GetChildByIndex(i);
		if (tempWindow)
		{
			if (SoStrCmp(tempWindow->GetName().GetValue(), szName) == 0)
			{
				pWindow = tempWindow;
				break;
			}
			if (tempWindow->GetType() == GGUIWindow_Container)
			{
				GGUIWindowContainer* pContainer = (GGUIWindowContainer*)tempWindow;
				GGUIWindowBase* pChild = pContainer->FindWindowByName(szName);
				if (pChild)
				{
					pWindow = pChild;
					break;
				}
			}
		}
	}
	return pWindow;
}
//----------------------------------------------------------------
int GGUIWindowContainer::GetIndexByID(int nWindowID) const
{
	int nIndex = -1;
	GGUIWindowBase* tempWindow = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		tempWindow = GetChildByIndex(i);
		if (tempWindow)
		{
			if (tempWindow->GetID() == nWindowID)
			{
				nIndex = i;
				break;
			}
		}
	}
	return nIndex;
}
//----------------------------------------------------------------
void GGUIWindowContainer::Notify_ParentRectChanged() const
{
	GGUIWindowBase* pChild = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		pChild = GetChildByIndex(i);
		if (pChild)
		{
			pChild->OnParentRectChanged(m_kRectInAbsCoord);
		}
	}
}
//----------------------------------------------------------------
void GGUIWindowContainer::Notify_ParentVisibleChanged() const
{
	GGUIWindowBase* pChild = 0;
	const bool bVisible = GetVisible();
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		pChild = GetChildByIndex(i);
		if (pChild)
		{
			pChild->SetVisibleByReason(GGUIReasonUnvisible_Parent, bVisible);
		}
	}
}
//----------------------------------------------------------------
void GGUIWindowContainer::SetFullRect(const GGUIFullRect& kRect)
{
	GGUIWindowBase::SetFullRect(kRect);
	Notify_ParentRectChanged();
}
//----------------------------------------------------------------
void GGUIWindowContainer::SetFullRectScalePos(float fScaleX, float fScaleY)
{
	GGUIWindowBase::SetFullRectScalePos(fScaleX, fScaleY);
	Notify_ParentRectChanged();
}
//----------------------------------------------------------------
void GGUIWindowContainer::SetFullRectDeltaPos(float fDeltaX, float fDeltaY)
{
	GGUIWindowBase::SetFullRectDeltaPos(fDeltaX, fDeltaY);
	Notify_ParentRectChanged();
}
//----------------------------------------------------------------
void GGUIWindowContainer::MoveDelta(float fDeltaX, float fDeltaY)
{
	GGUIWindowBase::MoveDelta(fDeltaX, fDeltaY);
	Notify_ParentRectChanged();
}
//----------------------------------------------------------------
void GGUIWindowContainer::SetScale(float fScaleX, float fScaleY)
{
    GGUIWindowBase::SetScale(fScaleX, fScaleY);
    Notify_ParentRectChanged();
}
//----------------------------------------------------------------
void GGUIWindowContainer::ScaleDelta(float fDeltaX, float fDeltaY)
{
    GGUIWindowBase::ScaleDelta(fDeltaX, fDeltaY);
    Notify_ParentRectChanged();
}
//----------------------------------------------------------------
void GGUIWindowContainer::OnParentRectChanged(const GGUIRect& kParentRectInAbsCoord)
{
	GGUIWindowBase::OnParentRectChanged(kParentRectInAbsCoord);
	Notify_ParentRectChanged();
}
//----------------------------------------------------------------
void GGUIWindowContainer::SetUIEventHandler(GGUIWindowBase* pHandler)
{
	GGUIWindowBase::SetUIEventHandler(pHandler);
	//
	GGUIWindowBase* pChild = 0;
	const int nCount = m_kWindowArray.GetSize();
	for (int i = 0; i < nCount; ++i)
	{
		pChild = GetChildByIndex(i);
		if (pChild)
		{
			pChild->SetUIEventHandler(pHandler);
		}
	}
}
//----------------------------------------------------------------
void GGUIWindowContainer::SetVisibleByReason(souint32 uiReason, bool bVisible)
{
	const bool oldValue = GetVisible();
	GGUIWindowBase::SetVisibleByReason(uiReason, bVisible);
	const bool newValue = GetVisible();
	if (oldValue != newValue)
	{
		Notify_ParentVisibleChanged();
	}
}
//------------------------------------------------------------
