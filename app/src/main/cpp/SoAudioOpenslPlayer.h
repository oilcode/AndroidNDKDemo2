//--------------------------------------------------------------------------------------------------
#ifndef _SoAudioOpenslPlayer_h_
#define _SoAudioOpenslPlayer_h_
//--------------------------------------------------------------------------------------------------
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "SoCodeBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class SoAudioResource;
//--------------------------------------------------------------------------------------------------
enum AudioPlayerState
{
    AudioPlayerState_Play,
    AudioPlayerState_Pause,
    AudioPlayerState_Stop,
};
//--------------------------------------------------------------------------------------------------
class SoAudioOpenslPlayer
{
public:
	bool AudioPlayerPlay(SoAudioResource *pResource);
	void AudioPlayerStop();
    void AudioPlayerPause();
    void AudioPlayerResume();
    int GetAudioID() const;
    bool IsUnused() const;

protected:
    friend class SoAudioOpenslManager;
	SoAudioOpenslPlayer();
	~SoAudioOpenslPlayer();
    bool CreateOpenslObject();
    void ReleaseOpenslObject();
    void SetAudioID(int nId);
    static void CallBack_FillBuffer(SLAndroidSimpleBufferQueueItf bq, void* context);

private:
	SLObjectItf m_pPlayerObject;
	SLPlayItf m_pPlayerPlay;
	SLAndroidSimpleBufferQueueItf m_pPlayerBufferQueue;
	SLEffectSendItf m_pPlayerEffectSend;
	SLVolumeItf m_pPlayerVolume;
    SoAudioResource* m_pResource;
    int m_nAudioId;
    AudioPlayerState m_eState;
};
//--------------------------------------------------------------------------------------------------
inline void SoAudioOpenslPlayer::SetAudioID(int nId)
{
    m_nAudioId = nId;
}
//--------------------------------------------------------------------------------------------------
inline int SoAudioOpenslPlayer::GetAudioID() const
{
    return m_nAudioId;
}
//--------------------------------------------------------------------------------------------------
inline bool SoAudioOpenslPlayer::IsUnused() const
{
    return (m_eState == AudioPlayerState_Stop);
}
//--------------------------------------------------------------------------------------------------
#endif //_SoAudioOpenslPlayer_h_
//--------------------------------------------------------------------------------------------------
