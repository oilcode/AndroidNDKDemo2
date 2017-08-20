//----------------------------------------------------------------
#include "GGUIWindowProcessBar.h"
#include "GGUIWindowFactory.h"
#include "GGUIWindowImage.h"
//----------------------------------------------------------------
GGUIWindowProcessBar::GGUIWindowProcessBar()
:m_pBarBG(0)
,m_pBarImage(0)
,m_fProcessValue(0.5f)
,m_fProcessValueForFlash(0.0f)
,m_fSpeedForFlash(0.0f)
,m_fRemainTimeForFlash(-1.0f)
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
    m_fProcessValue = 0.5f;
    m_fProcessValueForFlash = 0.0f;
    m_fSpeedForFlash = 0.0f;
    m_fRemainTimeForFlash = -1.0f;
}
//----------------------------------------------------------------
void GGUIWindowProcessBar::UpdateWindow(float fDeltaTime)
{
	//不需要执行父类的同名函数。
	//GGUIWindowContainer::UpdateWindow();

	if (m_fRemainTimeForFlash > 0.0f)
	{
		m_fRemainTimeForFlash -= fDeltaTime;
		//
		if (m_fRemainTimeForFlash <= 0.0f)
		{
			m_fRemainTimeForFlash = -1.0f;
			m_pBarImage->SetColor(GGUIColor_Empty);
			m_fProcessValueForFlash = m_fProcessValue;
		}
		else
		{
			m_fProcessValueForFlash += m_fSpeedForFlash * fDeltaTime;
		}
		m_pBarImage->SetFullRectScaleWH(m_fProcessValueForFlash, 1.0f);
	}
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
    pUIImage->SetImage(g_GGUI_ProcessBar_ImageBG);
	pUIImage->SetDragEnable(false);
    pUIImage->SetInputEnable(false);
	AddChild(pUIImage);
	m_pBarBG = pUIImage;
	//
	kFullRect.fScaleX = 0.0f;
	kFullRect.fDeltaX = 0.0f;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fScaleW = m_fProcessValue;
	kFullRect.fDeltaW = 0.0f;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = 0.0f;
	pUIImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
	pUIImage->SetFullRect(kFullRect);
    pUIImage->SetImage(g_GGUI_ProcessBar_ImageBar);
	pUIImage->SetDragEnable(false);
    pUIImage->SetInputEnable(false);
	AddChild(pUIImage);
	m_pBarImage = pUIImage;
}
//----------------------------------------------------------------
void GGUIWindowProcessBar::SetProcessBarStyle(const stUIProcessBarStyle* pStyle)
{
	m_pBarBG->SetImage(pStyle->szTextureBG);
	m_pBarImage->SetImage(pStyle->szTextureBar);

	GGUIFullRect kFullRect;
	kFullRect.fScaleX = 0.0f;
	kFullRect.fDeltaX = pStyle->fDeltaLeft;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = pStyle->fDeltaTop;
	kFullRect.fScaleW = m_fProcessValue;
	kFullRect.fDeltaW = - pStyle->fDeltaLeft - pStyle->fDeltaRight;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = - pStyle->fDeltaTop - pStyle->fDeltaBottom;
	m_pBarImage->SetFullRect(kFullRect);
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

	if (m_fRemainTimeForFlash > 0.0f)
	{
		//当前正在处于一个动画效果中，停止动画效果。
		m_fRemainTimeForFlash = -1.0f;
		m_pBarImage->SetColor(GGUIColor_Empty);
	}
}
//----------------------------------------------------------------
void GGUIWindowProcessBar::FlashProcessValue(float fValue)
{
	if (fValue < 0.0f)
	{
		fValue = 0.0f;
	}
	if (fValue > 1.0f)
	{
		fValue = 1.0f;
	}
	//
    float fDelta = 0.0f;
    if (m_fRemainTimeForFlash > 0.0f)
    {
        //当前正在处于一个动画效果中
        fDelta = fValue - m_fProcessValueForFlash;
    }
    else
    {
        fDelta = fValue - m_fProcessValue;
    }
    if (SoMath_IsFloatZero(fDelta))
    {
        //变化量接近0，不要做动画效果
        m_fProcessValue = fValue;
        m_pBarImage->SetFullRectScaleWH(m_fProcessValue, 1.0f);
        if (m_fRemainTimeForFlash > 0.0f)
        {
            //当前正在处于一个动画效果中，停止动画效果。
            m_fRemainTimeForFlash = -1.0f;
            m_pBarImage->SetColor(GGUIColor_Empty);
        }
    }
    else
    {
        //要做动画效果
        if (m_fRemainTimeForFlash < 0.0f)
        {
            //开始一个动画效果
            m_fProcessValueForFlash = m_fProcessValue;
            m_pBarImage->SetColor(g_GGUI_ProcessBar_FlashColor);
        }
        m_fSpeedForFlash = fDelta / GGUI_ProcessBar_FalshTime;
        m_fRemainTimeForFlash = GGUI_ProcessBar_FalshTime;
        m_fProcessValue = fValue;
    }
}
//----------------------------------------------------------------
