//----------------------------------------------------------------
#ifndef _GGUILogicFlowHelp_h_
#define _GGUILogicFlowHelp_h_
//----------------------------------------------------------------
struct AnInputMsgInfo;
//----------------------------------------------------------------
bool GGUILogicFlowHelp_Create();
void GGUILogicFlowHelp_Release();
void GGUILogicFlowHelp_Update(float fDeltaTime);
void GGUILogicFlowHelp_PreRender();
void GGUILogicFlowHelp_Render();
void GGUILogicFlowHelp_DispatchInputMsg(AnInputMsgInfo* kMsgInfo);
//----------------------------------------------------------------
#endif //_GGUILogicFlowHelp_h_
//----------------------------------------------------------------
