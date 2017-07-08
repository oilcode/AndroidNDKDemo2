//----------------------------------------------------------------
#ifndef _GGUIRenderHelp_h_
#define _GGUIRenderHelp_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
class GGUIComponentText;
//----------------------------------------------------------------
void GGUIRenderHelp_SimpleImage(int nImagesetId, int nImageRectId, const GGUIRect& kAbsRect, const GGUIColor& kColor);
void GGUIRenderHelp_SimpleText(const char* szText, const GGUIRect& kAbsRect, GGUITextAlignX eAlignX, GGUITextAlignY eAlignY, const SoTinyString& kFontName, const GGUIColor& kColor);
void GGUIRenderHelp_ComponetText(const GGUIComponentText* pCompText);
//----------------------------------------------------------------
#endif //_GGUIRenderHelp_h_
//----------------------------------------------------------------
