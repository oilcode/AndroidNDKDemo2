//--------------------------------------------------------------------------------------------------
#include "AndroidAdepter.h"
#include "AnFileAsset.h"
#include "AnFileInternal.h"
#include "AnFileExternal.h"
#include "GLLogicFlowHelp.h"
#include "GGUILogicFlowHelp.h"
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
	GLLogicFlowHelpTouchDown(fx, fy);
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onViewTouchMove(float fx, float fy)
{
	GLLogicFlowHelpTouchMove(fx, fy);
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onViewTouchUp(float fx, float fy)
{
	GLLogicFlowHelpTouchUp(fx, fy);
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onRenderSurfaceCreated()
{
    GLLogicFlowHelpCreateBase();
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onRenderSurfaceChanged(int width, int height)
{
    GLLogicFlowHelpResolutionChanged(width, height);
    GLLogicFlowHelpCreateOther();
    GGUILogicFlowHelp_Create();
}
//--------------------------------------------------------------------------------------------------
void AndroidAdepter::onRenderDrawFrame()
{
	GLLogicFlowHelpUpdate();
    GGUILogicFlowHelp_Update(0.0f);
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
