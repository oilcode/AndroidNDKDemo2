//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionLine_h_
#define _GGUIActionLine_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIBaseInclude.h"
#include "GGUIActionGroup.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionBase;
class GGUIWindowBase;
//--------------------------------------------------------------------------------------------------
class GGUIActionLine
{
public:
	GGUIActionLine();
	~GGUIActionLine();

	void AddAction(GGUIActionBase* pAction);
	void UpdateActionLine(float fDeltaTime);
	bool IsActionLineFinished() const;

	void SetActionGroup(GGUIActionGroup* pGroup);
	GGUIActionGroup* GetActionGroup() const;
	GGUIWindowBase* GetDestWindow() const;

protected:
	void ClearAllAction();

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
inline GGUIWindowBase* GGUIActionLine::GetDestWindow() const
{
	return m_pActionGroup->GetDestWindow();
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionLine_h_
//--------------------------------------------------------------------------------------------------
