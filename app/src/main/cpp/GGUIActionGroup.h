//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionGroup_h_
#define _GGUIActionGroup_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionLine;
//--------------------------------------------------------------------------------------------------
class GGUIActionGroup : public GGUIActionBase
{
	friend class GGUIActionFactory;
public:
	void AddActionLine(GGUIActionLine* pLine);
    void ClearAllAction();
	void UpdateActionGroup(float fDeltaTime);

    void SetDestWindow(GGUIWindowBase* pWindow);
	GGUIWindowBase* GetDestWindow() const;

protected:
    GGUIActionGroup();
    ~GGUIActionGroup();
    //re-write parent function
    void ClearAction();

protected:
	GGUIWindowBase* m_pDestWindow;
	SoArray m_kLineArray;
};
//--------------------------------------------------------------------------------------------------
inline void GGUIActionGroup::SetDestWindow(GGUIWindowBase* pWindow)
{
    m_pDestWindow = pWindow;
	//m_pActionLine must not be NULL
    SetActionLine((GGUIActionLine*)1);
}
//--------------------------------------------------------------------------------------------------
inline GGUIWindowBase* GGUIActionGroup::GetDestWindow() const
{
	return m_pDestWindow;
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionGroup_h_
//--------------------------------------------------------------------------------------------------
