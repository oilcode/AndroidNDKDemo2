//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionBase_h_
#define _GGUIActionBase_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIWindowBase.h"
//--------------------------------------------------------------------------------------------------
enum GGUIActionType
{
    GGUIAction_Invalid = -1,
    GGUIAction_Group,
    GGUIAction_Line,
    //
    GGUIAction_Move,
    GGUIAction_Scale,
    GGUIAction_Event,
    GGUIAction_Max,
};
//--------------------------------------------------------------------------------------------------
class GGUIActionLine;
//--------------------------------------------------------------------------------------------------
class GGUIActionBase
{
    friend class GGUIActionFactory;
public:
	virtual void UpdateAction(float fDeltaTime);
	virtual bool IsActionFinished() const;

	void SetActionLine(GGUIActionLine* pLine);
    GGUIActionLine* GetActionLine() const;
	GGUIWindowBase* GetDestWindow() const;

    int GetActionID() const;
    GGUIActionType GetActionType() const;

protected:
    GGUIActionBase();
    virtual ~GGUIActionBase();
    virtual void ClearAction();
    void SetActionID(int nId);

protected:
    int m_nActionId;
    GGUIActionType m_eActionType;
	GGUIActionLine* m_pActionLine;
};
//--------------------------------------------------------------------------------------------------
inline void GGUIActionBase::SetActionID(int nId)
{
    m_nActionId = nId;
}
//--------------------------------------------------------------------------------------------------
inline int GGUIActionBase::GetActionID() const
{
    return m_nActionId;
}
//--------------------------------------------------------------------------------------------------
inline GGUIActionType GGUIActionBase::GetActionType() const
{
    return m_eActionType;
}
//--------------------------------------------------------------------------------------------------
inline void GGUIActionBase::SetActionLine(GGUIActionLine* pLine)
{
	m_pActionLine = pLine;
}
//--------------------------------------------------------------------------------------------------
inline GGUIActionLine* GGUIActionBase::GetActionLine() const
{
    return m_pActionLine;
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionBase_h_
//--------------------------------------------------------------------------------------------------
