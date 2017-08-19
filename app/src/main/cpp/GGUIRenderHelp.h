//----------------------------------------------------------------
#ifndef _GGUIRenderHelp_h_
#define _GGUIRenderHelp_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
#include "GGUIRenderDefine.h"
//----------------------------------------------------------------
bool GGUIRenderHelp_Create();
void GGUIRenderHelp_Release();
void GGUIRenderHelp_Render();
void GGUIRenderHelp_AddRnederUnit(const stUIRenderUnit* pUIRenderUnit);
void* GGUIRenderHelp_CreateUITextureFromFile(const char* szFullTexName);
//----------------------------------------------------------------
void GGUIRenderHelp_SimpleImage(int nImagesetId, int nImageRectId, const GGUIRect& kAbsRect, const GGUIColor& kColor, bool bSwapX, bool bSwapY);
void GGUIRenderHelp_SimpleText(const char* szText, const GGUIRect& kAbsRect, GGUITextAlignX eAlignX, GGUITextAlignY eAlignY, const SoTinyString& kFontName, const GGUIColor& kColor);
//----------------------------------------------------------------
#endif //_GGUIRenderHelp_h_
//----------------------------------------------------------------
