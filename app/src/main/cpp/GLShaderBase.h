//--------------------------------------------------------------------------------------------------
#ifndef _GLShaderBase_h_
#define _GLShaderBase_h_
//--------------------------------------------------------------------------------------------------
#include "GLBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class GLShaderBase
{
public:
    GLShaderBase();
    virtual ~GLShaderBase();
    virtual void ProcessRender(void* pParam) const;

public:
    static GLuint CreateProgram(const char* szVertexSource, const char* szFragmentSource);

protected:
    static GLuint CompileShader(GLenum eShaderType, const char* szSource);

};
//--------------------------------------------------------------------------------------------------
#endif //_GLShaderBase_h_
//--------------------------------------------------------------------------------------------------
