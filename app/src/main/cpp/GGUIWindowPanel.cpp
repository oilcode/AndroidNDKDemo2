//------------------------------------------------------------
#include "GGUIWindowPanel.h"
#include "GGUIPanelManager.h"
//------------------------------------------------------------
GGUIWindowPanel::GGUIWindowPanel()
:m_eSpaceType(GGUIPanelSpace_Invalid)
,m_fStandardWidth(300.0f) //must not be zero
,m_fStandardHeight(300.0f) //must not be zero
,m_fRealWidth(300.0f)
,m_fRealHeight(300.0f)
,m_fDeltaToResolutionWidth(0.0f)
,m_fDeltaToResolutionHeight(0.0f)
{
    m_nID = -2;
	m_eType = GGUIWindow_Panel;
	m_pUIEventHandler = this;
    m_bAdjustChildRectWhenAddChild = false;
}
//------------------------------------------------------------
GGUIWindowPanel::~GGUIWindowPanel()
{

}
//------------------------------------------------------------
void GGUIWindowPanel::ClearWindow()
{
	GGUIWindowContainer::ClearWindow();
	SetSpaceType(GGUIPanelSpace_Invalid);
}
//------------------------------------------------------------
void GGUIWindowPanel::AddChild(GGUIWindowBase* pChild)
{
    if (pChild == 0)
    {
        return;
    }

    GGUIWindowContainer::AddChild(pChild);
    AdjustChildRect(pChild);
}
//----------------------------------------------------------------
void GGUIWindowPanel::Notify_ParentRectChanged() const
{
    const int nCount = GetChildCount();
    if (nCount == 0)
    {
        return;
    }

    GGUIWindowBase* pChild = 0;
    for (int i = 0; i < nCount; ++i)
    {
        pChild = GetChildByIndex(i);
        if (pChild)
        {
            AdjustChildRect(pChild);
        }
    }
}
//------------------------------------------------------------
void GGUIWindowPanel::SetSpaceType(GGUIPanelSpaceType eType)
{
    if (m_eSpaceType == eType)
    {
        return;
    }

	if (m_eSpaceType != GGUIPanelSpace_Invalid)
	{
		GGUIPanelManager::Get()->RemoveUIPanel(this, m_eSpaceType);
	}
	m_eSpaceType = eType;
	if (m_eSpaceType != GGUIPanelSpace_Invalid)
	{
		GGUIPanelManager::Get()->AddUIPanel(this, m_eSpaceType);
	}
}
//------------------------------------------------------------
void GGUIWindowPanel::SetStandardWidthHeight(float fWidth, float fHeight)
{
    m_fStandardWidth = fWidth;
    m_fStandardHeight = fHeight;
    const float fResolutionWidth = GGUIFunc_GetResolutionWidth();
    const float fResolutionHeight = GGUIFunc_GetResolutionHeight();
    AdjustPanelRect(fResolutionWidth, fResolutionHeight);
}
//------------------------------------------------------------
void GGUIWindowPanel::OnResolutionChanged(float newWidth, float newHeight)
{
    AdjustPanelRect(newWidth, newHeight);
}
//------------------------------------------------------------
void GGUIWindowPanel::AdjustPanelRect(float fResolutionWidth, float fResolutionHeight)
{
    float fScaleX = fResolutionWidth / m_fStandardWidth;
    float fScaleY = fResolutionHeight / m_fStandardHeight;
    if (fScaleX < fScaleY)
    {
        m_fRealWidth = fResolutionWidth;
        m_fRealHeight = m_fStandardHeight * fScaleX;
        m_fDeltaToResolutionWidth = 0.0f;
        m_fDeltaToResolutionHeight = fResolutionHeight - m_fRealHeight;
    }
    else
    {
        m_fRealWidth = m_fStandardWidth * fScaleY;
        m_fRealHeight = fResolutionHeight;
        m_fDeltaToResolutionWidth = fResolutionWidth - m_fRealWidth;
        m_fDeltaToResolutionHeight = 0.0f;
    }

    GGUIFullRect kFullRect;
    kFullRect.fDeltaW = m_fRealWidth;
    kFullRect.fDeltaH = m_fRealHeight;
    SetFullRect(kFullRect);
}
//------------------------------------------------------------
void GGUIWindowPanel::AdjustChildRect(GGUIWindowBase* pWindow) const
{
    GGUIRect kPanelRectInAbsCoord;
    kPanelRectInAbsCoord.x = m_kRectInAbsCoord.x;
    kPanelRectInAbsCoord.y = m_kRectInAbsCoord.y;
    kPanelRectInAbsCoord.w = m_kRectInAbsCoord.w;
    kPanelRectInAbsCoord.h = m_kRectInAbsCoord.h;

    const GGUIFullRect& kFullRect = pWindow->GetFullRect();

    if (SoMath_IsFloatZero(m_fDeltaToResolutionWidth) == false)
    {
        switch (kFullRect.eHorzAttachType)
        {
            case GGUIWindowHorzAttach_Left:
            {
                //kPanelRectInAbsCoord.x += 0.0f;
                //do nothing
            } break;
            case GGUIWindowHorzAttach_Center:
            {
                kPanelRectInAbsCoord.x += m_fDeltaToResolutionWidth * 0.5f;
            } break;
            case GGUIWindowHorzAttach_Right:
            {
                kPanelRectInAbsCoord.x += m_fDeltaToResolutionWidth;
            } break;
            default:
                break;
        }
    }

    if (SoMath_IsFloatZero(m_fDeltaToResolutionHeight) == false)
    {
        switch (kFullRect.eVertAttachType)
        {
            case GGUIWindowVertAttach_Top:
            {
                //kPanelRectInAbsCoord.y += 0.0f;
                //do nothing
            } break;
            case GGUIWindowVertAttach_Center:
            {
                kPanelRectInAbsCoord.y += m_fDeltaToResolutionHeight * 0.5f;
            } break;
            case GGUIWindowVertAttach_Bottom:
            {
                kPanelRectInAbsCoord.y += m_fDeltaToResolutionHeight;
            } break;
            default:
                break;
        }
    }

    pWindow->OnParentRectChanged(kPanelRectInAbsCoord);
}
//------------------------------------------------------------
