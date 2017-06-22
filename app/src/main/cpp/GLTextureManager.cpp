//------------------------------------------------------------
#include "GLTextureManager.h"
#include "SoImageHelp.h"
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
    return true;
}
//------------------------------------------------------------
void GLTextureManager::ClearTextureManager()
{

}
//------------------------------------------------------------
int GLTextureManager::LoadTextureFile(const char* pszFileName)
{
	int theTextureID = 0;
	if (pszFileName == 0 || pszFileName[0] == 0)
	{
		return theTextureID;
	}

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
	GLuint _TextureID;
	glGenTextures(1, &_TextureID);
	//绑定_TextureID，后面的操作都是针对_TextureID贴图
	glBindTexture(GL_TEXTURE_2D, _TextureID);
	//多级分辨率的纹理图像的级数。0表示只有一种分辨率。
	const GLint MipmapLevel = 0;
	const GLsizei Width = (GLsizei)kFileInfo.nWidth;
	const GLsizei Height = (GLsizei)kFileInfo.nHeight;
	//纹理边界宽度，通常设置为0。
	const GLint Border = 0;
	//图像数据
	const GLvoid* Pixels = (GLvoid*)kFileInfo.pData;
	glTexImage2D(GL_TEXTURE_2D, MipmapLevel, ColorComponent, Width, Height, Border, Format, GL_UNSIGNED_BYTE, Pixels);

	//当目标区域小于贴图的原始尺寸时，使用线性过滤方式
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//当目标区域大于贴图的原始尺寸时，使用线性过滤方式
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//
	theTextureID = (int)_TextureID;
	//删除临时数据缓存
	free(kFileInfo.pData);
	kFileInfo.pData = 0;
	return theTextureID;
}
//------------------------------------------------------------
