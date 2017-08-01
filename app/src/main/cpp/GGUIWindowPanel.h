//------------------------------------------------------------
#ifndef _GGUIWindowPanel_h_
#define _GGUIWindowPanel_h_
//------------------------------------------------------------
#include "GGUIWindowContainer.h"
//------------------------------------------------------------
class GGUIWindowPanel : public GGUIWindowContainer
{
public:
	void SetSpaceType(GGUIPanelSpaceType eType);
	GGUIPanelSpaceType GetSpaceType() const;
    void SetStandardWidthHeight(float fWidth, float fHeight);
	void OnResolutionChanged(float newWidth, float newHeight);

protected:
	friend class GGUIWindowFactory;
	GGUIWindowPanel();
	virtual ~GGUIWindowPanel();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
    virtual void AddChild(GGUIWindowBase* pChild);
    virtual void Notify_ParentRectChanged() const;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    void AdjustPanelRect(float fResolutionWidth, float fResolutionHeight);
    void AdjustChildRect(GGUIWindowBase* pWindow) const;

protected:
	GGUIPanelSpaceType m_eSpaceType;
    float m_fStandardWidth;
    float m_fStandardHeight;
    float m_fRealWidth;
    float m_fRealHeight;
    float m_fDeltaToResolutionWidth;
    float m_fDeltaToResolutionHeight;
};
//------------------------------------------------------------
inline GGUIPanelSpaceType GGUIWindowPanel::GetSpaceType() const
{
	return m_eSpaceType;
}
//------------------------------------------------------------
#endif //_GGUIWindowPanel_h_
//------------------------------------------------------------
