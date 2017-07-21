//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionLine_h_
#define _GGUIActionLine_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionGroup;
//--------------------------------------------------------------------------------------------------
class GGUIActionLine : public GGUIActionBase
{
    friend class GGUIActionFactory;
public:
	void AddAction(GGUIActionBase* pAction);
	void UpdateActionLine(float fDeltaTime);
	bool IsActionLineFinished() const;

	void SetActionGroup(GGUIActionGroup* pGroup);
	GGUIActionGroup* GetActionGroup() const;
	GGUIWindowBase* GetDestWindow() const;

protected:
    GGUIActionLine();
    ~GGUIActionLine();
    //re-write parent function
    void ClearAction();

protected:
	GGUIActionGroup* m_pActionGroup;
	SoArray m_kActionArray;
};
//--------------------------------------------------------------------------------------------------
inline bool GGUIActionLine::IsActionLineFinished() const
{
	return (m_kActionArray.GetSize() == 0);
}
//--------------------------------------------------------------------------------------------------
inline void GGUIActionLine::SetActionGroup(GGUIActionGroup* pGroup)
{
	m_pActionGroup = pGroup;
}
//--------------------------------------------------------------------------------------------------
inline GGUIActionGroup* GGUIActionLine::GetActionGroup() const
{
	return m_pActionGroup;
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionLine_h_
//--------------------------------------------------------------------------------------------------
