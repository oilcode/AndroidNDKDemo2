//----------------------------------------------------------------
#ifndef _GGUIWindowText_h_
#define _GGUIWindowText_h_
//----------------------------------------------------------------
#include "GGUIWindowBase.h"
//----------------------------------------------------------------
class GGUIWindowText : public GGUIWindowBase
{
public:
	void SetColor(const GGUIColor& kColor);
	void SetFont(const char* szFont);
	void SetText(const char* szText);
	const SoTinyString& GetFont() const;
	const GGUIColor& GetColor() const;
	const char* GetText() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowText();
	virtual ~GGUIWindowText();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	virtual void RenderWindow();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

private:
	GGUIColor m_kColor;
	SoTinyString m_kFont;
	std::string m_strText;
};
//----------------------------------------------------------------
inline void GGUIWindowText::SetColor(const GGUIColor& kColor)
{
	m_kColor = kColor;
}
//----------------------------------------------------------------
inline void GGUIWindowText::SetFont(const char* szFont)
{
	m_kFont = szFont;
}
//----------------------------------------------------------------
inline void GGUIWindowText::SetText(const char* szText)
{
	if (szText != 0 && szText[0] != 0)
	{
		m_strText = szText;
	}
	else
	{
		m_strText.clear();
	}
}
//----------------------------------------------------------------
inline const GGUIColor& GGUIWindowText::GetColor() const
{
	return m_kColor;
}
//----------------------------------------------------------------
inline const SoTinyString& GGUIWindowText::GetFont() const
{
	return m_kFont;
}
//----------------------------------------------------------------
inline const char* GGUIWindowText::GetText() const
{
	return m_strText.c_str();
}
//----------------------------------------------------------------
#endif //_GGUIWindowText_h_
//----------------------------------------------------------------
