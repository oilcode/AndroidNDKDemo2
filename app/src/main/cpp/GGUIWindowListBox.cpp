//------------------------------------------------------------
//1，本控件的子窗口的存储结构：
//   序号为0的子窗口必定是背景控件GGUIWindowImage；
//   序号为1的子窗口必定是滚动条控件GGUIWindowScrollBar；
//   从序号2开始，是条目（Item）控件GGUIWindowText；
//2，序号为N的Item，是本控件中序号为(GGUIWindowListBox_ItemStartIndex+N)的子窗口。
//------------------------------------------------------------
#include "GGUIWindowListBox.h"
#include "GGUIWindowFactory.h"
#include "GGUIWindowImage.h"
#include "GGUIWindowScrollBar.h"
#include "GGUIWindowText.h"
#include "GGUIEvent.h"
//------------------------------------------------------------
#define GGUIWindowListBox_ItemStartIndex 2
//------------------------------------------------------------
GGUIWindowListBox::GGUIWindowListBox()
:m_pImgBG(0)
,m_pScrollBar(0)
{
	m_eType = GGUIWindow_ListBox;
	InitListBox();
}
//------------------------------------------------------------
GGUIWindowListBox::~GGUIWindowListBox()
{
	//只要把指针设置成空即可。
	m_pImgBG = 0;
	m_pScrollBar = 0;
}
//----------------------------------------------------------------
void GGUIWindowListBox::ClearWindow()
{
    GGUIWindowContainer::ClearWindow();
}
//----------------------------------------------------------------
void GGUIWindowListBox::ProcessUIEvent(int nEventType, void* pParam)
{
	//switch (nEventType)
	//{
	//case GGUIEvent_Button_Clicked:
	//	{
	//		GGUIEventParam_ButtonClick* myParam = (GGUIEventParam_ButtonClick*)pParam;
	//		if (m_pBtnLeft->GetID() == myParam->nWindowID)
	//		{
	//			m_pBtnCenter->MoveDelta(-m_fRangePosDeltaPerStep, 0.0f);
	//			AdjustCenterBtnPos();
	//		}
	//		else if (m_pBtnRight->GetID() == myParam->nWindowID)
	//		{
	//			m_pBtnCenter->MoveDelta(m_fRangePosDeltaPerStep, 0.0f);
	//			AdjustCenterBtnPos();
	//		}
	//	} break;
	//case GGUIEvent_PosChangedByDrag:
	//	{
	//		AdjustCenterBtnPos();
	//	} break;
	//}
}
//----------------------------------------------------------------
void GGUIWindowListBox::SetUIEventHandler(GGUIWindowBase* pHandler)
{
	//注意，这里不是执行 GGUIWindowContainer::SetUIEventHandler ，而是执行 GGUIWindowBase::SetUIEventHandler 。
	GGUIWindowBase::SetUIEventHandler(pHandler);
	////本类要侦听每个子窗口的UIEvent。
	//m_pBtnLeft->SetUIEventHandler(this);
	//m_pBtnRight->SetUIEventHandler(this);
	//m_pBtnCenter->SetUIEventHandler(this);
}
//----------------------------------------------------------------
void GGUIWindowListBox::InitListBox()
{
	GGUIFullRect kFullRect;
	//
	kFullRect.fScaleX = 0.0f;
	kFullRect.fDeltaX = 0.0f;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fScaleW = 1.0f;
	kFullRect.fDeltaW = 0.0f;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = 0.0f;
	GGUIWindowImage* pUIImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
	pUIImage->SetFullRect(kFullRect);
	pUIImage->SetTexture("texture/mm2:Name1");
	pUIImage->SetDragEnable(true);
	AddChild(pUIImage);
	m_pImgBG = pUIImage;
	//
	//kFullRect.fScaleX = 1.0f;
	//kFullRect.fDeltaX = -10.0f;
	//kFullRect.fScaleY = 0.0f;
	//kFullRect.fDeltaY = 0.0f;
	//kFullRect.fScaleW = 0.0f;
	//kFullRect.fDeltaW = 10.0f;
	//kFullRect.fScaleH = 1.0f;
	//kFullRect.fDeltaH = 0.0f;
	//GGUIWindowScrollBar* pUIScrollBar = (GGUIWindowScrollBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ScrollBar);
	//pUIScrollBar->SetFullRect(kFullRect);
	//pUIScrollBar->SetDragEnable(false);
	//AddChild(pUIScrollBar);
	//m_pScrollBar = pUIScrollBar;
}
//----------------------------------------------------------------
void GGUIWindowListBox::AddItem(const char* szText, void* pUserData)
{

}
//----------------------------------------------------------------
void GGUIWindowListBox::InsertItem(int nItemIndex, const char* szText, void* pUserData)
{

}
//----------------------------------------------------------------
void GGUIWindowListBox::RemoveItem(int nItemIndex)
{

}
//------------------------------------------------------------
