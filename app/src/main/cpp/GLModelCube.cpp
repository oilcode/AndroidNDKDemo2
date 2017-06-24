//--------------------------------------------------------------------------------------------------
#include "GLModelCube.h"
#include "GLShaderManager.h"
#include "GLTextureManager.h"
//--------------------------------------------------------------------------------------------------
GLModelCube::GLModelCube()
:m_pShader(0)
,m_pVertexArray(0)
,m_pIndexArray(0)
,m_nVertexCount(0)
,m_nIndexCount(0)
,m_uiTextureID(0)
{
    InitModelCube();
}
//--------------------------------------------------------------------------------------------------
GLModelCube::~GLModelCube()
{
    ClearModelCube();
}
//--------------------------------------------------------------------------------------------------
void GLModelCube::ModelCubeUpdate()
{

}
//--------------------------------------------------------------------------------------------------
void GLModelCube::ModelCubeRender()
{
    if (m_pShader == 0)
    {
        return;
    }

    GLShaderStandardParam kParam;
    kParam.pVertexArray = (float*)m_pVertexArray;
    kParam.pIndexArray = m_pIndexArray;
    kParam.pMatWorld = &m_kMatWorld;
    kParam.nSizeofVertexStruct = sizeof(stVertexType);
    kParam.nIndexCount = m_nIndexCount;
    kParam.uiTextureID = m_uiTextureID;
    m_pShader->ProcessRender(&kParam);
}
//--------------------------------------------------------------------------------------------------
bool GLModelCube::InitModelCube()
{
    m_pShader = GLShaderManager::Get()->GetShader(GLShader_Standard);
    CreateVertexArray(10.0f, 10.0f, 10.0f);
    CreateIndexArray();
    m_uiTextureID = GLTextureManager::GetInstance()->LoadTextureFile("pic4.png");
    m_kMatWorld.MakeIdentity();
    return true;
}
//--------------------------------------------------------------------------------------------------
void GLModelCube::ClearModelCube()
{
    ReleaseVertexArray();
    ReleaseIndexArray();
}
//--------------------------------------------------------------------------------------------------
bool GLModelCube::CreateVertexArray(float fWidth, float fHeight, float fDepth)
{
    const int nVertexCount = 24;
    stVertexType* pVertexArray = new stVertexType[nVertexCount];
    if (pVertexArray == NULL)
    {
        return false;
    }

    const float width = fWidth * 0.5f;
    const float depth = fDepth * 0.5f;
    const float height = fHeight * 0.5f;
    const SoMathFloat4 color(1.0f, 1.0f, 1.0f, 0.0f);

    //Front
    //此面与Y轴垂直，位于Y轴负方向处。
    //1---2
    //| / |
    //0---3
    int curIndex = 0;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, -depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, -1.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 1.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, -depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, -1.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, -depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, -1.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, -depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, -1.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 1.0f);

    //Back
    //此面与Y轴垂直，位于Y轴正方向处。由于此面位于背面，所以顶点顺序有变化。
    //3---2
    //| / |
    //0---1
    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 1.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 1.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 1.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 1.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 1.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 1.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 0.0f);

    // Left
    //此面与X轴垂直，位于X轴负方向处。
    //1---2
    //| / |
    //0---3
    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(-1.0f, 0.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 1.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(-1.0f, 0.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, -depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(-1.0f, 0.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, -depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(-1.0f, 0.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 1.0f);

    // Right
    //此面与X轴垂直，位于X轴正方向处。
    //1---2
    //| / |
    //0---3
    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, -depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(1.0f, 0.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 1.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, -depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(1.0f, 0.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(1.0f, 0.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(1.0f, 0.0f, 0.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 1.0f);

    // Top
    //此面与Z轴垂直，位于Z轴正方向处。
    //0---1
    //| \ |
    //3---2
    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, 1.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, 1.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, -depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, 1.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 1.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, -depth, height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, 1.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 1.0f);

    // Bottom
    //此面与Z轴垂直，位于Z轴负方向处。
    //0---1
    //| \ |
    //3---2
    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, -depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, -1.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, -depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, -1.0f);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, -1.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 0.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(width, depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, -1.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(1.0f, 1.0f);

    ++curIndex;
    pVertexArray[curIndex].kPosition = SoMathFloat3(-width, depth, -height);
    pVertexArray[curIndex].kNormal = SoMathFloat3(0.0f, 0.0f, -1.0f);
    pVertexArray[curIndex].kColor = color;
    pVertexArray[curIndex].kUV = SoMathFloat2(0.0f, 1.0f);

    m_pVertexArray = pVertexArray;
    m_nVertexCount = nVertexCount;
    return true;
}
//--------------------------------------------------------------------------------------------------
void GLModelCube::ReleaseVertexArray()
{
    if (m_pVertexArray)
    {
        delete[] m_pVertexArray;
        m_pVertexArray = 0;
    }
    m_nVertexCount = 0;
}
//--------------------------------------------------------------------------------------------------
bool GLModelCube::CreateIndexArray()
{
    const int nIndexCount = 36;
    unsigned short* pIndexArray = new unsigned short[nIndexCount];
    if (pIndexArray == NULL)
    {
        return false;
    }

    for (unsigned short i=0; i<6; ++i)
    {
        unsigned short nIndex = i * 6;
        pIndexArray[nIndex+0] = i*4+0;
        pIndexArray[nIndex+1] = i*4+1;
        pIndexArray[nIndex+2] = i*4+2;
        pIndexArray[nIndex+3] = i*4+0;
        pIndexArray[nIndex+4] = i*4+2;
        pIndexArray[nIndex+5] = i*4+3;
    }

    m_pIndexArray = pIndexArray;
    m_nIndexCount = nIndexCount;
    return true;
}
//--------------------------------------------------------------------------------------------------
void GLModelCube::ReleaseIndexArray()
{
    if (m_pIndexArray)
    {
        delete[] m_pIndexArray;
        m_pIndexArray = 0;
    }
    m_nIndexCount = 0;
}
//--------------------------------------------------------------------------------------------------
