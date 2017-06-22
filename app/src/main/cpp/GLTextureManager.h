//--------------------------------------------------------------------------------------------------
#ifndef _GLTextureManager_h_
#define _GLTextureManager_h_
//--------------------------------------------------------------------------------------------------
#include "GLBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class GLTextureManager
{
public:
	static bool CreateTextureManager();
	static void ReleaseTextureManager();
	static GLTextureManager* GetInstance();

	//加载磁盘文件作为贴图。
	//如果失败，则返回SoTextureID_Invalid。
	int LoadTextureFile(const char* pszFileName);
	
private:
	GLTextureManager();
	~GLTextureManager();
	bool InitTextureManager();
	void ClearTextureManager();

private:
	static GLTextureManager* ms_pInstance;
private:

};
//--------------------------------------------------------------------------------------------------
inline GLTextureManager* GLTextureManager::GetInstance()
{
	return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
#endif //_GLTextureManager_h_
//--------------------------------------------------------------------------------------------------
