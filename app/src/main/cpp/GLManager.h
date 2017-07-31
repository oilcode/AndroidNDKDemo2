//--------------------------------------------------------------------------------------------------
#ifndef _GLManager_h_
#define _GLManager_h_
//--------------------------------------------------------------------------------------------------
#include "GLBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class GLManager
{
public:
    static bool CreateGLManager();
    static void ReleaseGLManager();
    static GLManager* Get();

    void BeginRender();
    void EndRender();

private:
    GLManager();
    ~GLManager();
    bool InitGLManager();
    void ClearGLManager();
    void ReInitGLResource();

private:
    static GLManager* ms_pInstance;
};
//--------------------------------------------------------------------------------------------------
inline GLManager* GLManager::Get()
{
    return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
inline void GLManager::BeginRender()
{
    //清除后台缓冲区。
    //用背景色填充颜色缓冲区，用默认深度值填充深度缓冲区。
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//--------------------------------------------------------------------------------------------------
inline void GLManager::EndRender()
{

}
//--------------------------------------------------------------------------------------------------
#endif //_GLManager_h_
//--------------------------------------------------------------------------------------------------
