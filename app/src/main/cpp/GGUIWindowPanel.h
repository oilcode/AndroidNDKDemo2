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
	void OnResolutionChanged(float newWidth, float newHeight);

protected:
	friend class GGUIWindowFactory;
	GGUIWindowPanel();
	virtual ~GGUIWindowPanel();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

protected:
	GGUIPanelSpaceType m_eSpaceType;
};
//------------------------------------------------------------
inline GGUIPanelSpaceType GGUIWindowPanel::GetSpaceType() const
{
	return m_eSpaceType;
}
//------------------------------------------------------------
#endif //_GGUIWindowPanel_h_
//------------------------------------------------------------
