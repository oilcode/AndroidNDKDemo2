//----------------------------------------------------------------
#ifndef _GGUIUserDefine_h_
#define _GGUIUserDefine_h_
//----------------------------------------------------------------
#include "GGUIColor.h"
#include "SoTinyString.h"
//----------------------------------------------------------------
//渲染覆盖顺序，是由距离远近决定的。顶点坐标Z值越大，距离越远，越容易被距离近的窗口覆盖。
//摄像机的观察范围是[0,10000]，见 SoD3DCameraUI::InitD3DCameraUI() ，要想被摄像机“看见”的话，
//窗口顶点坐标Z值的取值范围最好是[1,9999]。
//在右手坐标系下，摄像机面向的是Z轴负方向，所以窗口顶点坐标Z值的取值范围最好是[-1,-9999]。
#define GGUI_RenderOrder_Max -9999.0f
//每绘制一个窗口，RenderOrder就减少 GGUI_RenderOrder_Step ，以使得下一个窗口绘制在它的上层，新窗口覆盖旧窗口。
//注意，GGUI_RenderOrder_Step的值不能太小，因为float数据类型精度比较低，会导致相邻的面片不能正确排序。
#define GGUI_RenderOrder_Step 1.0f
//----------------------------------------------------------------
#define GGUI_ButtonStateHover_ColorR 1.0f
#define GGUI_ButtonStateHover_ColorG 0.0f
#define GGUI_ButtonStateHover_ColorB 0.0f
#define GGUI_ButtonStateHover_ColorA 0.5f
#define GGUI_ButtonStatePush_ColorR 0.0f
#define GGUI_ButtonStatePush_ColorG 0.0f
#define GGUI_ButtonStatePush_ColorB 1.0f
#define GGUI_ButtonStatePush_ColorA 0.5f
#define GGUI_ButtonStateDisable_ColorR 0.5f
#define GGUI_ButtonStateDisable_ColorG 0.5f
#define GGUI_ButtonStateDisable_ColorB 0.5f
#define GGUI_ButtonStateDisable_ColorA 0.75f

#define GGUI_ButtonStateHover_DeltaX -1.0f
#define GGUI_ButtonStateHover_DeltaY -1.0f

#if (SoTargetPlatform == SoPlatform_Windows)
#define GGUI_ButtonStatePush_DeltaX 2.0f
#define GGUI_ButtonStatePush_DeltaY 2.0f
#elif (SoTargetPlatform == SoPlatform_Android)
#define GGUI_ButtonStatePush_DeltaX 4.0f
#define GGUI_ButtonStatePush_DeltaY 5.0f
#endif
//----------------------------------------------------------------
extern SoTinyString g_GGUI_ButtonText_Font;
extern GGUIColor g_GGUI_ButtonText_Color;
//----------------------------------------------------------------
extern const char* g_GGUI_ProcessBar_ImageBG;
extern const char* g_GGUI_ProcessBar_ImageBar;
extern GGUIColor g_GGUI_ProcessBar_FlashColor;
#define GGUI_ProcessBar_FalshTime 0.2f
//----------------------------------------------------------------
extern const char* g_GGUI_ScrollBar_LeftBG;
extern const char* g_GGUI_ScrollBar_RightBG;
extern const char* g_GGUI_ScrollBar_CenterBG;
//----------------------------------------------------------------
#define GGUI_ComponentText_TextChunkAddCount 4
#define GGUI_ComponentText_NewChunkCountPrePause 2
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
#define GGUI_DefaultFont "宋体"
#endif
//----------------------------------------------------------------
#endif //_GGUIUserDefine_h_
//----------------------------------------------------------------
