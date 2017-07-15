//----------------------------------------------------------------
#include "GGUIWindowButton.h"
#include "GGUIRenderHelp.h"
#include "GGUIEvent.h"
//----------------------------------------------------------------
GGUIWindowButton::GGUIWindowButton()
:m_nImagesetIndex(-1)
,m_nImageRectIndex(-1)
,m_eButtonState(GGUIButtonState_Normal)
{
	m_eType = GGUIWindow_Button;
}
//----------------------------------------------------------------
GGUIWindowButton::~GGUIWindowButton()
{

}
//----------------------------------------------------------------
void GGUIWindowButton::ClearWindow()
{
	GGUIWindowBase::ClearWindow();
	m_nImagesetIndex = -1;
	m_nImageRectIndex = -1;
	m_eButtonState = GGUIButtonState_Normal;
}
//----------------------------------------------------------------
void GGUIWindowButton::RenderWindow()
{
	if (m_nImagesetIndex == -1)
	{
		return;
	}
	if (m_nImageRectIndex == -1)
	{
		return;
	}
	//
	float fDeltaX_BtnState = 0.0f;
	float fDeltaY_BtnState = 0.0f;
	float fColorR_BtnState = 0.0f;
	float fColorG_BtnState = 0.0f;
	float fColorB_BtnState = 0.0f;
	float fColorA_BtnState = 0.0f;
	if (m_eButtonState == GGUIButtonState_Hover)
	{
		fColorR_BtnState = GGUI_ButtonStateHover_ColorR;
		fColorG_BtnState = GGUI_ButtonStateHover_ColorG;
		fColorB_BtnState = GGUI_ButtonStateHover_ColorB;
		fColorA_BtnState = GGUI_ButtonStateHover_ColorA;
		fDeltaX_BtnState = GGUI_ButtonStateHover_DeltaX;
		fDeltaY_BtnState = GGUI_ButtonStateHover_DeltaY;
	}
	else if (m_eButtonState == GGUIButtonState_Push)
	{
		fColorR_BtnState = GGUI_ButtonStatePush_ColorR;
		fColorG_BtnState = GGUI_ButtonStatePush_ColorG;
		fColorB_BtnState = GGUI_ButtonStatePush_ColorB;
		fColorA_BtnState = GGUI_ButtonStatePush_ColorA;
		fDeltaX_BtnState = GGUI_ButtonStatePush_DeltaX;
		fDeltaY_BtnState = GGUI_ButtonStatePush_DeltaY;
	}
	//
	GGUIRect kAbsRect(m_kRectInAbsCoord.x + fDeltaX_BtnState, m_kRectInAbsCoord.y + fDeltaY_BtnState, m_kRectInAbsCoord.w, m_kRectInAbsCoord.h);
	GGUIColor kColor(fColorR_BtnState, fColorG_BtnState, fColorB_BtnState, fColorA_BtnState);
	GGUIRenderHelp_SimpleImage(m_nImagesetIndex, m_nImageRectIndex, kAbsRect, kColor);
    //
	if (m_strText.empty() == false)
	{
		GGUIRenderHelp_SimpleText(m_strText.c_str(), kAbsRect, GGUITextAlignX_Center, GGUITextAlignY_Center, g_GGUI_ButtonText_Font, g_GGUI_ButtonText_Color);
	}
}
//----------------------------------------------------------------
bool GGUIWindowButton::InputWindow(GGUIInputMsg* pInputMsg)
{
	if (GGUIWindowBase::InputWindow(pInputMsg))
	{
		//派生类不要再处理input。
		return true;
	}

	//下面的逻辑会做两件事情：
	//1，更新按钮的显示状态；
	//2，判断按钮是否被按下；
	bool bShouldSendEvent_ButtonClick = false;
	const GGUIButtonState curBtnState = m_eButtonState;
	
#if (SoTargetPlatform == SoPlatform_Windows)
	if (pInputEvent->theEvent == InputEvent_MouseMove)
	{
		if (m_bCursorIsInside)
		{
			if (curBtnState == GGUIButtonState_Normal)
			{
				m_eButtonState = GGUIButtonState_Hover;
			}
		}
		else
		{
			if (curBtnState != GGUIButtonState_Normal)
			{
				m_eButtonState = GGUIButtonState_Normal;
			}
		}
	}
#elif (SoTargetPlatform == SoPlatform_Android)
	if (pInputMsg->theType == GGUIInputMsg_TouchMove)
	{
		if (m_bCursorIsInside == false)
		{
			if (curBtnState != GGUIButtonState_Normal)
			{
				m_eButtonState = GGUIButtonState_Normal;
			}
		}
	}
#endif

	
#if (SoTargetPlatform == SoPlatform_Windows)
	else if (pInputEvent->theEvent == InputEvent_Down && pInputEvent->theKey == InputKey_LMouse)
	{
		if (curBtnState == GGUIButtonState_Hover)
		{
			m_eButtonState = GGUIButtonState_Push;
		}
	}
#elif (SoTargetPlatform == SoPlatform_Android)
    else if (pInputMsg->theType == GGUIInputMsg_TouchDown)
	{
		if (m_bCursorIsInside)
		{
			m_eButtonState = GGUIButtonState_Push;
		}
	}
#endif

#if (SoTargetPlatform == SoPlatform_Windows)
	else if (pInputEvent->theEvent == InputEvent_Up && pInputEvent->theKey == InputKey_LMouse)
	{
		if (curBtnState == GGUIButtonState_Push)
		{
			m_eButtonState = GGUIButtonState_Hover;
			bShouldSendEvent_ButtonClick = true;
		}
	}
#elif (SoTargetPlatform == SoPlatform_Android)
    else if (pInputMsg->theType == GGUIInputMsg_TouchUp)
	{
		if (m_bCursorIsInside)
		{
			m_eButtonState = GGUIButtonState_Normal;
			bShouldSendEvent_ButtonClick = true;
		}
	}
#endif

	//
	if (bShouldSendEvent_ButtonClick)
	{
		GGUIEventParam_Button_Clicked kParam;
		kParam.szWindowName = m_kName.GetValue();
		kParam.nWindowID = m_nID;
		m_pUIEventHandler->ProcessUIEvent(GGUIEvent_Button_Clicked, &kParam);
		//派生类不要再处理input。
		return true;
	}

	return false;
}
//----------------------------------------------------------------
void GGUIWindowButton::SetImage(const char* szImage)
{
	GGUIFunc_GetImagesetIndexRectIndex(szImage, &m_nImagesetIndex, &m_nImageRectIndex);
}
//----------------------------------------------------------------
void GGUIWindowButton::SetText(const char* szText)
{
	if (szText)
	{
		m_strText = szText;
	}
	else
	{
		m_strText.clear();
	}
}
//----------------------------------------------------------------
