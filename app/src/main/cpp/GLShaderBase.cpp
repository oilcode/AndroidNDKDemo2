//--------------------------------------------------------------------------------------------------
#include "GLShaderBase.h"
//--------------------------------------------------------------------------------------------------
GLShaderBase::GLShaderBase()
{

}
//--------------------------------------------------------------------------------------------------
GLShaderBase::~GLShaderBase()
{

}
//--------------------------------------------------------------------------------------------------
void GLShaderBase::ReCreateGLResource()
{

}
//--------------------------------------------------------------------------------------------------
void GLShaderBase::ProcessRender(void* pParam) const
{

}
//--------------------------------------------------------------------------------------------------
GLuint GLShaderBase::CreateProgram(const char* szVertexSource, const char* szFragmentSource)
{
    GLuint uiVertexHandle = CompileShader(GL_VERTEX_SHADER, szVertexSource);
    if (uiVertexHandle == 0)
    {
        return 0;
    }

    GLuint uiFragmentHandle = CompileShader(GL_FRAGMENT_SHADER, szFragmentSource);
    if (uiFragmentHandle == 0)
    {
        glDeleteShader(uiVertexHandle);
        return 0;
    }

    GLuint uiProgramHandle = glCreateProgram();
    if (uiProgramHandle == 0)
    {
        glDeleteShader(uiVertexHandle);
        glDeleteShader(uiFragmentHandle);
        return 0;
    }

    glAttachShader(uiProgramHandle, uiVertexHandle);
    glAttachShader(uiProgramHandle, uiFragmentHandle);
    glLinkProgram(uiProgramHandle);

    //不管链接是否成功，都尝试打印出编译回馈信息。
    //这里总是出现无法解析的字符串，所以不再输出调试信息。
    /*
    GLint nLinkInfoLen = 0;
    glGetProgramiv(uiProgramHandle, GL_INFO_LOG_LENGTH, &nLinkInfoLen);
    if (nLinkInfoLen > 0)
    {
        char* buff = (char*)malloc(nLinkInfoLen+1);
        if (buff)
        {
            buff[nLinkInfoLen] = 0;
            glGetProgramInfoLog(uiProgramHandle, nLinkInfoLen, NULL, buff);
            SoIDEOutputLogf("%s", buff);
#ifdef SoMessageBoxEnable
            SoMessageBox("shader error", buff);
#endif
            free(buff);
            buff = 0;
        }
    }
     */

    //删除不需要的数据。
    glDetachShader(uiProgramHandle, uiVertexHandle);
    glDetachShader(uiProgramHandle, uiFragmentHandle);
    glDeleteShader(uiVertexHandle);
    glDeleteShader(uiFragmentHandle);

    //检查链接是否成功。
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(uiProgramHandle, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        glDeleteProgram(uiProgramHandle);
        uiProgramHandle = 0;
    }

    return uiProgramHandle;
}
//--------------------------------------------------------------------------------------------------
GLuint GLShaderBase::CompileShader(GLenum eShaderType, const char* szSource)
{
    GLuint uiShaderHandle = glCreateShader(eShaderType);
    if (uiShaderHandle == 0)
    {
        return 0;
    }

    glShaderSource(uiShaderHandle, 1, &szSource, NULL);
    glCompileShader(uiShaderHandle);

    //不管编译是否成功，都尝试打印出编译回馈信息。
    GLint nCompileInfoLen = 0;
    glGetShaderiv(uiShaderHandle, GL_INFO_LOG_LENGTH, &nCompileInfoLen);
    if (nCompileInfoLen > 0)
    {
        char* buff = (char*)malloc(nCompileInfoLen+1);
        if (buff)
        {
            buff[nCompileInfoLen] = 0;
            glGetShaderInfoLog(uiShaderHandle, nCompileInfoLen, NULL, buff);
            SoIDEOutputLog(buff);
#ifdef SoMessageBoxEnable
            SoMessageBox("shader error", buff);
#endif
            free(buff);
            buff = 0;
        }
    }

    //检查编译是否成功。
    GLint nCompileResult = GL_FALSE;
    glGetShaderiv(uiShaderHandle, GL_COMPILE_STATUS, &nCompileResult);
    if (nCompileResult == GL_FALSE)
    {
        glDeleteShader(uiShaderHandle);
        uiShaderHandle = 0;
    }

    return uiShaderHandle;
}
//--------------------------------------------------------------------------------------------------
