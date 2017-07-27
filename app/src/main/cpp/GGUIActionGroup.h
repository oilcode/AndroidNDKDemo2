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
    void RemoveAllAction();
	void UpdateAction(float fDeltaTime);

    void SetActionEventHandler(GGUIWindowBase* pHandler);

protected:
    GGUIActionGroup();
    ~GGUIActionGroup();
    //re-write parent function
    void ClearAction();

protected:
	GGUIWindowBase* m_pActionEventHandler;
	SoArray m_kLineArray;

};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionGroup_h_
//--------------------------------------------------------------------------------------------------
