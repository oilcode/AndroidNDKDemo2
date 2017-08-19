//----------------------------------------------------------------
#include "GGUILogicFlowHelp.h"
#include "GGUIRenderHelp.h"
#include "GGUIImagesetManager.h"
#include "GGUIWindowFactory.h"
#include "GGUIPanelManager.h"
#include "GGUIActionFactory.h"
#include "GLFuncHelp.h"
//----------------------------------------------------------------
bool GGUILogicFlowHelp_Create()
{
    float fWidth = 0.0f;
    float fHeight = 0.0f;
    GLFunc_GetResolution(&fWidth, &fHeight);
    GGUIFunc_OnResolutionChanged(fWidth, fHeight);
    //
	if (GGUIRenderHelp_Create() == false)
	{
		return false;
	}
	if (GGUIImagesetManager::CreateUIImagesetManager() == false)
	{
		return false;
	}
	if (GGUIWindowFactory::CreateUIWindowFactory() == false)
	{
		return false;
	}
	if (GGUIPanelManager::CreateUIPanelManager() == false)
	{
		return false;
	}
	if (GGUIActionFactory::CreateUIActionFactory() == false)
	{
		return false;
	}
	return true;
}
//----------------------------------------------------------------
void GGUILogicFlowHelp_Release()
{
    GGUIActionFactory::ReleaseUIActionFactory();
	GGUIPanelManager::ReleaseUIPanelManager();
	GGUIWindowFactory::ReleaseUIWindowFactory();
	GGUIImagesetManager::ReleaseUIImagesetManager();
	GGUIRenderHelp_Release();
}
//----------------------------------------------------------------
void GGUILogicFlowHelp_Update(float fDeltaTime)
{
	GGUIPanelManager::Get()->UpdateUIPanelManager(fDeltaTime);

	/*
    stUIRenderUnit kUnit;
    kUnit.fRectLeft = 200.0f;
    kUnit.fRectTop = 200.0f;
    kUnit.fRectWidth = 200.0f;
    kUnit.fRectHeight = 200.0f;
    kUnit.fTexCoordLeft = 0.0f;
    kUnit.fTexCoordTop = 0.0f;
    kUnit.fTexCoordWidth = 1.0f;
    kUnit.fTexCoordHeight = 1.0f;
    kUnit.fColorR = 0.0f;
    kUnit.fColorG = 0.0f;
    kUnit.fColorB = 0.0f;
    kUnit.fColorA = 0.0f;
    kUnit.uiTexResourceId = 1;
    GGUIRenderManagerGL::Get()->AddRnederUnit(&kUnit);
    */
}
//----------------------------------------------------------------
void GGUILogicFlowHelp_PreRender()
{

}
//----------------------------------------------------------------
void GGUILogicFlowHelp_Render()
{
	GGUIPanelManager::Get()->RenderUIPanelManager();
	GGUIRenderHelp_Render();
}
//----------------------------------------------------------------
void GGUILogicFlowHelp_DispatchInputMsg(GGUIInputMsg* kInputMsg)
{
    GGUIPanelManager::Get()->InputUIPanelManager(kInputMsg);
}
//----------------------------------------------------------------
