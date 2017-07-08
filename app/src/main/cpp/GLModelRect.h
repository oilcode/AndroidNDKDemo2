//--------------------------------------------------------------------------------------------------
#ifndef _GLModelRect_h_
#define _GLModelRect_h_
//--------------------------------------------------------------------------------------------------
#include "GLBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class GLShaderBase;
class GLTexture;
//--------------------------------------------------------------------------------------------------
class GLModelRect
{
public:
    GLModelRect();
    ~GLModelRect();
    void ModelRectUpdate();
    void ModelRectRender();
    void ModelProcessInputMsg(AnInputMsgInfo* kMsgInfo);

private:
    struct stVertexType
    {
        SoMathFloat3 kPosition;
        SoMathFloat3 kUVAndTexIndex;
        SoMathFloat4 kColor;
    };

private:
    const GLShaderBase* m_pShader;
    GLTexture* m_pTexture;
    stVertexType* m_pVertexList;
    unsigned short m_usIndexList[6];
};
//--------------------------------------------------------------------------------------------------
#endif //_GLModelRect_h_
//--------------------------------------------------------------------------------------------------
