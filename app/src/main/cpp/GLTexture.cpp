//------------------------------------------------------------
#include "GLTexture.h"
//------------------------------------------------------------
GLTexture::GLTexture()
:m_pFileName("")
,m_nTextureID(-1)
,m_uiResourceID(0)
,m_nWidth(0)
,m_nHeight(0)
,m_nRefCount(0)
{

}
//------------------------------------------------------------
GLTexture::~GLTexture()
{

}
//------------------------------------------------------------
void GLTexture::ClearTexture()
{
    if (m_uiResourceID > 0)
    {
        glDeleteTextures(1, &m_uiResourceID);
    }

    m_pFileName = "";
    m_nTextureID = -1;
    m_uiResourceID = 0;
    m_nWidth = 0;
    m_nHeight = 0;
    m_nRefCount = 0;
}
//------------------------------------------------------------
