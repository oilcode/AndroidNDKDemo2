//------------------------------------------------------------
#ifndef _GGUIWindowButton_h_
#define _GGUIWindowButton_h_
//------------------------------------------------------------
#include "GGUIWindowBase.h"
//------------------------------------------------------------
struct stInputEvent;
//------------------------------------------------------------
class GGUIWindowButton : public GGUIWindowBase
{
public:
	//--szTexture "ImagesetName:RectName"
	void SetTexture(const char* szTexture);
	int GetImagesetIndex() const;
	int GetImageRectIndex() const;

	void SetButtonState(GGUIButtonState eState);
	GGUIButtonState GetButtonState() const;

	void SetText(const char* szText);
	const char* GetText() const;

protected:
	friend class GGUIWindowFactory;
	friend class GGUIWindowScrollBar;
	GGUIWindowButton();
	virtual ~GGUIWindowButton();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	virtual void RenderWindow();
	virtual bool InputWindow(stInputEvent* pInputEvent);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
private:
	int m_nImagesetIndex;
	int m_nImageRectIndex;
	GGUIButtonState m_eButtonState;
	std::string m_strText;
};
//----------------------------------------------------------------
inline int GGUIWindowButton::GetImagesetIndex() const
{
	return m_nImagesetIndex;
}
//----------------------------------------------------------------
inline int GGUIWindowButton::GetImageRectIndex() const
{
	return m_nImageRectIndex;
}
//----------------------------------------------------------------
inline void GGUIWindowButton::SetButtonState(GGUIButtonState eState)
{
	m_eButtonState = eState;
}
//------------------------------------------------------------
inline GGUIButtonState GGUIWindowButton::GetButtonState() const
{
	return m_eButtonState;
}
//----------------------------------------------------------------
inline const char* GGUIWindowButton::GetText() const
{
	return m_strText.c_str();
}
//------------------------------------------------------------
#endif //_GGUIWindowButton_h_
//------------------------------------------------------------
