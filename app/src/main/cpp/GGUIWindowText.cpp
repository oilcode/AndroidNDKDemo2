//----------------------------------------------------------------
#include "GGUIWindowText.h"
#include "GGUIRenderHelp.h"
//----------------------------------------------------------------
GGUIWindowText::GGUIWindowText()
:m_kColor(GGUIColor_White)
,m_kFont(g_GGUI_ButtonText_Font)
{
	m_eType = GGUIWindow_Text;
}
//----------------------------------------------------------------
GGUIWindowText::~GGUIWindowText()
{

}
//----------------------------------------------------------------
void GGUIWindowText::ClearWindow()
{
	GGUIWindowBase::ClearWindow();
	m_kColor = GGUIColor_White;
	m_kFont.Clear();
	m_strText.clear();
}
//----------------------------------------------------------------
void GGUIWindowText::RenderWindow()
{
	GGUIRenderHelp_SimpleText(m_strText.c_str(), m_kRectInAbsCoord, GGUITextAlignX_Left, GGUITextAlignY_Center, m_kFont, m_kColor);
}
//----------------------------------------------------------------
