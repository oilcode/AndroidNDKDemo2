//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionBase_h_
#define _GGUIActionBase_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIBaseInclude.h"
#include "GGUIActionLine.h"
#include "GGUIWindowBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionLine;
class GGUIWindowBase;
//--------------------------------------------------------------------------------------------------
class GGUIActionBase
{
public:
	GGUIActionBase();
	virtual ~GGUIActionBase();
	virtual void UpdateAction(float fDeltaTime);
	virtual bool IsActionFinished() const;

	void SetActionLine(GGUIActionLine* pLine);
	GGUIWindowBase* GetDestWindow() const;

protected:
	GGUIActionLine* m_pActionLine;
};
//--------------------------------------------------------------------------------------------------
inline void GGUIActionBase::SetActionLine(GGUIActionLine* pLine)
{
	m_pActionLine = pLine;
}
//--------------------------------------------------------------------------------------------------
inline GGUIWindowBase* GGUIActionBase::GetDestWindow() const
{
	return m_pActionLine->GetDestWindow();
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionBase_h_
//--------------------------------------------------------------------------------------------------
