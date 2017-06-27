//--------------------------------------------------------------------------------------------------
#include "GLManager.h"
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
:m_nResolutionWidth(0)
,m_nResolutionHeight(0)
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
    //开启剔除功能。
    glEnable(GL_CULL_FACE);
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

    return true;
}
//--------------------------------------------------------------------------------------------------
void GLManager::ClearGLManager()
{

}
//--------------------------------------------------------------------------------------------------
void GLManager::BeginRender()
{
    //清除后台缓冲区。
    //用背景色填充颜色缓冲区，用默认深度值填充深度缓冲区。
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//--------------------------------------------------------------------------------------------------
void GLManager::EndRender()
{

}
//--------------------------------------------------------------------------------------------------
void GLManager::SetResolution(int newWidth, int newHeight)
{
    m_nResolutionWidth = newWidth;
    m_nResolutionHeight = newHeight;
    //设置视口。
    glViewport(0, 0, newWidth, newHeight);
}
//--------------------------------------------------------------------------------------------------
void GLManager::GetResolution(int* pWidth, int* pHeight)
{
    *pWidth = m_nResolutionWidth;
    *pHeight = m_nResolutionHeight;
}
//--------------------------------------------------------------------------------------------------
