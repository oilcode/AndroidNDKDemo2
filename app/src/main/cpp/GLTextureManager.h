//--------------------------------------------------------------------------------------------------
#ifndef _GLTextureManager_h_
#define _GLTextureManager_h_
//--------------------------------------------------------------------------------------------------
#include "GLBaseInclude.h"
#include "GLTexture.h"
//--------------------------------------------------------------------------------------------------
class GLTextureManager
{
public:
	static bool CreateTextureManager();
	static void ReleaseTextureManager();
	static GLTextureManager* Get();

    GLTexture* CreateUITextureFromFile(const char* pszFileName);
    GLTexture* GetUITextureByID(int nTextureID);

    GLTexture* CreateModelTextureFromFile(const char* pszFileName);
    GLTexture* GetModelTextureByID(int nTextureID);
	
private:
	GLTextureManager();
	~GLTextureManager();
	bool InitTextureManager();
	void ClearTextureManager();
    GLuint LoadGLTexResource(const char* pszFileName, bool bGenerateMipMap, int* pWidth, int* pHeight);

private:
	typedef std::map<std::string, int> mapName2TextureID;

private:
	static GLTextureManager* ms_pInstance;
    SoArrayUID m_kUITextureArray;
    SoArrayUID m_kModelTextureArray;
    mapName2TextureID m_kUITexName2ID;
    mapName2TextureID m_kModelTexName2ID;
};
//--------------------------------------------------------------------------------------------------
inline GLTextureManager* GLTextureManager::Get()
{
	return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
#endif //_GLTextureManager_h_
//--------------------------------------------------------------------------------------------------
