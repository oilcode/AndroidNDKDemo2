//--------------------------------------------------------------------------------------------------
#ifndef _GLModelCube_h_
#define _GLModelCube_h_
//--------------------------------------------------------------------------------------------------
#include "GLBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class GLShaderBase;
class GLTexture;
struct stInputMsgInfo;
//--------------------------------------------------------------------------------------------------
class GLModelCube
{
public:
    GLModelCube();
    ~GLModelCube();

    void ModelCubeUpdate();
    void ModelCubeRender();
    void ModelProcessInputMsg(stInputMsgInfo* kMsgInfo);
    void SetDeltaPitchYaw(float fDeltaPitch, float fDeltaYaw);

private:
    struct stVertexType
    {
        SoMathFloat3 kPosition;
        SoMathFloat3 kNormal;
        SoMathFloat4 kColor;
        SoMathFloat2 kUV;
    };

private:
    bool InitModelCube();
    void ClearModelCube();
    bool CreateVertexArray(float fWidth, float fHeight, float fDepth);
    void ReleaseVertexArray();
    bool CreateIndexArray();
    void ReleaseIndexArray();

private:
    const GLShaderBase* m_pShader;
    stVertexType* m_pVertexArray;
    unsigned short* m_pIndexArray;
    GLTexture* m_pTexture;
    int m_nVertexCount;
    int m_nIndexCount;
    SoMathMatrix4 m_kMatWorld;
    float m_fPitch;
    float m_fYaw;
};
//--------------------------------------------------------------------------------------------------
#endif //_GLModelCube_h_
//--------------------------------------------------------------------------------------------------
