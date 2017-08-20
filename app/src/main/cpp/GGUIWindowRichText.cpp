//----------------------------------------------------------------
#include "GGUIWindowRichText.h"
#include "GGUIRichTextParse.h"
#include "GGUIRenderHelp.h"
//----------------------------------------------------------------
GGUIWindowRichText::GGUIWindowRichText()
:m_bNeedPause(false)
{
    m_eType = GGUIWindow_RichText;
}
//----------------------------------------------------------------
GGUIWindowRichText::~GGUIWindowRichText()
{

}
//----------------------------------------------------------------
void GGUIWindowRichText::ClearWindow()
{
    GGUIWindowBase::ClearWindow();
    ClearRichText();
}
//----------------------------------------------------------------
void GGUIWindowRichText::RenderWindow()
{
    if (m_bNeedPause)
    {
        m_bNeedPause = false;
        m_kRichText.SetMaxWidth(m_kRectInAbsCoord.w);
        m_kRichText.SetMaxHeight(m_kRectInAbsCoord.h);
        GGUIRichText_Pause(m_strText.c_str(), &m_kRichText);
    }
    if (m_kRichText.GetTextChunkCount() > 0)
    {
        GGUIRenderHelp_RichText(&m_kRichText, m_kRectInAbsCoord.x, m_kRectInAbsCoord.y);
    }
}
//----------------------------------------------------------------
void GGUIWindowRichText::SetRichText(const char* szText)
{
	if (szText == 0 || szText[0] == 0)
	{
		ClearRichText();
		return;
	}

	m_strText = szText;
	m_bNeedPause = true;
}
//----------------------------------------------------------------
void GGUIWindowRichText::ClearRichText()
{
    m_kRichText.ClearRichTextStruct();
	m_strText.clear();
	m_bNeedPause = false;
}
//----------------------------------------------------------------
