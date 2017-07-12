//--------------------------------------------------------------------------------------------------
#ifndef _GLShaderGGUI_h_
#define _GLShaderGGUI_h_
//--------------------------------------------------------------------------------------------------
#include "GLShaderBase.h"
//--------------------------------------------------------------------------------------------------
#define GLShaderGGUI_MaxTexSamplerCount 8
//--------------------------------------------------------------------------------------------------
struct GLShaderGGUIParam
{
    const float* pVertexArray;
    const unsigned short* pIndexArray;
    const GLuint* pTexIDList;
    int nSizeofVertexStruct;
    int nVertexOffset;
    int nUVOffset;
    int nColorOffset;
    int nIndexCount;
    int nTexIDCount;
};
//--------------------------------------------------------------------------------------------------
class GLShaderGGUI : public GLShaderBase
{
public:
    GLShaderGGUI();
    ~GLShaderGGUI();
    void ProcessRender(void* pParam) const;

private:
    GLuint m_uiProgramID;
    GLuint m_uiVertexID;
    GLuint m_uiUVID;
    GLuint m_uiColorID;
    GLuint m_uiMatProjectViewID;
    GLuint m_uiTexSamplerID;
    GLint m_kSamplerUnitList[GLShaderGGUI_MaxTexSamplerCount];
};
//--------------------------------------------------------------------------------------------------
#endif //_GLShaderGGUI_h_
//--------------------------------------------------------------------------------------------------
