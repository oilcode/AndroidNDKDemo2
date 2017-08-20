//----------------------------------------------------------------
#ifndef _GGUIWindowRichText_h_
#define _GGUIWindowRichText_h_
//----------------------------------------------------------------
#include "GGUIWindowBase.h"
#include "GGUIRichTextStruct.h"
//----------------------------------------------------------------
class GGUIWindowRichText : public GGUIWindowBase
{
public:
	void SetRichText(const char* szText);
	void ClearRichText();
	bool IsNeedPause() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowRichText();
	virtual ~GGUIWindowRichText();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
    virtual void RenderWindow();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

private:
	GGUIRichTextStruct m_kRichText;
	std::string m_strText;
	bool m_bNeedPause;
};
//----------------------------------------------------------------
inline bool GGUIWindowRichText::IsNeedPause() const
{
	return m_bNeedPause;
}
//----------------------------------------------------------------
#endif //_GGUIWindowRichText_h_
//----------------------------------------------------------------
