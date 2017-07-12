//------------------------------------------------------------
#ifndef _GGUIEvent_h_
#define _GGUIEvent_h_
//------------------------------------------------------------
enum GGUIEventType
{
	GGUIEvent_Invalid = -1,
	GGUIEvent_WindowRectEnter,
	GGUIEvent_WindowRectLeave,
	GGUIEvent_PosChangedByDrag, //由于鼠标拖拽导致的位置移动
	GGUIEvent_Button_Clicked, //按钮按下了
	GGUIEvent_ScrollBar_PosChanged, //滚动条的滑块发生了位置移动
};
//------------------------------------------------------------
struct GGUIEventParam_WindowRectEnter
{
	const char* szWindowName;
	int nWindowID;
};
//------------------------------------------------------------
struct GGUIEventParam_WindowRectLeave
{
	const char* szWindowName;
	int nWindowID;
};
//------------------------------------------------------------
struct GGUIEventParam_ButtonClick
{
	const char* szWindowName;
	int nWindowID;
};
//------------------------------------------------------------
struct GGUIEventParam_PosChangedByDrag
{
	const char* szWindowName;
	int nWindowID;
};
//------------------------------------------------------------
struct GGUIEventParam_ScrollBar_PosChanged
{
	const char* szWindowName;
	int nWindowID;
	float fNewValue;
};
//------------------------------------------------------------
#endif //_GGUIEvent_h_
//------------------------------------------------------------
