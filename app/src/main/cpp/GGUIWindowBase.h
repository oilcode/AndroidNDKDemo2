//----------------------------------------------------------------
#ifndef _GGUIWindowBase_h_
#define _GGUIWindowBase_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
class GGUIActionGroup;
//----------------------------------------------------------------
class GGUIWindowBase
{
public:
	//更新。
	virtual void UpdateWindow(float fDeltaTime);
	//绘制。
	virtual void RenderWindow();
	//处理Input事件。
	//返回true，表示本函数内已经处理了事件，派生类不需要再处理input；
	//返回false，表示派生类可以处理自己感兴趣的input。
	virtual bool InputWindow(GGUIInputMsg* pInputMsg);
	//处理UI事件。
	//此函数主要由 GGUIWindowPanel 来做处理。
	//一般情况下，界面内的窗口抛出事件（例如Button抛出 GGUIEvent_Button_Clicked 事件），
	//由 GGUIWindowPanel 来响应事件。
	virtual void ProcessUIEvent(int nEventType, void* pParam);
	//处理Action事件。
	virtual void ProcessActionEvent(int nEventId);

	//获取窗口ID。
	int GetID() const;
	//获取窗口类型。
	GGUIWindowType GetType() const;

	//设置父窗口ID。
	void SetParentID(int nID);
	//获取父窗口ID。
	int GetParentID() const;

	//设置窗口名字。
	void SetName(const char* szName);
	//获取窗口名字。
	const SoTinyString& GetName() const;

	virtual void SetFullRect(const GGUIFullRect& kRect);
	virtual void SetFullRectScalePos(float fScaleX, float fScaleY);
	virtual void SetFullRectDeltaPos(float fDeltaX, float fDeltaY);
	virtual void SetFullRectScaleWH(float fScaleW, float fScaleH);
	virtual void MoveDelta(float fDeltaX, float fDeltaY);
    virtual void SetScale(float fScaleX, float fScaleY);
    virtual void ScaleDelta(float fDeltaX, float fDeltaY);
	virtual void OnParentRectChanged(const GGUIRect& kParentRectInAbsCoord);
	virtual void SetUIEventHandler(GGUIWindowBase* pHandler);

	const GGUIFullRect& GetFullRect() const;
	const GGUIRect& GetRectInAbsCoord() const;
	const GGUIRect& GetParentRectInAbsCoord() const;

	void SetVisible(bool bVisible);
	virtual void SetVisibleByReason(souint32 uiReason, bool bVisible);
	bool GetVisible() const;

	void SetInputEnable(bool bEnable);
	void SetInputEnableByReason(souint32 uiReason, bool bEnable);
	bool GetInputEnable() const;

	void SetDragEnable(bool bDrag);
	bool GetDragEnable() const;

	GGUIActionGroup* CreateActionGroup();
	void DeleteActionGroup();
	GGUIActionGroup* GetActionGroup() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowBase();
	virtual ~GGUIWindowBase();
	virtual void ClearWindow();
	void SetID(int nID);
	void CalculateRectInAbsCoord(bool bOnlyScaleChanged);
	//返回值为true，表示鼠标正在拖拽本窗口。
	bool InputDragLogic(GGUIInputMsg* pInputMsg);
	//返回值为true，表示抛出了“鼠标进入窗口区域”或者“鼠标离开窗口区域”事件。
	bool InputWindowRectLogic();

protected:
	int m_nID;
	int m_nParentID;
	GGUIWindowType m_eType;
	SoTinyString m_kName;
	//本窗口会抛出UIEvent，而m_pUIEventHandler就是响应该UIEvent的窗口。
	//一般情况下，GGUIWindowPanel 会充当 m_pUIEventHandler 。
	GGUIWindowBase* m_pUIEventHandler;
	GGUIActionGroup* m_pActionGroup;

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //本窗口原始的完全矩形，是UI编辑器中指定的值。
    GGUIFullRect m_kFullRect;
    //父窗口当前的矩形范围。
    GGUIRect m_kParentRectInAbsCoord;
    //在父窗口的影响下，本窗口原始的未被缩放的矩形范围。
    GGUIRect m_kOriginalRectInAbsCoord;
    //在父窗口的影响下，本窗口当前的矩形范围。
	GGUIRect m_kRectInAbsCoord;
    //缩放相关的值。
    float m_fScaleX;
    float m_fScaleY;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	SoBitFlag m_kUnvisibleReason;
	SoBitFlag m_kInputDisableReason;
	bool m_bDragEnable;
	bool m_bCursorIsInside;
};
//----------------------------------------------------------------
inline void GGUIWindowBase::SetID(int nID)
{
	m_nID = nID;
}
//----------------------------------------------------------------
inline int GGUIWindowBase::GetID() const
{
	return m_nID;
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetParentID(int nID)
{
	m_nParentID = nID;
}
//----------------------------------------------------------------
inline int GGUIWindowBase::GetParentID() const
{
	return m_nParentID;
}
//----------------------------------------------------------------
inline GGUIWindowType GGUIWindowBase::GetType() const
{
	return m_eType;
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetName(const char* szName)
{
	m_kName = szName;
}
//----------------------------------------------------------------
inline const SoTinyString& GGUIWindowBase::GetName() const
{
	return m_kName;
}
//----------------------------------------------------------------
inline const GGUIFullRect& GGUIWindowBase::GetFullRect() const
{
	return m_kFullRect;
}
//----------------------------------------------------------------
inline const GGUIRect& GGUIWindowBase::GetRectInAbsCoord() const
{
	return m_kRectInAbsCoord;
}
//----------------------------------------------------------------
inline const GGUIRect& GGUIWindowBase::GetParentRectInAbsCoord() const
{
	return m_kParentRectInAbsCoord;
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetVisible(bool bVisible)
{
	SetVisibleByReason(GGUIReasonUnvisible_Self, bVisible);
}
//----------------------------------------------------------------
inline bool GGUIWindowBase::GetVisible() const
{
	return m_kUnvisibleReason.IsZero();
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetInputEnable(bool bEnable)
{
	SetInputEnableByReason(GGUIReasonInputDisable_Self, bEnable);
}
//----------------------------------------------------------------
inline bool GGUIWindowBase::GetInputEnable() const
{
	return m_kInputDisableReason.IsZero();
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetDragEnable(bool bDrag)
{
	m_bDragEnable = bDrag;
}
//----------------------------------------------------------------
inline bool GGUIWindowBase::GetDragEnable() const
{
	return m_bDragEnable;
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetUIEventHandler(GGUIWindowBase* pHandler)
{
	m_pUIEventHandler = pHandler;
}
//----------------------------------------------------------------
inline GGUIActionGroup* GGUIWindowBase::GetActionGroup() const
{
	return m_pActionGroup;
}
//----------------------------------------------------------------
#endif //_GGUIWindowBase_h_
//----------------------------------------------------------------
