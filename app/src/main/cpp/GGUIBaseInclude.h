//----------------------------------------------------------------
#ifndef _GGUIBaseInclude_h_
#define _GGUIBaseInclude_h_
//----------------------------------------------------------------
#include "SoCodeBaseInclude.h"
#include "SoStringHelp.h"
#include "SoCmdLineHelp.h"
#include "SoTinyString.h"
#include "SoArray.h"
#include "SoArrayUID.h"
#include "SoBitFlag.h"
#include "SoFileHelp.h"
#include "SoMath.h"
#include "SoIDEOutputLog.h"
#include "SoMessageBox.h"
//----------------------------------------------------------------
#include "GGUILogHelp.h"
#include "GGUIUserDefine.h"
#include "GGUIRect.h"
#include "GGUIPoint.h"
#include "GGUIColor.h"
#include "GGUIFuncHelp.h"
#include "GGUIInputMsg.h"
#include "GGUIInputState.h"
//----------------------------------------------------------------
enum GGUIWindowType
{
	GGUIWindow_Invalid = -1,
	GGUIWindow_Container,
	GGUIWindow_Panel,
	GGUIWindow_Text,
	GGUIWindow_Image,
	GGUIWindow_Button,
	GGUIWindow_ScrollBar,
	GGUIWindow_ProcessBar,
	GGUIWindow_ListBox,
	GGUIWindow_ComboBox,
	GGUIWindow_Max,
};
//----------------------------------------------------------------
enum GGUIReasonUnvisible
{
	GGUIReasonUnvisible_Self = 0x00000001,
	GGUIReasonUnvisible_Parent = 0x00000002,
	GGUIReasonUnvisible_3 = 0x00000004,
	GGUIReasonUnvisible_4 = 0x00000008,
};
//----------------------------------------------------------------
enum GGUIReasonInputDisable
{
	GGUIReasonInputDisable_Self = 0x00000001,
	GGUIReasonInputDisable_2 = 0x00000002,
	GGUIReasonInputDisable_3 = 0x00000004,
	GGUIReasonInputDisable_4 = 0x00000008,
};
//----------------------------------------------------------------
enum GGUITextAlignX
{
	GGUITextAlignX_Left,
	GGUITextAlignX_Center,
	GGUITextAlignX_Right,
};
//----------------------------------------------------------------
enum GGUITextAlignY
{
	GGUITextAlignY_Top,
	GGUITextAlignY_Center,
	GGUITextAlignY_Bottom,
};
//----------------------------------------------------------------
enum GGUIButtonState
{
	GGUIButtonState_Normal,
	GGUIButtonState_Hover,
	GGUIButtonState_Push,
	GGUIButtonState_Disable,
};
//------------------------------------------------------------
//值越大，越靠近屏幕，越绘制在上层，越优先处理input。
enum GGUIPanelSpaceType
{
	GGUIPanelSpace_Invalid = -1,
	GGUIPanelSpace_1,
	GGUIPanelSpace_2,
	GGUIPanelSpace_3,
	GGUIPanelSpace_Max,
};
//----------------------------------------------------------------
enum GGUIImagesetType
{
	GGUIImagesetType_Normal,
	GGUIImagesetType_Font,
};
//----------------------------------------------------------------
#endif //_GGUIBaseInclude_h_
//----------------------------------------------------------------
