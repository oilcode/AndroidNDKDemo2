//------------------------------------------------------------
#ifndef _GGUIWindowContainer_h_
#define _GGUIWindowContainer_h_
//------------------------------------------------------------
#include "GGUIWindowBase.h"
//------------------------------------------------------------
class GGUIWindowContainer : public GGUIWindowBase
{
public:
	virtual void AddChild(GGUIWindowBase* pChild);
	void RemoveChildByIndex(int nIndex);
	void RemoveChildByID(int nWindowID);
	void RemoveAllChild();
	void SwapChild(int nIndexA, int nIndexB);

	int GetChildCount() const;
	GGUIWindowBase* GetChildByIndex(int nIndex) const;
	GGUIWindowBase* GetChildByID(int nWindowID) const;
	GGUIWindowBase* GetChildByName(const char* szName) const;
	int GetIndexByID(int nWindowID) const;
	//递归遍历
	GGUIWindowBase* FindWindowByID(int nWindowID) const;
	//递归遍历
	GGUIWindowBase* FindWindowByName(const char* szName) const;

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void UpdateWindow(float fDeltaTime);
	virtual void RenderWindow();
	//返回true，表示本函数内已经处理了事件，派生类不需要再处理input；
	//返回false，表示派生类可以处理自己感兴趣的input。
	virtual bool InputWindow(GGUIInputMsg* pInputMsg);
	virtual void SetFullRect(const GGUIFullRect& kRect);
	virtual void SetFullRectScalePos(float fScaleX, float fScaleY);
	virtual void SetFullRectDeltaPos(float fDeltaX, float fDeltaY);
	virtual void MoveDelta(float fDeltaX, float fDeltaY);
	virtual void SetScale(float fScaleX, float fScaleY);
	virtual void ScaleDelta(float fDeltaX, float fDeltaY);
	virtual void OnParentRectChanged(const GGUIRect& kParentRectInAbsCoord);
	virtual void SetUIEventHandler(GGUIWindowBase* pHandler);
	virtual void SetVisibleByReason(souint32 uiReason, bool bVisible);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

protected:
	friend class GGUIWindowFactory;
	GGUIWindowContainer();
	virtual ~GGUIWindowContainer();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void DoRemoveChild(GGUIWindowBase* pChild);
	virtual void Notify_ParentRectChanged() const;
	void Notify_ParentVisibleChanged() const;

protected:
	SoArray m_kWindowArray;
	bool m_bAdjustChildRectWhenAddChild;
};
//----------------------------------------------------------------
inline int GGUIWindowContainer::GetChildCount() const
{
	return m_kWindowArray.GetSize();
}
//------------------------------------------------------------
#endif //_GGUIWindowContainer_h_
//------------------------------------------------------------
