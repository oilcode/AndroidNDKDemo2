//------------------------------------------------------------
#include "GLTexture.h"
//------------------------------------------------------------
GLTexture::GLTexture()
:m_pFileName("")
,m_nTextureID(-1)
,m_uiResourceID(0)
,m_nWidth(1)
,m_nHeight(1)
,m_nRefCount(0)
,m_bGenerateMipMap(false)
{

}
//------------------------------------------------------------
GLTexture::~GLTexture()
{

}
//------------------------------------------------------------
bool GLTexture::InitTexture(int nID, const char* pFileName, bool bGenerateMipMap)
{
    int nTexWidth = 0;
    int nTexHeight = 0;
    GLuint uiResourceID = LoadGLTexResource(pFileName, bGenerateMipMap, &nTexWidth, &nTexHeight);
    if (uiResourceID == 0)
    {
        return false;
    }

    m_pFileName = pFileName;
    m_nTextureID = nID;
    m_uiResourceID = uiResourceID;
    m_nWidth = nTexWidth;
    m_nHeight = nTexHeight;
    m_bGenerateMipMap = bGenerateMipMap;
    return true;
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
    m_nWidth = 1;
    m_nHeight = 1;
    m_nRefCount = 0;
    m_bGenerateMipMap = false;
}
//------------------------------------------------------------
bool GLTexture::ReCreateGLResource()
{
    m_uiResourceID = 0;

    int nTexWidth = 0;
    int nTexHeight = 0;
    GLuint uiResourceID = LoadGLTexResource(m_pFileName, m_bGenerateMipMap, &nTexWidth, &nTexHeight);
    if (uiResourceID == 0)
    {
        return false;
    }

    m_uiResourceID = uiResourceID;
    return true;
}
//------------------------------------------------------------
GLuint GLTexture::LoadGLTexResource(const char* pszFileName, bool bGenerateMipMap, int* pWidth, int* pHeight)
{
    GLuint theTextureID = 0;

    SoImageFileInfo kFileInfo;
    if (SoImageHelp::LoadImageFile(pszFileName, &kFileInfo) == false)
    {
        return theTextureID;
    }

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //根据图像信息，决定ColorComponent和Format两个变量的值，这两个变量用于创建OpenGL贴图。
    //是一个从1到4的整数，指出选择了R、G、B、A中的哪些分量用于调整和混合，
    //1表示选择了R分量，2表示选择了R和A两个分量，3表示选择了R、G、B三个分量，4表示选择了R、G、B、A四个分量。
    GLint ColorComponent = 0;
    //图像格式
    GLenum Format = 0;
    //
    if (kFileInfo.theColorType == SoImageColor_RGBA)
    {
        //这两个的取值必须相同。
        ColorComponent = GL_RGBA;
        Format = GL_RGBA;
    }
    else if (kFileInfo.theColorType == SoImageColor_RGB)
    {
        //这两个的取值必须相同。
        ColorComponent = GL_RGB;
        Format = GL_RGB;
    }
    else
    {
        //错误，不支持的格式。
        return theTextureID;
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //申请一个贴图纹理序号ID
    glGenTextures(1, &theTextureID);
    //绑定 theTextureID ，后面的操作都是针对 theTextureID 贴图
    glBindTexture(GL_TEXTURE_2D, theTextureID);

    //Mipmap层级。值为0表示分辨率最大的那一层级。
    //该参数的含义是，把像素数据填充成目标纹理的哪个Mipmap层级。
    //一般情况下，这里的像素数据就是原图片的像素数据，也就是第0层级。
    const GLint MipmapLevel = 0;
    const GLsizei Width = (GLsizei)kFileInfo.nWidth;
    const GLsizei Height = (GLsizei)kFileInfo.nHeight;
    //纹理边界宽度，通常设置为0。
    const GLint Border = 0;
    //图像数据
    const GLvoid* Pixels = (GLvoid*)kFileInfo.pData;
    glTexImage2D(GL_TEXTURE_2D, MipmapLevel, ColorComponent, Width, Height, Border, Format, GL_UNSIGNED_BYTE, Pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (bGenerateMipMap)
    {
        //当目标区域小于贴图的原始尺寸时，使用三线性过滤方式
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //当目标区域大于贴图的原始尺寸时，使用三线性过滤方式
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //为当前绑定的纹理生成mipmap。
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        //当目标区域小于贴图的原始尺寸时，使用线性过滤方式
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //当目标区域大于贴图的原始尺寸时，使用线性过滤方式
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    if (pWidth)
    {
        *pWidth = kFileInfo.nWidth;
    }
    if (pHeight)
    {
        *pHeight = kFileInfo.nHeight;
    }

    return theTextureID;
}
//------------------------------------------------------------
