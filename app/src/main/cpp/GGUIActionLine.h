//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionLine_h_
#define _GGUIActionLine_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionLine : public GGUIActionBase
{
    friend class GGUIActionFactory;

public:
	void AddAction(GGUIActionBase* pAction);
    void UpdateAction(float fDeltaTime);

protected:
    GGUIActionLine();
    ~GGUIActionLine();
    //re-write parent function
    void ClearAction();

protected:
	SoArray m_kActionArray;
};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionLine_h_
//--------------------------------------------------------------------------------------------------
