//----------------------------------------------------------------
#include "GGUIWindowBase.h"
#include "GGUIWindowFactory.h"
#include "WinInputMsg.h"
#include "GGUIEvent.h"
//----------------------------------------------------------------
GGUIWindowBase::GGUIWindowBase()
:m_nID(-1)
,m_nParentID(-1)
,m_eType(GGUIWindow_Invalid)
,m_pUIEventHandler(0)
,m_bDragEnable(false)
,m_bCursorIsInside(false)
{
	
}
//----------------------------------------------------------------
GGUIWindowBase::~GGUIWindowBase()
{

}
//----------------------------------------------------------------
void GGUIWindowBase::ClearWindow()
{
	//被Factory回收的Window，其ParentID都是-1；
	//只要ParentID为-1，则该Window处于被回收待利用状态。
	//
	//m_nID = -1;
	//m_eType = GGUIWindow_Invalid;
	m_nParentID = -1;
	m_kName.Clear();
	m_pUIEventHandler = 0;
	m_kFullRect = GGUIFullRect_Empty;
	m_kRectInAbsCoord = GGUIRect_Empty;
	m_kParentRectInAbsCoord = GGUIRect_Empty;
	m_kUnvisibleReason.Clear();
	m_kInputDisableReason.Clear();
	m_bCursorIsInside = false;
}
//----------------------------------------------------------------
void GGUIWindowBase::UpdateWindow(float fDeltaTime)
{
	//do nothing
}
//----------------------------------------------------------------
void GGUIWindowBase::RenderWindow()
{
	//do nothing
}
//----------------------------------------------------------------
bool GGUIWindowBase::InputWindow(stInputEvent* pInputEvent)
{
	if (GetVisible() == false)
	{
		//派生类不要再处理input。
		return true;
	}
	if (GetInputEnable() == false)
	{
		//派生类不要再处理input。
		return true;
	}
	if (m_pUIEventHandler == 0)
	{
		//派生类不要再处理input。
		return true;
	}
	if (GGUIInputState::m_nWindoeID_CursorDrag != -1 && GGUIInputState::m_nWindoeID_CursorDrag != m_nID)
	{
		//有窗口正在处于拖拽中，并且该窗口不是本窗口。
		//派生类不要再处理input。
		return true;
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//判断鼠标是否位于窗口范围内。
	bool bIsInside = false;
	if (m_nID == GGUIInputState::m_nWindoeID_CursorDrag)
	{
		//鼠标正在拖拽本窗口，则认为鼠标总是位于窗口范围内。
		//这是为了防止出现这种情况：
		//鼠标拖拽过程中，鼠标瞬间滑动太快，当前帧内鼠标移出了本窗口范围，
		//导致判断成了“鼠标离开窗口范围”，拖拽中断。
		bIsInside = true;
	}
	else
	{
		bIsInside = m_kRectInAbsCoord.IsInside((float)pInputEvent->nParam1, (float)pInputEvent->nParam2);
	}
	if (bIsInside)
	{
		//鼠标位于窗口范围内。
		if (m_eType == GGUIWindow_Panel)
		{
			//本窗口是一个Panel，不能把所有的消息都吞噬掉，
			//例如，本窗口是一个全屏窗口，如果把所有的消息都吞噬掉，那么其他模块永远不能响应消息了。
			//Panel窗口只吞噬造成窗口拖拽的消息。
		}
		else
		{
			pInputEvent->Swallow();
		}
	}
	m_bCursorIsInside = bIsInside;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//检测窗口拖拽逻辑。
	if (GetDragEnable())
	{
		if (InputDragLogic(pInputEvent))
		{
			//正在拖拽中。
			//只处理拖拽，不处理其他事件，直接退出。
			//派生类不要再处理input。
			return true;
		}
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//检测是否要抛出“鼠标进入窗口区域”或者“鼠标离开窗口区域”事件。
	if (InputWindowRectLogic())
	{
		//抛出了事件，不处理其他事件，直接退出。
		//派生类不要再处理input。
		return true;
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	return false;
}
//----------------------------------------------------------------
void GGUIWindowBase::ProcessUIEvent(int nEventType, void* pParam)
{
	//do nothing
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRect(const GGUIFullRect& kRect)
{
	m_kFullRect = kRect;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRectScalePos(float fScaleX, float fScaleY)
{
	m_kFullRect.fScaleX = fScaleX;
	m_kFullRect.fScaleY = fScaleY;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRectDeltaPos(float fDeltaX, float fDeltaY)
{
	m_kFullRect.fDeltaX = fDeltaX;
	m_kFullRect.fDeltaY = fDeltaY;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::MoveDelta(float fDeltaX, float fDeltaY)
{
	m_kFullRect.fDeltaX += fDeltaX;
	m_kFullRect.fDeltaY += fDeltaY;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::OnParentRectChanged(const GGUIRect& kParentRectInAbsCoord)
{
	m_kParentRectInAbsCoord = kParentRectInAbsCoord;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::SetVisibleByReason(souint32 uiReason, bool bVisible)
{
	if (bVisible)
	{
		m_kUnvisibleReason.RemoveFlag(uiReason);
	}
	else
	{
		m_kUnvisibleReason.AddFlag(uiReason);
	}
}
//----------------------------------------------------------------
void GGUIWindowBase::SetInputEnableByReason(souint32 uiReason, bool bEnable)
{
	if (bEnable)
	{
		m_kInputDisableReason.RemoveFlag(uiReason);
	}
	else
	{
		m_kInputDisableReason.AddFlag(uiReason);
	}
}
//----------------------------------------------------------------
void GGUIWindowBase::CalculateRectInAbsCoord()
{
	m_kRectInAbsCoord.x = m_kParentRectInAbsCoord.x + m_kParentRectInAbsCoord.w * m_kFullRect.fScaleX + m_kFullRect.fDeltaX;
	m_kRectInAbsCoord.y = m_kParentRectInAbsCoord.y + m_kParentRectInAbsCoord.h * m_kFullRect.fScaleY + m_kFullRect.fDeltaY;
	m_kRectInAbsCoord.w = m_kParentRectInAbsCoord.w * m_kFullRect.fScaleW + m_kFullRect.fDeltaW;
	m_kRectInAbsCoord.h = m_kParentRectInAbsCoord.h * m_kFullRect.fScaleH + m_kFullRect.fDeltaH;
}
//----------------------------------------------------------------
bool GGUIWindowBase::InputDragLogic(stInputEvent* pInputEvent)
{
	bool bDrag = false;
	if (m_nID != GGUIInputState::m_nWindoeID_CursorDrag)
	{
		//判断鼠标是否开始拖拽窗口。
		if (m_bCursorIsInside && m_nID == GGUIInputState::m_nWindoeID_CursorInWindowRect)
		{
			//鼠标一直位于本窗口矩形范围内。
			if (pInputEvent->theEvent == InputEvent_Down && pInputEvent->theKey == InputKey_LMouse)
			{
				//鼠标左键按下了，开始拖拽。
				GGUIInputState::m_nWindoeID_CursorDrag = m_nID;
				GGUIInputState::m_nLastCursorPosX = pInputEvent->nParam1;
				GGUIInputState::m_nLastCursorPosY = pInputEvent->nParam2;
				//注意，这里不能把bDrag设置成true，否则窗口无法响应单击事件。
				//消息被处理了，消息被吞噬。
				pInputEvent->Swallow();
			}
		}
	}
	else
	{
		//鼠标正在拖拽本窗口。
		//本窗口只响应鼠标移动和鼠标左键抬起两个事件。
		if (pInputEvent->theEvent == InputEvent_MouseMove)
		{
			//窗口移动。
			int nDeltaX = pInputEvent->nParam1 - GGUIInputState::m_nLastCursorPosX;
			int nDeltaY = pInputEvent->nParam2 - GGUIInputState::m_nLastCursorPosY;
			MoveDelta((float)nDeltaX, (float)nDeltaY);
			GGUIInputState::m_nLastCursorPosX = pInputEvent->nParam1;
			GGUIInputState::m_nLastCursorPosY = pInputEvent->nParam2;
			bDrag = true;
			//抛出事件
			GGUIEventParam_PosChangedByDrag kParam;
			kParam.szWindowName = m_kName.GetValue();
			kParam.nWindowID = m_nID;
			m_pUIEventHandler->ProcessUIEvent(GGUIEvent_PosChangedByDrag, &kParam);
			//消息被处理了，消息被吞噬。
			pInputEvent->Swallow();
		}
		else if (pInputEvent->theEvent == InputEvent_Up && pInputEvent->theKey == InputKey_LMouse)
		{
			//停止拖拽。
			GGUIInputState::m_nWindoeID_CursorDrag = -1;
			//消息被处理了，消息被吞噬。
			pInputEvent->Swallow();
		}
	}
	return bDrag;
}
//----------------------------------------------------------------
bool GGUIWindowBase::InputWindowRectLogic()
{
	bool bShouldSendEvent_WindowRect = false;
	const int oldWindoeID_CursorInWindowRect = GGUIInputState::m_nWindoeID_CursorInWindowRect;
	if (m_nID == GGUIInputState::m_nWindoeID_CursorInWindowRect)
	{
		if (m_bCursorIsInside == false)
		{
			//之前鼠标位于本窗口内部，现在不再位于本窗口内部。
			bShouldSendEvent_WindowRect = true;
			GGUIInputState::m_nWindoeID_CursorInWindowRect = -1;
			if (m_nID == GGUIInputState::m_nWindoeID_CursorDrag)
			{
				//本窗口正处于拖拽中，停止拖拽。
				//下面的情形就会出现这种情况：
				//鼠标拖拽本窗口过程中，鼠标移入了上层窗口的矩形范围，
				//上层窗口的input优先级比本窗口要高,
				//则本窗口停止拖拽，本窗口抛出“移出窗口范围”的事件，
				//上层窗口抛出“移入窗口范围”的事件。
				GGUIInputState::m_nWindoeID_CursorDrag = -1;
			}
		}
	}
	else
	{
		if (m_bCursorIsInside == true)
		{
			//之前鼠标不位于本窗口内部，现在位于本窗口内部。
			bShouldSendEvent_WindowRect = true;
			GGUIInputState::m_nWindoeID_CursorInWindowRect = m_nID;
			//本窗口肯定不在拖拽中；不管是哪个窗口处于拖拽中，都要停止。
			GGUIInputState::m_nWindoeID_CursorDrag = -1;
		}
	}
	//
	if (bShouldSendEvent_WindowRect)
	{
		if (m_bCursorIsInside)
		{
			if (oldWindoeID_CursorInWindowRect != -1)
			{
				//旧窗口要抛出离开窗口的事件。
				//未完待续，这里有一个不完善的逻辑，旧窗口一定隶属于g_pCurrentPanel吗？
				//答案是不一定。
				//如果旧窗口不隶属于g_pCurrentPanel，那么就要找出它所属于的那个Panel（该Panel要事先记录下来）。
				//现在，总是认为旧窗口隶属于g_pCurrentPanel。
				GGUIWindowBase* pOldWindow = GGUIWindowFactory::Get()->GetUIWindow(oldWindoeID_CursorInWindowRect);
				if (pOldWindow)
				{
					GGUIEventParam_WindowRectLeave kParam;
					kParam.szWindowName = pOldWindow->GetName().GetValue();
					kParam.nWindowID = pOldWindow->GetID();
					m_pUIEventHandler->ProcessUIEvent(GGUIEvent_WindowRectLeave, &kParam);
				}
			}
			//
			GGUIEventParam_WindowRectEnter kParam;
			kParam.szWindowName = m_kName.GetValue();
			kParam.nWindowID = m_nID;
			m_pUIEventHandler->ProcessUIEvent(GGUIEvent_WindowRectEnter, &kParam);
		}
		else
		{
			GGUIEventParam_WindowRectLeave kParam;
			kParam.szWindowName = m_kName.GetValue();
			kParam.nWindowID = m_nID;
			m_pUIEventHandler->ProcessUIEvent(GGUIEvent_WindowRectLeave, &kParam);
		}
	}
	return bShouldSendEvent_WindowRect;
}
//----------------------------------------------------------------
