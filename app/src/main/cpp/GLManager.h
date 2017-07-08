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

    void SetResolution(int newWidth, int newHeight);
    void GetResolution(int* pWidth, int* pHeight);
    float GetResolutionWidth();
    float GetResolutionHeight();

private:
    GLManager();
    ~GLManager();
    bool InitGLManager();
    void ClearGLManager();

private:
    static GLManager* ms_pInstance;
    int m_nResolutionWidth;
    int m_nResolutionHeight;
};
//--------------------------------------------------------------------------------------------------
inline GLManager* GLManager::Get()
{
    return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
inline float GLManager::GetResolutionWidth()
{
    return (float)m_nResolutionWidth;
}
//--------------------------------------------------------------------------------------------------
inline float GLManager::GetResolutionHeight()
{
    return (float)m_nResolutionHeight;
}
//--------------------------------------------------------------------------------------------------
#endif //_GLManager_h_
//--------------------------------------------------------------------------------------------------
