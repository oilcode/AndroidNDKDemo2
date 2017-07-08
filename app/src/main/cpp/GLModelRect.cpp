//--------------------------------------------------------------------------------------------------
#include "GLModelRect.h"
#include "GLManager.h"
#include "GLTextureManager.h"
#include "GLShaderManager.h"
//--------------------------------------------------------------------------------------------------
GLModelRect::GLModelRect()
{
    m_pShader = GLShaderManager::Get()->GetShader(GLShader_GGUI);

    m_pVertexList = SoNew stVertexType[4];
    //左上
    m_pVertexList[0].kPosition = SoMathFloat3(0.0f, 0.0f, -10.5f);
    m_pVertexList[0].kUVAndTexIndex = SoMathFloat3(0.0f, 0.0f, 0.0f);
    m_pVertexList[0].kColor = SoMathFloat4(0.0f, 0.0f, 0.0f, 0.0f);

    //左下
    m_pVertexList[1].kPosition = SoMathFloat3(0.0f, 230.0f, -10.5f);
    m_pVertexList[1].kUVAndTexIndex = SoMathFloat3(0.0f, 1.0f, 0.0f);
    m_pVertexList[1].kColor = SoMathFloat4(0.0f, 0.0f, 0.0f, 0.0f);

    //右下
    m_pVertexList[2].kPosition = SoMathFloat3(230.0f, 230.0f, -10.5f);
    m_pVertexList[2].kUVAndTexIndex = SoMathFloat3(1.0f, 1.0f, 0.0f);
    m_pVertexList[2].kColor = SoMathFloat4(0.0f, 0.0f, 0.0f, 0.0f);

    //右上
    m_pVertexList[3].kPosition = SoMathFloat3(230.0f, 0.0f, -10.5f);
    m_pVertexList[3].kUVAndTexIndex = SoMathFloat3(1.0f, 0.0f, 0.0f);
    m_pVertexList[3].kColor = SoMathFloat4(0.0f, 0.0f, 0.0f, 0.0f);

    m_usIndexList[0] = 0;
    m_usIndexList[1] = 3;
    m_usIndexList[2] = 2;
    m_usIndexList[3] = 0;
    m_usIndexList[4] = 2;
    m_usIndexList[5] = 1;

    m_pTexture = GLTextureManager::Get()->CreateUITextureFromFile("pic3.png");
    m_pTexture->TextureAddRef();
}
//--------------------------------------------------------------------------------------------------
GLModelRect::~GLModelRect()
{
    SoDelete[] m_pVertexList;
    m_pVertexList = NULL;
}
//--------------------------------------------------------------------------------------------------
void GLModelRect::ModelRectUpdate()
{

}
//--------------------------------------------------------------------------------------------------
void GLModelRect::ModelRectRender()
{
    if (m_pShader == 0 || m_pTexture == 0)
    {
        return;
    }

    GLuint theTexId = m_pTexture->GetGLResourceID();

    GLShaderGGUIParam kParam;
    kParam.pVertexArray = (float*)m_pVertexList;
    kParam.pIndexArray = m_usIndexList;
    kParam.nSizeofVertexStruct = sizeof(stVertexType);
    kParam.nVertexOffset = 0;
    kParam.nUVOffset = 3;
    kParam.nColorOffset = 6;
    kParam.nIndexCount = 6;
    kParam.pTexIDList = &theTexId;
    kParam.nTexIDCount = 1;
    m_pShader->ProcessRender(&kParam);
}
//-----------------------------------------------------------------------
void GLModelRect::ModelProcessInputMsg(AnInputMsgInfo* kMsgInfo)
{
    if (kMsgInfo->theType == AnInputMsg_TouchMove)
    {
        kMsgInfo->bSwallowed = true;

        float fDeltaX = kMsgInfo->fDeltaX;
        float fDeltaY = kMsgInfo->fDeltaY;
        if (fDeltaX < -1.0f || fDeltaX > 1.0f || fDeltaY < -1.0f || fDeltaY > 1.0f)
        {
            /*
            int nWidth = 0;
            int nHeight = 0;
            GLManager::Get()->GetResolution(&nWidth, &nHeight);
            const float width = (float)nWidth;
            const float height = (float)nHeight;
            fDeltaX = fDeltaX / width;
            fDeltaY = fDeltaY / height;
            */

            m_pVertexList[0].kPosition.x += fDeltaX;
            m_pVertexList[0].kPosition.y += fDeltaY;
            m_pVertexList[1].kPosition.x += fDeltaX;
            m_pVertexList[1].kPosition.y += fDeltaY;
            m_pVertexList[2].kPosition.x += fDeltaX;
            m_pVertexList[2].kPosition.y += fDeltaY;
            m_pVertexList[3].kPosition.x += fDeltaX;
            m_pVertexList[3].kPosition.y += fDeltaY;
        }
    }
}
//--------------------------------------------------------------------------------------------------

