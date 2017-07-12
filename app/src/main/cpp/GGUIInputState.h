//----------------------------------------------------------------
#ifndef _GGUIInputState_h_
#define _GGUIInputState_h_
//----------------------------------------------------------------
class GGUIInputState
{
public:
	//鼠标正位于哪个窗口范围内。
	static int m_nWindoeID_CursorInWindowRect;
	//鼠标正在拖动哪个窗口。
	//鼠标左键单击窗口，就会触发“鼠标开始拖拽该窗口”的逻辑，
	//同时也会触发Click逻辑（例如 GGUIEvent_Button_Clicked），
	//所以拖拽和单击会同时触发。
	static int m_nWindoeID_CursorDrag;
	//下面两个成员提供辅助作用，在拖拽逻辑中会用到。
	static float m_fLastCursorPosX;
	static float m_fLastCursorPosY;
};
//----------------------------------------------------------------
#endif //_GGUIInputState_h_
//----------------------------------------------------------------
