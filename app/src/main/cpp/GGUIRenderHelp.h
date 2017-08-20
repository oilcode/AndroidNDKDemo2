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
class GGUIImageset;
class GGUIRichTextStruct;
//----------------------------------------------------------------
void GGUIRenderHelp_SimpleImage(int nImagesetId, int nImageRectId, const GGUIRect& kAbsRect, const GGUIColor& kColor, bool bSwapX, bool bSwapY);
void GGUIRenderHelp_SimpleText(const char* szText, const GGUIRect& kAbsRect, GGUITextAlignX eAlignX, GGUITextAlignY eAlignY, const SoTinyString& kFontName, const GGUIColor& kColor);
//--nValidCount 绘制多少个字节。值为-1表示把整个字符串都绘制出来。
void GGUIRenderHelp_SimpleTextByImageset(const char* szText, const int nValidCount, const GGUIRect& kAbsRect, GGUITextAlignX eAlignX, GGUITextAlignY eAlignY, const GGUIImageset* pImageset, const GGUIColor& kColor);
void GGUIRenderHelp_RichText(const GGUIRichTextStruct* pCompText, float fRectLeft, float fRectTop);
//----------------------------------------------------------------
#endif //_GGUIRenderHelp_h_
//----------------------------------------------------------------
