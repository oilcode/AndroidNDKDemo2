//----------------------------------------------------------------
#ifndef _GGUIImagesetManager_h_
#define _GGUIImagesetManager_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
#include "GGUIImageset.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
struct stImagesetParam
{
	//Imageset的名字。
	SoTinyString kName;
	//预分配多少个GGUIRect。
	int nInitRectCount;
	//贴图对象。
	GLTexture* pD3DTexture;
};
//----------------------------------------------------------------
class GGUIImagesetManager
{
public:
	static bool CreateUIImagesetManager();
	static void ReleaseUIImagesetManager();
	static GGUIImagesetManager* Get();

	//创建一个新的Imageset对象。
	//返回值为ImagesetID。
	int CreateImageset(const stImagesetParam& kParam);
	int GetImagesetIndex(const SoTinyString& kName);
	GGUIImageset* GetImagesetByID(int nImagesetID);
	GGUIImageset* GetImagesetByName(const SoTinyString& kName);

private:
	GGUIImagesetManager();
	~GGUIImagesetManager();
	bool InitUIImagesetManager();
	void ClearUIImagesetManager();

private:
	typedef std::map<SoTinyString, int> mapName2Index;

private:
	static GGUIImagesetManager* ms_pInstance;
	//数组，存储的元素是GGUIImageset*。
	SoArrayUID m_kImagesetArray;
	//Imageset名字到Imageset序号的映射。
	mapName2Index m_kName2IndexMap;
};
//----------------------------------------------------------------
inline GGUIImagesetManager* GGUIImagesetManager::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_GGUIImagesetManager_h_
//----------------------------------------------------------------
