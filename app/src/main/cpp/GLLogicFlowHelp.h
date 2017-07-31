//--------------------------------------------------------------------------------------------------
#ifndef _GLLogicGlowHelp_h_
#define _GLLogicGlowHelp_h_
//--------------------------------------------------------------------------------------------------
struct AnInputMsgInfo;
//--------------------------------------------------------------------------------------------------
bool GLLogicFlowHelpCreate();
bool GLLogicFlowHelpReCreateGLResource();
void GLLogicFlowHelpRelease();
void GLLogicFlowHelpPause();
void GLLogicFlowHelpResume();
void GLLogicFlowHelpUpdate(float fDeltaTime);
void GLLogicFlowHelpPreRender();
void GLLogicFlowHelpRender();
void GLLogicFlowHelpSetResolution(int width, int height);
void GLLogicFlowHelpDispatchInputMsg(AnInputMsgInfo* kMsgInfo);
bool GLLogicFlowHelpShouldReCreateGLResource();
//--------------------------------------------------------------------------------------------------
#endif //_GLLogicGlowHelp_h_
//--------------------------------------------------------------------------------------------------
