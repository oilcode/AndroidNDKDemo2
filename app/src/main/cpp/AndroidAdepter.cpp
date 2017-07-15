//--------------------------------------------------------------------------------------------------
#include "AndroidAdepter.h"
#include "AnFileAsset.h"
#include "AnFileInternal.h"
#include "AnFileExternal.h"
#include "AnInputMsgDispatch.h"
#include "GLLogicFlowHelp.h"
#include "GGUILogicFlowHelp.h"
#include "NwLogicFlowHelp.h"
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onActivityCreate()
{

}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onActivityPause()
{
	GLLogicFlowHelpPause();
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onActivityResume()
{
	GLLogicFlowHelpResume();
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onViewTouchDown(float fx, float fy)
{
	AnInputMsgDispatch::DispatchInputMsg(AnInputMsg_TouchDown, fx, fy);
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onViewTouchMove(float fx, float fy)
{
    AnInputMsgDispatch::DispatchInputMsg(AnInputMsg_TouchMove, fx, fy);
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onViewTouchUp(float fx, float fy)
{
    AnInputMsgDispatch::DispatchInputMsg(AnInputMsg_TouchUp, fx, fy);
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onRenderSurfaceCreated()
{
    AnInputMsgDispatch::InitInputMsgDispatch();
    GLLogicFlowHelpCreateBase();
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onRenderSurfaceChanged(int width, int height)
{
    GLLogicFlowHelpResolutionChanged(width, height);
    GLLogicFlowHelpCreateOther();
    GGUILogicFlowHelp_Create();
    NwLogicFlowHelp_Create();
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onRenderDrawFrame()
{
    float fDeltaTime = 0.01666f;
	GLLogicFlowHelpUpdate(fDeltaTime);
    GGUILogicFlowHelp_Update(fDeltaTime);
    NwLogicFlowHelp_Update(fDeltaTime);
    //
    GLLogicFlowHelpPreRender();
    GGUILogicFlowHelp_PreRender();
    //
    GLLogicFlowHelpRender();
    GGUILogicFlowHelp_Render();
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::setAssetManager(AAssetManager* pAssetMgr)
{
    AnFileAsset::SetAssetMgr(pAssetMgr);
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::setInternalPath(const char* szPath)
{
    AnFileInternal::SetInternalPath(szPath);
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::setExternalPath(const char* szPath)
{
    AnFileExternal::SetExternalPath(szPath);
}
//--------------------------------------------------------------------------------------------------
