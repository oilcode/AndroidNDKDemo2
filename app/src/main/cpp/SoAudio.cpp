//--------------------------------------------------------------------------------------------------
#include "SoAudio.h"
#include "SoAudioResourceMgr.h"
#include "SoAudioOpenslManager.h"
//--------------------------------------------------------------------------------------------------
bool SoAudioCreate()
{
    if (SoAudioResourceMgr::CreateAudioResourceMgr() == false)
    {
        return false;
    }
    if (SoAudioOpenslManager::CreateAudioOpenslManager() == false)
    {
        return false;
    }
	return true;
}
//--------------------------------------------------------------------------------------------------
void SoAudioRelease()
{
    SoAudioOpenslManager::ReleaseAudioOpenslManager();
    SoAudioResourceMgr::ReleaseAudioResourceMgr();
}
//--------------------------------------------------------------------------------------------------
int SoAudioPlay(const char* szResourceName, bool bLoop, bool bEndEvent)
{
    int nAudioId = -1;
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        nAudioId = pManager->AudioPlay(szResourceName, bLoop, bEndEvent);
    }
	return nAudioId;
}
//--------------------------------------------------------------------------------------------------
void SoAudioStop(int nAudioId)
{
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        pManager->AudioStop(nAudioId);
    }
}
//--------------------------------------------------------------------------------------------------
void SoAudioPause(int nAudioId)
{
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        pManager->AudioPause(nAudioId);
    }
}
//--------------------------------------------------------------------------------------------------
void SoAudioResume(int nAudioId)
{
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        pManager->AudioResume(nAudioId);
    }
}
//--------------------------------------------------------------------------------------------------
bool SoAudioPreloadResource(const char* szResourceName)
{
    SoTinyString kName(szResourceName);
    SoAudioResource* pResource = SoAudioResourceMgr::Get()->CreateAudioResource(kName);
	return (pResource != NULL);
}
//--------------------------------------------------------------------------------------------------
void SoAudioRemoveResource(const char* szResourceName)
{

}
//--------------------------------------------------------------------------------------------------
void SoAudioGC()
{

}
//--------------------------------------------------------------------------------------------------
