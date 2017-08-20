//----------------------------------------------------------------
#include "GGUIUserDefine.h"
//----------------------------------------------------------------
GGUIColor g_GGUI_ButtonText_Color(0.0f, 0.0f, 1.0f, 1.0f);
GGUIColor g_GGUI_ProcessBar_FlashColor(1.0f, 1.0f, 1.0f, 0.7f);
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)

SoTinyString g_GGUI_ButtonText_Font("ËÎÌו");
const char* g_GGUI_ProcessBar_ImageBG = "texture/mm2:Name1";
const char* g_GGUI_ProcessBar_ImageBar = "texture/mm1:Name1";
const char* g_GGUI_ScrollBar_LeftBG = "texture/mm2:Name1";
const char* g_GGUI_ScrollBar_RightBG = "texture/mm2:Name1";
const char* g_GGUI_ScrollBar_CenterBG = "texture/mm2:Name1";

#elif (SoTargetPlatform == SoPlatform_Android)

SoTinyString g_GGUI_ButtonText_Font("nwfont");
const char* g_GGUI_ProcessBar_ImageBG = "mm1:hud_11";
const char* g_GGUI_ProcessBar_ImageBar = "mm1:hud_10";
const char* g_GGUI_ScrollBar_LeftBG = "mm1:hud_30";
const char* g_GGUI_ScrollBar_RightBG = "mm1:hud_30";
const char* g_GGUI_ScrollBar_CenterBG = "mm1:hud_30";

#endif

//----------------------------------------------------------------
