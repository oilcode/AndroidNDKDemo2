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
    GLuint GetResourceID() const;
    int GetTextureWidth() const;
    int GetTextureHeight() const;
    const char* GetFileName() const;

    void TextureAddRef();
    void TextureRemoveRef();
    int TextureGetRef() const;

protected:
    GLTexture();
    ~GLTexture();
    bool InitTexture(int nID, const char* pFileName, bool bGenerateMipMap);
    void ClearTexture();
    bool ReCreateGLResource();
    GLuint LoadGLTexResource(const char* pszFileName, bool bGenerateMipMap, int* pWidth, int* pHeight);

private:
    const char* m_pFileName;
    int m_nTextureID;
    GLuint m_uiResourceID;
    //宽高值可能会作为除数，除数不能是0，所以宽高的默认值是1.
    int m_nWidth;
    int m_nHeight;
    int m_nRefCount;
    bool m_bGenerateMipMap;
};
//------------------------------------------------------------
inline int GLTexture::GetTextureID() const
{
    return m_nTextureID;
}
//------------------------------------------------------------
inline GLuint GLTexture::GetResourceID() const
{
    return m_uiResourceID;
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
