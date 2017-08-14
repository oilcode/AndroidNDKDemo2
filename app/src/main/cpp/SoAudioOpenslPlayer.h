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

    void SetVolume(float fVolume);
    float GetVolume() const;
    void SetLoop(bool bLoop);
    bool GetLoop() const;

    int GetAudioID() const;
    bool IsUnused() const;

protected:
    friend class SoAudioOpenslManager;
	SoAudioOpenslPlayer();
	~SoAudioOpenslPlayer();
    bool CreateOpenslObject(SLuint32 ChannelCount, SLuint32 Frequency, SLuint32 BitsPerSample);
    void ReleaseOpenslObject();
    void SetAudioID(int nId);
    bool IsSatisfied(SLuint32 ChannelCount, SLuint32 Frequency, SLuint32 BitsPerSample) const;
    static void CallBack_FillBuffer(SLAndroidSimpleBufferQueueItf bq, void* context);

private:
	SLObjectItf m_pPlayerObject;
	SLPlayItf m_pPlayerPlay;
	SLAndroidSimpleBufferQueueItf m_pPlayerBufferQueue;
	SLVolumeItf m_pPlayerVolume;
    //SLEffectSendItf m_pPlayerEffectSend;
    //设置循环播放，正规的做法是使用 SLSeekItf 组件来设置，
    //但是有些设备不支持该组件，只能使用“播放结束就重新灌一次数据”的方式实现循环播放。
    //SLSeekItf m_pPlayerSeek;
    SoAudioResource* m_pResource;
    int m_nAudioId;
    AudioPlayerState m_eState;
    SLuint32 m_ChannelCount;
    SLuint32 m_Frequency;
    SLuint32 m_BitsPerSample;
	float m_fVolume;
    bool m_bLoop;
    //是否抛出播放结束的事件。
    //bool m_bEndEvent;
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
inline bool SoAudioOpenslPlayer::IsSatisfied(SLuint32 ChannelCount, SLuint32 Frequency, SLuint32 BitsPerSample) const
{
    return (m_ChannelCount==ChannelCount && m_Frequency==Frequency && m_BitsPerSample==BitsPerSample);
}
//--------------------------------------------------------------------------------------------------
inline float SoAudioOpenslPlayer::GetVolume() const
{
    return m_fVolume;
}
//--------------------------------------------------------------------------------------------------
inline bool SoAudioOpenslPlayer::GetLoop() const
{
    return m_bLoop;
}
//--------------------------------------------------------------------------------------------------
#endif //_SoAudioOpenslPlayer_h_
//--------------------------------------------------------------------------------------------------
