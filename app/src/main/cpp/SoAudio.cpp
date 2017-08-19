//--------------------------------------------------------------------------------------------------
#include "SoAudio.h"
#include "SoAudioResourceMgr.h"
//--------------------------------------------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
#include "SoAudioOpenslManager.h"
#endif
//--------------------------------------------------------------------------------------------------
bool SoAudioCreate()
{
    if (SoAudioResourceMgr::CreateAudioResourceMgr() == false)
    {
        return false;
    }
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    if (SoAudioOpenslManager::CreateAudioOpenslManager() == false)
    {
        return false;
    }
#endif
	return true;
}
//--------------------------------------------------------------------------------------------------
void SoAudioRelease()
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    SoAudioOpenslManager::ReleaseAudioOpenslManager();
#endif
    SoAudioResourceMgr::ReleaseAudioResourceMgr();
}
//--------------------------------------------------------------------------------------------------
int SoAudioPlay(const char* szResourceName, float fVolume, bool bLoop, bool bEndEvent)
{
    int nAudioId = -1;
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        nAudioId = pManager->AudioPlay(szResourceName, fVolume, bLoop, bEndEvent);
    }
#endif
	return nAudioId;
}
//--------------------------------------------------------------------------------------------------
void SoAudioStop(int nAudioId)
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        pManager->AudioStop(nAudioId);
    }
#endif
}
//--------------------------------------------------------------------------------------------------
void SoAudioPause(int nAudioId)
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        pManager->AudioPause(nAudioId);
    }
#endif
}
//--------------------------------------------------------------------------------------------------
void SoAudioResume(int nAudioId)
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        pManager->AudioResume(nAudioId);
    }
#endif
}
//--------------------------------------------------------------------------------------------------
void SoAudioVolume(int nAudioId, float fVolume)
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    SoAudioOpenslManager* pManager = SoAudioOpenslManager::Get();
    if (pManager)
    {
        pManager->SetAudioVolume(nAudioId, fVolume);
    }
#endif
}
//--------------------------------------------------------------------------------------------------
bool SoAudioPreloadResource(const char* szResourceName)
{
    bool br = false;
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    SoTinyString kName(szResourceName);
    SoAudioResource* pResource = SoAudioResourceMgr::Get()->CreateAudioResource(kName);
    br = (pResource != NULL);
#endif
    return br;
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
