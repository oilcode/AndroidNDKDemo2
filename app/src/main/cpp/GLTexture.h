//------------------------------------------------------------
#ifndef _GLTexture_h_
#define _GLTexture_h_
//------------------------------------------------------------
#include "GLBaseInclude.h"
//------------------------------------------------------------
class GLTexture
{
    friend class GLTextureManager;
public:
    int GetTextureID() const;
    GLuint GetGLResourceID() const;
    int GetTextureWidth() const;
    int GetTextureHeight() const;
    const char* GetFileName() const;

    void TextureAddRef();
    void TextureRemoveRef();
    int TextureGetRef() const;

protected:
    GLTexture();
    ~GLTexture();
    void InitTexture(int nID, GLuint uiResourceID, const char* pFileName, int nWidth, int nHeight);
    void ClearTexture();

private:
    const char* m_pFileName;
    int m_nTextureID;
    GLuint m_uiGLResourceID;
    int m_nWidth;
    int m_nHeight;
    int m_nRefCount;
};
//------------------------------------------------------------
inline void GLTexture::InitTexture(int nID, GLuint uiResourceID, const char* pFileName, int nWidth, int nHeight)
{
    m_pFileName = pFileName;
    m_nTextureID = nID;
    m_uiGLResourceID = uiResourceID;
    m_nWidth = nWidth;
    m_nHeight = nHeight;
}
//------------------------------------------------------------
inline int GLTexture::GetTextureID() const
{
    return m_nTextureID;
}
//------------------------------------------------------------
inline GLuint GLTexture::GetGLResourceID() const
{
    return m_uiGLResourceID;
}
//------------------------------------------------------------
inline int GLTexture::GetTextureWidth() const
{
    return m_nWidth;
}
//------------------------------------------------------------
inline int GLTexture::GetTextureHeight() const
{
    return m_nHeight;
}
//------------------------------------------------------------
inline const char* GLTexture::GetFileName() const
{
    return m_pFileName;
}
//------------------------------------------------------------
inline void GLTexture::TextureAddRef()
{
    ++m_nRefCount;
}
//------------------------------------------------------------
inline void GLTexture::TextureRemoveRef()
{
    --m_nRefCount;
}
//------------------------------------------------------------
inline int GLTexture::TextureGetRef() const
{
    return m_nRefCount;
}
//------------------------------------------------------------
#endif //_GLTexture_h_
//------------------------------------------------------------
