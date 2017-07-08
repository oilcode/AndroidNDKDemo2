//----------------------------------------------------------------
#ifndef _GGUIFuncHelp_h_
#define _GGUIFuncHelp_h_
//----------------------------------------------------------------
class GGUIColor;
//----------------------------------------------------------------
bool GGUIFunc_GetImagesetIndexRectIndex(const char* szTexture, int* pImagesetIndex, int* pRectIndex);
void GGUIFunc_UIntConvertToGGUIColor(unsigned int uiColor, GGUIColor* pColor);
void GGUIFunc_OnResolutionChanged(float newWidth, float newHeight);
float GGUIFunc_GetResolutionWidth();
float GGUIFunc_GetResolutionHeight();
//----------------------------------------------------------------
#endif //_GGUIFuncHelp_h_
//----------------------------------------------------------------
