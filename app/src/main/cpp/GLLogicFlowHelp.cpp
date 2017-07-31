//--------------------------------------------------------------------------------------------------
#include "GLLogicFlowHelp.h"
#include "GLFuncHelp.h"
#include "GLManager.h"
#include "GLTextureManager.h"
#include "GLShaderManager.h"
#include "GLCamera.h"
#include "GLCameraUI.h"
#include "GLModelCube.h"
#include "GLModelRect.h"
//--------------------------------------------------------------------------------------------------
//GLModelCube* g_pModelCube = 0;
//GLModelRect* g_pModelRect = 0;
//--------------------------------------------------------------------------------------------------
bool GLLogicFlowHelpCreate()
{
    SoIDEOutputLogInfo("GLLogicFlowHelpCreate : begin");
    GLManager::CreateGLManager();
    GLTextureManager::CreateTextureManager();
    GLShaderManager::CreateShaderManager();
    GLCamera::CreateCamera();
    GLCameraUI::CreateCameraUI();

    //g_pModelCube = SoNew GLModelCube;

    //g_pModelRect = SoNew GLModelRect;

    /*
    SoFile* pFileInternal = SoFileHelp::CreateFileInternal("kk1.txt", "r");
    if (pFileInternal)
    {
        const char* buff = (char*)pFileInternal->GetFileData();
        SoIDEOutputLogInfo("%s", buff);
        SoFileHelp::DeleteFile(pFileInternal);
    }

    SoFile* pFileExternal = SoFileHelp::CreateFileExternal("kk2.txt", "w");
    if (pFileExternal)
    {
        pFileExternal->Write("kk2", 1, 3);
        SoFileHelp::DeleteFile(pFileExternal);
    }
    */

    SoIDEOutputLogInfo("GLLogicFlowHelpCreate : end");
    return true;
}
//--------------------------------------------------------------------------------------------------
bool GLLogicFlowHelpReCreateGLResource()
{
    SoIDEOutputLogInfo("GLLogicFlowHelpReCreateGLResource : begin");
    GLManager::CreateGLManager();
    GLTextureManager::CreateTextureManager();
    GLShaderManager::CreateShaderManager();
    SoIDEOutputLogInfo("GLLogicFlowHelpReCreateGLResource : end");
    return true;
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpRelease()
{
    SoIDEOutputLogInfo("GLLogicFlowHelpRelease : begin");
    //if (g_pModelCube)
    //{
    //    SoDelete g_pModelCube;
    //    g_pModelCube = 0;
    //}
    //if (g_pModelRect)
    //{
    //    SoDelete g_pModelRect;
    //    g_pModelRect = NULL;
    //}



    GLCameraUI::ReleaseCameraUI();
    GLCamera::ReleaseCamera();
    GLShaderManager::ReleaseShaderManager();
    GLTextureManager::ReleaseTextureManager();
    GLManager::ReleaseGLManager();
    SoIDEOutputLogInfo("GLLogicFlowHelpRelease : end");
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpPause()
{
    SoIDEOutputLogInfo("GLLogicFlowHelpPause : begin");
    SoIDEOutputLogInfo("GLLogicFlowHelpPause : end");
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpResume()
{
    SoIDEOutputLogInfo("GLLogicFlowHelpResume : begin");
    SoIDEOutputLogInfo("GLLogicFlowHelpResume : end");
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpUpdate(float fDeltaTime)
{
    if (GLCamera::Get())
    {
        GLCamera::Get()->UpdateViewMatrix();
    }
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpPreRender()
{

}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpRender()
{
    GLManager::Get()->BeginRender();

    //if (g_pModelCube)
    //{
    //    g_pModelCube->ModelCubeRender();
    // }
    //if (g_pModelRect)
    //{
    //    g_pModelRect->ModelRectRender();
    //}

    GLManager::Get()->EndRender();
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpSetResolution(int width, int height)
{
    GLFunc_SetResolution((float)width, (float)height);
}
//--------------------------------------------------------------------------------------------------
bool GLLogicFlowHelpShouldReCreateGLResource()
{
    if (GLManager::Get() == NULL)
    {
        //刚刚启动，执行初始化流程，不需要重建GL资源。
        return false;
    }
    else
    {
        //应用程序已经初始化过了，需要重建GL资源。
        return true;
    }
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpDispatchInputMsg(AnInputMsgInfo* pMsgInfo)
{
    /*
    if (g_pModelCube)
    {
        g_pModelCube->ModelProcessInputMsg(pMsgInfo);
        if (pMsgInfo->bSwallowed)
        {
            //  return;
        }
    }


    if (g_pModelRect)
    {
        g_pModelRect->ModelProcessInputMsg(pMsgInfo);
        if (pMsgInfo->bSwallowed)
        {
            return;
        }
    }
    */
}
//--------------------------------------------------------------------------------------------------
