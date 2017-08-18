//--------------------------------------------------------------------------------------------------
#include "SoAudioOpenslPlayer.h"
#include "SoAudioOpenslManager.h"
#include "SoAudioResource.h"
#include "SoMessageBox.h"
#include <math.h>
//--------------------------------------------------------------------------------------------------
SoAudioOpenslPlayer::SoAudioOpenslPlayer()
:m_pPlayerObject(NULL)
,m_pPlayerPlay(NULL)
,m_pPlayerBufferQueue(NULL)
,m_pPlayerVolume(NULL)
//,m_pPlayerEffectSend(NULL)
//,m_pPlayerSeek(NULL)
,m_pResource(NULL)
,m_nAudioId(-1)
,m_eState(AudioPlayerState_Stop)
,m_ChannelCount(0)
,m_Frequency(0)
,m_BitsPerSample(0)
,m_fVolume(1.0f)
,m_bLoop(false)
{
    pthread_mutex_init(&m_Lock, NULL);
}
//--------------------------------------------------------------------------------------------------
SoAudioOpenslPlayer::~SoAudioOpenslPlayer()
{
    ReleaseOpenslObject();
    pthread_mutex_destroy(&m_Lock);
}
//--------------------------------------------------------------------------------------------------
bool SoAudioOpenslPlayer::CreateOpenslObject(SLuint32 ChannelCount, SLuint32 Frequency, SLuint32 BitsPerSample)
{
    SLEngineItf pSLEngine = SoAudioOpenslManager::Get()->GetSLEngine();
    SLObjectItf pSLOutputMix = SoAudioOpenslManager::Get()->GetSLOutputMix();

    SLresult result = SL_RESULT_SUCCESS;
    do
    {
        const SLuint32 BackBufferCount = 3;
        const SLuint32 ContainerSize = BitsPerSample;
        const SLuint32 ChannelMask = (ChannelCount == 1) ? SL_SPEAKER_FRONT_CENTER : (SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT);

        SLDataLocator_AndroidSimpleBufferQueue loc_bufq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, BackBufferCount };
        SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, ChannelCount, Frequency, BitsPerSample, ContainerSize, ChannelMask, SL_BYTEORDER_LITTLEENDIAN };
        SLDataSource audioSrc = { &loc_bufq, &format_pcm };
        SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, pSLOutputMix };
        SLDataSink audioSnk = { &loc_outmix, NULL };

        const SLuint32 InterfaceCount = 2;
        const SLInterfaceID ids[2] = { SL_IID_BUFFERQUEUE, SL_IID_VOLUME };
        const SLboolean req[2] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
        result = (*pSLEngine)->CreateAudioPlayer(pSLEngine, &m_pPlayerObject, &audioSrc, &audioSnk, InterfaceCount, ids, req);
        if (result != SL_RESULT_SUCCESS)
        {
#ifdef SoMessageBoxEnable
            SoMessageBox("", "SoAudioOpenslPlayer : CreateAudioPlayer fail");
#endif
            break;
        }

        result = (*m_pPlayerObject)->Realize(m_pPlayerObject, SL_BOOLEAN_FALSE);
        if (result != SL_RESULT_SUCCESS)
        {
#ifdef SoMessageBoxEnable
            SoMessageBox("", "SoAudioOpenslPlayer : (*m_pPlayerObject)->Realize fail");
#endif
            break;
        }

        result = (*m_pPlayerObject)->GetInterface(m_pPlayerObject, SL_IID_PLAY, &m_pPlayerPlay);
        if (result != SL_RESULT_SUCCESS)
        {
#ifdef SoMessageBoxEnable
            SoMessageBox("", "SoAudioOpenslPlayer : get m_pPlayerPlay fail");
#endif
            break;
        }

        // get the buffer queue interface
        result = (*m_pPlayerObject)->GetInterface(m_pPlayerObject, SL_IID_BUFFERQUEUE, &m_pPlayerBufferQueue);
        if (result != SL_RESULT_SUCCESS)
        {
#ifdef SoMessageBoxEnable
            SoMessageBox("", "SoAudioOpenslPlayer : get m_pPlayerBufferQueue fail");
#endif
            break;
        }

        // get the volume interface
        result = (*m_pPlayerObject)->GetInterface(m_pPlayerObject, SL_IID_VOLUME, &m_pPlayerVolume);
        if (result != SL_RESULT_SUCCESS)
        {
#ifdef SoMessageBoxEnable
            SoMessageBox("", "SoAudioOpenslPlayer : get m_pPlayerVolume fail");
#endif
            break;
        }

        // register callback on the buffer queue
        result = (*m_pPlayerBufferQueue)->RegisterCallback(m_pPlayerBufferQueue, SoAudioOpenslPlayer::CallBack_FillBuffer, this);
        if (result != SL_RESULT_SUCCESS)
        {
#ifdef SoMessageBoxEnable
            SoMessageBox("", "SoAudioOpenslPlayer : RegisterCallback fail");
#endif
            break;
        }

    } while (0);

    if (result != SL_RESULT_SUCCESS)
    {
        ReleaseOpenslObject();
        return false;
    }

    m_ChannelCount = ChannelCount;
    m_Frequency = Frequency;
    m_BitsPerSample = BitsPerSample;
    return true;
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::ReleaseOpenslObject()
{
    if (m_pPlayerObject)
    {
        (*m_pPlayerObject)->Destroy(m_pPlayerObject);
        m_pPlayerObject = NULL;
        m_pPlayerPlay = NULL;
        m_pPlayerBufferQueue = NULL;
        m_pPlayerVolume = NULL;
        //m_pPlayerEffectSend = NULL;
        //m_pPlayerSeek = NULL;
    }
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::DoSafeStop()
{
    //加锁
    pthread_mutex_lock(&m_Lock);

    if (m_eState != AudioPlayerState_Stop)
    {
        if (m_pResource)
        {
            m_pResource->AudioRemoveRef();
            m_pResource = NULL;
        }
        m_eState = AudioPlayerState_Stop;
    }

    //解锁
    pthread_mutex_unlock(&m_Lock);
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::CallBack_FillBuffer(SLAndroidSimpleBufferQueueItf bq, void* context)
{
    //这个回调函数所在的线程是音频线程，
    //而 SoAudioOpenslPlayer 对象资源所在的线程是OpenGL渲染线程，
    //这里要使用线程安全的函数。
    SoAudioOpenslPlayer* pPlayer = (SoAudioOpenslPlayer*)context;
    if (pPlayer->m_bLoop)
    {
        SoAudioResource* pResource = pPlayer->m_pResource;
        (*bq)->Enqueue(bq, pResource->GetAudioData(), pResource->GetAudioDataSize());
        //if (result == SL_RESULT_BUFFER_INSUFFICIENT) //buff不足
    }
    else
    {
        pPlayer->DoSafeStop();
    }
}
//--------------------------------------------------------------------------------------------------
bool SoAudioOpenslPlayer::AudioPlayerPlay(SoAudioResource *pResource)
{
    if (pResource == NULL)
    {
        return false;
    }

    if (m_eState != AudioPlayerState_Stop)
    {
#ifdef SoMessageBoxEnable
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerPlay : m_eState != AudioPlayerState_Stop");
#endif
        return false;
    }

    SLresult result = (*m_pPlayerBufferQueue)->Enqueue(m_pPlayerBufferQueue, pResource->GetAudioData(), pResource->GetAudioDataSize());
    if (result != SL_RESULT_SUCCESS)
    {
#ifdef SoMessageBoxEnable
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerPlay : m_pPlayerBufferQueue->Enqueue fail");
#endif
        return false;
    }

    // set the player's state to playing
    result = (*m_pPlayerPlay)->SetPlayState(m_pPlayerPlay, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS)
    {
#ifdef SoMessageBoxEnable
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerPlay : (*m_pPlayerPlay)->SetPlayState fail");
#endif
        return false;
    }

    if (m_pResource)
    {
        m_pResource->AudioRemoveRef();
        m_pResource = NULL;
    }
    m_pResource = pResource;
    m_pResource->AudioAddRef();

    m_eState = AudioPlayerState_Play;
    return true;
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::AudioPlayerStop()
{
    (*m_pPlayerPlay)->SetPlayState(m_pPlayerPlay, SL_PLAYSTATE_STOPPED);
    (*m_pPlayerBufferQueue)->Clear(m_pPlayerBufferQueue);
    DoSafeStop();
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::AudioPlayerPause()
{
    (*m_pPlayerPlay)->SetPlayState(m_pPlayerPlay, SL_PLAYSTATE_STOPPED);
    (*m_pPlayerBufferQueue)->Clear(m_pPlayerBufferQueue);
    m_eState = AudioPlayerState_Pause;
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::AudioPlayerResume()
{
    if (m_pResource == NULL)
    {
        return;
    }

    SLresult result = (*m_pPlayerBufferQueue)->Enqueue(m_pPlayerBufferQueue, m_pResource->GetAudioData(), m_pResource->GetAudioDataSize());
    if (result != SL_RESULT_SUCCESS)
    {
#ifdef SoMessageBoxEnable
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerResume : m_pPlayerBufferQueue->Enqueue fail");
#endif
    }

    // set the player's state to playing
    result = (*m_pPlayerPlay)->SetPlayState(m_pPlayerPlay, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS)
    {
#ifdef SoMessageBoxEnable
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerResume : (*m_pPlayerPlay)->SetPlayState fail");
#endif
    }

    m_eState = AudioPlayerState_Play;
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::SetVolume(float fVolume)
{
    //SLmillibel MinVolume = SL_MILLIBEL_MIN;
    //SLmillibel MaxVolume = SL_MILLIBEL_MIN;
    //(*m_pPlayerVolume)->GetMaxVolumeLevel(m_pPlayerVolume, &MaxVolume);

    //fVolume的值不能是0，否则执行log2操作会得到无效值
    if (fVolume < 0.001f)
    {
        fVolume = 0.001f;
    }

    const double dfT = 3.3219280948873622; //log2(10.0);
    double dBVolume = 20.0 * log2(fVolume) / dfT;
    SLmillibel volume = (SLmillibel)(dBVolume * 100.0); //1dB = 100mB
    (*m_pPlayerVolume)->SetVolumeLevel(m_pPlayerVolume, volume);

    m_fVolume = fVolume;
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::SetLoop(bool bLoop)
{
    m_bLoop = bLoop;

    //SLboolean _Loop = bLoop ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE;
    //(*m_pPlayerSeek)->SetLoop(m_pPlayerSeek, _Loop, 0, SL_TIME_UNKNOWN);
}
//--------------------------------------------------------------------------------------------------
