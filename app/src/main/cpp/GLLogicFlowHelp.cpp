//--------------------------------------------------------------------------------------------------
#include "GLLogicFlowHelp.h"
#include "SoBaseInclude.h"
#include "GLManager.h"
#include "GLTextureManager.h"
#include "GLShaderManager.h"
#include "GLModelCube.h"
//--------------------------------------------------------------------------------------------------
GLModelCube* g_pModelCube = 0;
float g_fTouchPosX = 0.0f;
float g_fTouchPosY = 0.0f;
//--------------------------------------------------------------------------------------------------
bool GLLogicFlowHelpCreateBase()
{
    SoIDEOutputLogInfo("GLLogicFlowHelpCreateBase : begin");
    GLManager::CreateGLManager();
    GLTextureManager::CreateTextureManager();
    GLShaderManager::CreateShaderManager();
    SoIDEOutputLogInfo("GLLogicFlowHelpCreateBase : end");
    return true;
}
//--------------------------------------------------------------------------------------------------
bool GLLogicFlowHelpCreateOther()
{
    SoIDEOutputLogInfo("GLLogicFlowHelpCreateOther : begin");
    g_pModelCube = new GLModelCube;

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

    SoIDEOutputLogInfo("GLLogicFlowHelpCreateOther : end");
    return true;
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpRelease()
{
    SoIDEOutputLogInfo("GLLogicFlowHelpRelease : begin");
    if (g_pModelCube)
    {
        delete g_pModelCube;
        g_pModelCube = 0;
    }

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
void GLLogicFlowHelpResolutionChanged(int width, int height)
{
    SoIDEOutputLogInfo("GLLogicFlowHelpResolutionChanged : begin width[%d] height[%d]", width, height);
    GLManager::Get()->SetResolution(width, height);
    SoIDEOutputLogInfo("GLLogicFlowHelpResolutionChanged : end");
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpUpdate()
{

}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpRender()
{
    GLManager::Get()->BeginRender();
    if (g_pModelCube)
    {
        g_pModelCube->ModelCubeRender();
    }
    GLManager::Get()->EndRender();
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpTouchDown(float fx, float fy)
{
    g_fTouchPosX = fx;
    g_fTouchPosY = fy;
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpTouchMove(float fx, float fy)
{
    float fDeltaX = fx - g_fTouchPosX;
    float fDeltaY = fy - g_fTouchPosY;
    g_fTouchPosX = fx;
    g_fTouchPosY = fy;

    if (fDeltaX < -1.0f || fDeltaX > 1.0f || fDeltaY < -1.0f || fDeltaY > 1.0f)
    {
        //if (g_pModelRect)
        //{
        //    g_pModelRect->SetPosDelta(fDeltaX, fDeltaY);
        //}
    }
}
//--------------------------------------------------------------------------------------------------
void GLLogicFlowHelpTouchUp(float fx, float fy)
{

}
//--------------------------------------------------------------------------------------------------
