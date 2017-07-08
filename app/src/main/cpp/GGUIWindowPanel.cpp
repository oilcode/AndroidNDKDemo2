//------------------------------------------------------------
#include "GGUIWindowPanel.h"
#include "GGUIPanelManager.h"
//------------------------------------------------------------
GGUIWindowPanel::GGUIWindowPanel()
:m_eSpaceType(GGUIPanelSpace_Invalid)
{
	m_eType = GGUIWindow_Panel;
	m_pUIEventHandler = this;
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
void GGUIWindowPanel::SetSpaceType(GGUIPanelSpaceType eType)
{
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
void GGUIWindowPanel::OnResolutionChanged(float newWidth, float newHeight)
{

}
//------------------------------------------------------------
