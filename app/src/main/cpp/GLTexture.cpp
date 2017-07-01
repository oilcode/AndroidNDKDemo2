//------------------------------------------------------------
#include "GLTexture.h"
//------------------------------------------------------------
GLTexture::GLTexture()
:m_pFileName("")
,m_nTextureID(-1)
,m_uiGLResourceID(0)
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
    if (m_uiGLResourceID > 0)
    {
        glDeleteTextures(1, &m_uiGLResourceID);
    }

    m_pFileName = "";
    m_nTextureID = -1;
    m_uiGLResourceID = 0;
    m_nWidth = 0;
    m_nHeight = 0;
    m_nRefCount = 0;
}
//------------------------------------------------------------
