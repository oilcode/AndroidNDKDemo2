//--------------------------------------------------------------------------------------------------
#ifndef _GLLogicGlowHelp_h_
#define _GLLogicGlowHelp_h_
//--------------------------------------------------------------------------------------------------
struct AnInputMsgInfo;
//--------------------------------------------------------------------------------------------------
bool GLLogicFlowHelpCreateBase();
bool GLLogicFlowHelpCreateOther();
void GLLogicFlowHelpRelease();
void GLLogicFlowHelpPause();
void GLLogicFlowHelpResume();
void GLLogicFlowHelpUpdate(float fDeltaTime);
void GLLogicFlowHelpPreRender();
void GLLogicFlowHelpRender();
void GLLogicFlowHelpResolutionChanged(int width, int height);
void GLLogicFlowHelpDispatchInputMsg(AnInputMsgInfo* kMsgInfo);
//--------------------------------------------------------------------------------------------------
#endif //_GLLogicGlowHelp_h_
//--------------------------------------------------------------------------------------------------
