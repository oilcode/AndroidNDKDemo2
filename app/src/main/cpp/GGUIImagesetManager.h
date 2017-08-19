//----------------------------------------------------------------
#ifndef _GGUIImagesetManager_h_
#define _GGUIImagesetManager_h_
//----------------------------------------------------------------
#include "GGUIImageset.h"
//----------------------------------------------------------------
class GGUIImagesetManager
{
public:
	static bool CreateUIImagesetManager();
	static void ReleaseUIImagesetManager();
	static GGUIImagesetManager* Get();

    GGUIImageset* CreateImageset(const stImagesetParam* pParam);
	GGUIImageset* GetImagesetByID(int nImagesetID);
	GGUIImageset* GetImagesetByName(const SoTinyString& kName);
	int GetImagesetIDByName(const SoTinyString &kName);

private:
	GGUIImagesetManager();
	~GGUIImagesetManager();
	bool InitUIImagesetManager();
	void ClearUIImagesetManager();

private:
	typedef std::map<SoTinyString, int> mapName2Index;

private:
	static GGUIImagesetManager* ms_pInstance;
	SoArrayUID m_kImagesetArray;
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
