//------------------------------------------------------------
#include "GLTextureManager.h"
//------------------------------------------------------------
GLTextureManager* GLTextureManager::ms_pInstance = 0;
//------------------------------------------------------------
bool GLTextureManager::CreateTextureManager()
{
    bool br = true;
    if (ms_pInstance == 0)
    {
        ms_pInstance = new GLTextureManager;
        if (ms_pInstance && ms_pInstance->InitTextureManager())
        {
            br = true;
        }
        else
        {
            ReleaseTextureManager();
            br = false;
        }
    }
	return br;
}
//------------------------------------------------------------
void GLTextureManager::ReleaseTextureManager()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = 0;
	}
}
//------------------------------------------------------------
GLTextureManager::GLTextureManager()
{

}
//------------------------------------------------------------
GLTextureManager::~GLTextureManager()
{
    ClearTextureManager();
}
//------------------------------------------------------------
bool GLTextureManager::InitTextureManager()
{
    if (m_kUITextureArray.InitArray(sizeof(GLTexture*), 10, 10) == false)
    {
        return false;
    }
    if (m_kModelTextureArray.InitArray(sizeof(GLTexture*), 10, 10) == false)
    {
        return false;
    }
    return true;
}
//------------------------------------------------------------
void GLTextureManager::ClearTextureManager()
{
    const int nUITexCount = m_kUITextureArray.GetCapacity();
    GLTexture* pTexture = NULL;
    for (int i = 0; i < nUITexCount; ++i)
    {
        pTexture = GetUITextureByID(i);
        if (pTexture)
        {
            pTexture->ClearTexture();
            delete pTexture;
        }
    }
    m_kUITextureArray.ClearArray();
    m_kUITexName2ID.clear();
    //---------------
    const int nModelTexCount = m_kModelTextureArray.GetCapacity();
    pTexture = NULL;
    for (int i = 0; i < nModelTexCount; ++i)
    {
        pTexture = GetModelTextureByID(i);
        if (pTexture)
        {
            pTexture->ClearTexture();
            delete pTexture;
        }
    }
    m_kModelTextureArray.ClearArray();
    m_kModelTexName2ID.clear();
}
//------------------------------------------------------------
GLTexture* GLTextureManager::CreateUITextureFromFile(const char* pszFileName)
{
    GLTexture* pTexture = NULL;
    if (pszFileName == 0 || pszFileName[0] == 0)
    {
        return pTexture;
    }

    int nTexWidth = 0;
    int nTexHeight = 0;
    GLuint uiResourceID = LoadGLTexResource(pszFileName, false, &nTexWidth, &nTexHeight);
    if (uiResourceID == 0)
    {
        return pTexture;
    }

    pTexture = SoNew GLTexture;
    const int nTextureID = m_kUITextureArray.FillAt(-1, &pTexture);

    std::pair<mapName2TextureID::iterator, bool> insertResult = m_kUITexName2ID.insert(std::make_pair(std::string(pszFileName), nTextureID));
    if (insertResult.second == false)
    {
        glDeleteTextures(1, &uiResourceID);
        m_kUITextureArray.ClearAt(nTextureID);
        SoDelete pTexture;
        pTexture = NULL;
        return pTexture;
    }

    const char* fileName = insertResult.first->first.c_str();
    pTexture->InitTexture(nTextureID, uiResourceID, fileName, nTexWidth, nTexHeight);
    return pTexture;
}
//------------------------------------------------------------
GLTexture* GLTextureManager::CreateModelTextureFromFile(const char* pszFileName)
{
    GLTexture* pTexture = NULL;
    if (pszFileName == 0 || pszFileName[0] == 0)
    {
        return pTexture;
    }

    int nTexWidth = 0;
    int nTexHeight = 0;
    GLuint uiResourceID = LoadGLTexResource(pszFileName, true, &nTexWidth, &nTexHeight);
    if (uiResourceID == 0)
    {
        return pTexture;
    }

    pTexture = SoNew GLTexture;
    const int nTextureID = m_kModelTextureArray.FillAt(-1, &pTexture);

    std::pair<mapName2TextureID::iterator, bool> insertResult = m_kModelTexName2ID.insert(std::make_pair(std::string(pszFileName), nTextureID));
    if (insertResult.second == false)
    {
        glDeleteTextures(1, &uiResourceID);
        m_kModelTextureArray.ClearAt(nTextureID);
        SoDelete pTexture;
        pTexture = NULL;
        return pTexture;
    }

    const char* fileName = insertResult.first->first.c_str();
    pTexture->InitTexture(nTextureID, uiResourceID, fileName, nTexWidth, nTexHeight);
    return pTexture;
}
//------------------------------------------------------------
GLTexture* GLTextureManager::GetUITextureByID(int nTextureID)
{
    void* pElement = m_kUITextureArray.GetAt(nTextureID);
    if (pElement)
    {
        return (*((GLTexture**)pElement));
    }
    else
    {
        return NULL;
    }
}
//------------------------------------------------------------
GLTexture* GLTextureManager::GetModelTextureByID(int nTextureID)
{
    void* pElement = m_kModelTextureArray.GetAt(nTextureID);
    if (pElement)
    {
        return (*((GLTexture**)pElement));
    }
    else
    {
        return NULL;
    }
}
//------------------------------------------------------------
GLuint GLTextureManager::LoadGLTexResource(const char* pszFileName, bool bGenerateMipMap, int* pWidth, int* pHeight)
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

