//----------------------------------------------------------------
#include "GGUIWindowProcessBar.h"
#include "GGUIWindowFactory.h"
#include "GGUIWindowImage.h"
//----------------------------------------------------------------
GGUIWindowProcessBar::GGUIWindowProcessBar()
:m_pBarBG(0)
,m_pBarImage(0)
,m_fProcessValue(0.0f)
{
	m_eType = GGUIWindow_ProcessBar;
	InitProcessBar();
}
//----------------------------------------------------------------
GGUIWindowProcessBar::~GGUIWindowProcessBar()
{
	m_pBarBG = 0;
	m_pBarImage = 0;
}
//----------------------------------------------------------------
void GGUIWindowProcessBar::ClearWindow()
{
	GGUIWindowContainer::ClearWindow();
	//m_pBarBG not change
	//m_pBarImage not change
	m_fProcessValue = 0.0f;
}
//----------------------------------------------------------------
void GGUIWindowProcessBar::InitProcessBar()
{
	GGUIFullRect kFullRect;
	GGUIWindowImage* pUIImage = 0;
	//
	kFullRect.fScaleX = 0.0f;
	kFullRect.fDeltaX = 0.0f;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fScaleW = 1.0f;
	kFullRect.fDeltaW = 0.0f;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = 0.0f;
	pUIImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
	pUIImage->SetFullRect(kFullRect);
    pUIImage->SetImage("uitexture/mm4:hud_30");
	pUIImage->SetDragEnable(false);
    pUIImage->SetInputEnable(false);
	AddChild(pUIImage);
	m_pBarBG = pUIImage;
	//
	kFullRect.fScaleX = 0.0f;
	kFullRect.fDeltaX = 0.0f;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fScaleW = 0.0f;
	kFullRect.fDeltaW = 0.0f;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = 0.0f;
	pUIImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
	pUIImage->SetFullRect(kFullRect);
    pUIImage->SetImage("uitexture/mm4:hud_10");
	pUIImage->SetDragEnable(false);
    pUIImage->SetInputEnable(false);
	AddChild(pUIImage);
	m_pBarImage = pUIImage;
}
//----------------------------------------------------------------
void GGUIWindowProcessBar::SetProcessValue(float fValue)
{
	if (fValue < 0.0f)
	{
		fValue = 0.0f;
	}
	if (fValue > 1.0f)
	{
		fValue = 1.0f;
	}
	m_fProcessValue = fValue;
	m_pBarImage->SetFullRectScaleWH(m_fProcessValue, 1.0f);
}
//----------------------------------------------------------------
