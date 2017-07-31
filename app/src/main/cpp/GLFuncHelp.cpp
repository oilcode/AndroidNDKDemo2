//--------------------------------------------------------------------------------------------------
#include "GLFuncHelp.h"
//--------------------------------------------------------------------------------------------------
float g_fGLResolutionWidth = 960.0f;
float g_fGLResolutionHeight = 480.0f;
//--------------------------------------------------------------------------------------------------
void GLFunc_SetResolution(float fWidth, float fHeight)
{
    g_fGLResolutionWidth = fWidth;
    g_fGLResolutionHeight = fHeight;
}
//--------------------------------------------------------------------------------------------------
void GLFunc_GetResolution(float* pWidth, float* pHeight)
{
    *pWidth = g_fGLResolutionWidth;
    *pHeight = g_fGLResolutionHeight;
}
//--------------------------------------------------------------------------------------------------
