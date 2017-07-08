//--------------------------------------------------------------------------------------------------
#ifndef _GLLogicGlowHelp_h_
#define _GLLogicGlowHelp_h_
//--------------------------------------------------------------------------------------------------
bool GLLogicFlowHelpCreateBase();
bool GLLogicFlowHelpCreateOther();
void GLLogicFlowHelpRelease();
void GLLogicFlowHelpPause();
void GLLogicFlowHelpResume();
void GLLogicFlowHelpResolutionChanged(int width, int height);
void GLLogicFlowHelpTouchDown(float fx, float fy);
void GLLogicFlowHelpTouchMove(float fx, float fy);
void GLLogicFlowHelpTouchUp(float fx, float fy);
void GLLogicFlowHelpUpdate();
void GLLogicFlowHelpPreRender();
void GLLogicFlowHelpRender();
//--------------------------------------------------------------------------------------------------
#endif //_GLLogicGlowHelp_h_
//--------------------------------------------------------------------------------------------------
