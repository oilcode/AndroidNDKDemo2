//--------------------------------------------------------------------------------------------------
#include "GLManager.h"
#include "GLFuncHelp.h"
//--------------------------------------------------------------------------------------------------
GLManager* GLManager::ms_pInstance = 0;
//--------------------------------------------------------------------------------------------------
bool GLManager::CreateGLManager()
{
    bool br = true;
    if (ms_pInstance == 0)
    {
        ms_pInstance = new GLManager;
        if (ms_pInstance && ms_pInstance->InitGLManager())
        {
            br = true;
        }
        else
        {
            ReleaseGLManager();
            br = false;
        }
    }
    else
    {
        ms_pInstance->ReInitGLResource();
    }
    return br;
}
//--------------------------------------------------------------------------------------------------
void GLManager::ReleaseGLManager()
{
    if (ms_pInstance)
    {
        delete ms_pInstance;
        ms_pInstance = 0;
    }
}
//--------------------------------------------------------------------------------------------------
GLManager::GLManager()
{

}
//--------------------------------------------------------------------------------------------------
GLManager::~GLManager()
{
    ClearGLManager();
}
//--------------------------------------------------------------------------------------------------
bool GLManager::InitGLManager()
{
    ReInitGLResource();
    return true;
}
//--------------------------------------------------------------------------------------------------
void GLManager::ClearGLManager()
{

}
//--------------------------------------------------------------------------------------------------
void GLManager::ReInitGLResource()
{
    //开启剔除功能。
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);
    //设置成剔除背面。
    glCullFace(GL_BACK);
    //把逆时针方向设置成正面；顺时针方向的绕序被认为是背面，不进行绘制。
    glFrontFace(GL_CCW);

    //开启2D纹理。这句代码在opengles1.0版本中是需要的，在2.0版本中已经不需要调用了。
    //glEnable(GL_TEXTURE_2D);

    //开启深度检测。
    glEnable(GL_DEPTH_TEST);
    //设置深度检测的规则。
    glDepthFunc(GL_LEQUAL);
    //设置默认深度值。
    glClearDepthf(1.0f);

    //设置背景色。
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    //开启颜色混合功能。
    glEnable(GL_BLEND);
    //设置颜色混合的规则。
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //设置视口。
    float fWidth = 0.0f;
    float fHeight = 0.0f;
    GLFunc_GetResolution(&fWidth, &fHeight);
    GLsizei nW = (GLsizei)(fWidth + 0.5f);
    GLsizei nH = (GLsizei)(fHeight + 0.5f);
    glViewport(0, 0, nW, nH);
}
//--------------------------------------------------------------------------------------------------
