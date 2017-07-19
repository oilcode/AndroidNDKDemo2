//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionGroup_h_
#define _GGUIActionGroup_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionLine;
class GGUIWindowBase;
//--------------------------------------------------------------------------------------------------
class GGUIActionGroup
{
public:
	GGUIActionGroup(GGUIWindowBase* pDestWindow);
	~GGUIActionGroup();

	void AddActionLine(GGUIActionLine* pLine);
	void UpdateActionGroup(float fDeltaTime);
	GGUIWindowBase* GetDestWindow() const;

protected:
	void ClearAllActionLine();

protected:
	GGUIWindowBase* m_pDestWindow;
	SoArray m_kLineArray;
};
//--------------------------------------------------------------------------------------------------
inline GGUIWindowBase* GGUIActionGroup::GetDestWindow() const
{
	return m_pDestWindow;
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionGroup_h_
//--------------------------------------------------------------------------------------------------
