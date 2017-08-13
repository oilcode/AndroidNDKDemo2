//----------------------------------------------------------------
#ifndef _SoAudioResourceMgr_h_
#define _SoAudioResourceMgr_h_
//----------------------------------------------------------------
#include "SoTinyString.h"
#include "SoArrayUID.h"
#include "SoAudioResource.h"
//----------------------------------------------------------------
class SoAudioResourceMgr
{
public:
	static bool CreateAudioResourceMgr();
	static void ReleaseAudioResourceMgr();
	static SoAudioResourceMgr* Get();

	//获取或者创建一个Resource对象。
	//外界想删除一个Resource对象，只需调用 SoAudioResource::AudioRemoveRef 函数。
	SoAudioResource* CreateAudioResource(const SoTinyString& kResourceName);
    SoAudioResource* GetAudioResource(int nResourceId);
    int GetAudioResourceID(const SoTinyString& kResourceName);

private:
	SoAudioResourceMgr();
	~SoAudioResourceMgr();
	bool InitAudioResourceMgr();
	void ClearAudioResourceMgr();

private:
	typedef std::map<SoTinyString, int> mapName2ID;

private:
    static SoAudioResourceMgr* ms_pInstance;
    //数组，存储的元素是 SoAudioResource*。
    SoArrayUID m_kResourceArray;
	mapName2ID m_kResourceMap;
};
//----------------------------------------------------------------
inline SoAudioResourceMgr* SoAudioResourceMgr::Get()
{
    return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_SoAudioResourceMgr_h_
//----------------------------------------------------------------
