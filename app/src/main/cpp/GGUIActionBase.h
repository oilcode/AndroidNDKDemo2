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
class GGUIActionBase
{
    friend class GGUIActionFactory;

public:
	virtual void UpdateAction(float fDeltaTime);

    int GetActionID() const;
    GGUIActionType GetActionType() const;
    bool IsActionFinished() const;
    bool IsActionDead() const;

    void SetDestWindow(GGUIWindowBase* pWindow);
    GGUIWindowBase* GetDestWindow() const;

protected:
	enum eActionLifeStep
    {
        ActionLife_Running,
        ActionLife_Finished,
        ActionLife_Dead,
    };

protected:
    GGUIActionBase();
    virtual ~GGUIActionBase();
    virtual void ClearAction();
    void SetActionID(int nId);

protected:
    GGUIWindowBase* m_pDestWindow;
    int m_nActionId;
    GGUIActionType m_eActionType;
    eActionLifeStep m_eLifeStep;
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
inline bool GGUIActionBase::IsActionFinished() const
{
    return (m_eLifeStep == ActionLife_Finished);
}
//--------------------------------------------------------------------------------------------------
inline bool GGUIActionBase::IsActionDead() const
{
    return (m_eLifeStep == ActionLife_Dead);
}
//--------------------------------------------------------------------------------------------------
inline void GGUIActionBase::SetDestWindow(GGUIWindowBase* pWindow)
{
    m_pDestWindow = pWindow;
}
//--------------------------------------------------------------------------------------------------
inline GGUIWindowBase* GGUIActionBase::GetDestWindow() const
{
    return m_pDestWindow;
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionBase_h_
//--------------------------------------------------------------------------------------------------
