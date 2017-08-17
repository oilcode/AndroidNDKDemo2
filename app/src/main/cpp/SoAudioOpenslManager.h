//--------------------------------------------------------------------------------------------------
#ifndef _SoAudioOpenslManager_h_
#define _SoAudioOpenslManager_h_
//--------------------------------------------------------------------------------------------------
#include "SoAudioOpenslPlayer.h"
#include "SoArrayUID.h"
//--------------------------------------------------------------------------------------------------
class SoAudioOpenslManager
{
public:
	static bool CreateAudioOpenslManager();
	static void ReleaseAudioOpenslManager();
	static SoAudioOpenslManager* Get();

	SLEngineItf GetSLEngine();
	SLObjectItf GetSLOutputMix();
    SoAudioOpenslPlayer* GetAudioPlayer(int nAudioId);

	int AudioPlay(const char* szResourceName, float fVolume, bool bLoop, bool bEndEvent);
	void AudioStop(int nAudioId);
    void AudioPause(int nAudioId);
    void AudioResume(int nAudioId);

	//--fVolume 音量，取值范围[0.0, 1.0]
	void SetAudioVolume(int nAudioId, float fVolume);

private:
	SoAudioOpenslManager();
	~SoAudioOpenslManager();
	bool InitAudioOpenslManager();
	void ClearAudioOpenslManager();
    SoAudioOpenslPlayer* FindEmptyPlayer(SLuint32 ChannelCount, SLuint32 Frequency, SLuint32 BitsPerSample);

private:
	static SoAudioOpenslManager* ms_pInstance;
	SLObjectItf m_pSLObject;
	SLEngineItf m_pSLEngine;
	SLObjectItf m_pOutputMixObject;
    SoArrayUID m_kPlayerArray;
};
//--------------------------------------------------------------------------------------------------
inline SoAudioOpenslManager* SoAudioOpenslManager::Get()
{
	return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
inline SLEngineItf SoAudioOpenslManager::GetSLEngine()
{
	return m_pSLEngine;
}
//--------------------------------------------------------------------------------------------------
inline SLObjectItf SoAudioOpenslManager::GetSLOutputMix()
{
	return m_pOutputMixObject;
}
//--------------------------------------------------------------------------------------------------
#endif //_SoAudioOpenslManager_h_
//--------------------------------------------------------------------------------------------------
