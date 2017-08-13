//--------------------------------------------------------------------------------------------------
#include "SoAudioOpenslPlayer.h"
#include "SoAudioOpenslManager.h"
#include "SoAudioResource.h"
#include "SoMessageBox.h"
//--------------------------------------------------------------------------------------------------
SoAudioOpenslPlayer::SoAudioOpenslPlayer()
:m_pPlayerObject(NULL)
,m_pPlayerPlay(NULL)
,m_pPlayerBufferQueue(NULL)
,m_pPlayerEffectSend(NULL)
,m_pPlayerVolume(NULL)
,m_pResource(NULL)
,m_nAudioId(-1)
,m_eState(AudioPlayerState_Stop)
{

}
//--------------------------------------------------------------------------------------------------
SoAudioOpenslPlayer::~SoAudioOpenslPlayer()
{
    ReleaseOpenslObject();
}
//--------------------------------------------------------------------------------------------------
bool SoAudioOpenslPlayer::CreateOpenslObject()
{
    SLEngineItf pSLEngine = SoAudioOpenslManager::Get()->GetSLEngine();
    SLObjectItf pSLOutputMix = SoAudioOpenslManager::Get()->GetSLOutputMix();

    SLresult result = SL_RESULT_SUCCESS;
    do
    {
        const SLuint32 BackBufferCount = 3;
        const SLuint32 ChannelCount = 1;
        const SLuint32 Frequency = SL_SAMPLINGRATE_44_1;
        const SLuint32 BitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
        const SLuint32 ContainerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
        const SLuint32 ChannelMask = (ChannelCount == 1) ? SL_SPEAKER_FRONT_CENTER : (SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT);

        SLDataLocator_AndroidSimpleBufferQueue loc_bufq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, BackBufferCount };
        SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, ChannelCount, Frequency, BitsPerSample, ContainerSize, ChannelMask, SL_BYTEORDER_LITTLEENDIAN };
        SLDataSource audioSrc = { &loc_bufq, &format_pcm };
        SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, pSLOutputMix };
        SLDataSink audioSnk = { &loc_outmix, NULL };

        const SLuint32 InterfaceCount = 3;
        const SLInterfaceID ids[3] = { SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME };
        const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
        result = (*pSLEngine)->CreateAudioPlayer(pSLEngine, &m_pPlayerObject, &audioSrc, &audioSnk, InterfaceCount, ids, req);
        if (result != SL_RESULT_SUCCESS)
        {
            SoMessageBox("", "SoAudioOpenslManager : CreateAudioPlayer fail");
            break;
        }

        result = (*m_pPlayerObject)->Realize(m_pPlayerObject, SL_BOOLEAN_FALSE);
        if (result != SL_RESULT_SUCCESS)
        {
            SoMessageBox("", "SoAudioOpenslManager : (*m_pPlayerObject)->Realize fail");
            break;
        }

        result = (*m_pPlayerObject)->GetInterface(m_pPlayerObject, SL_IID_PLAY, &m_pPlayerPlay);
        if (result != SL_RESULT_SUCCESS)
        {
            SoMessageBox("", "SoAudioOpenslManager : get m_pPlayerPlay fail");
            break;
        }

        // get the buffer queue interface
        result = (*m_pPlayerObject)->GetInterface(m_pPlayerObject, SL_IID_BUFFERQUEUE, &m_pPlayerBufferQueue);
        if (result != SL_RESULT_SUCCESS)
        {
            SoMessageBox("", "SoAudioOpenslManager : get m_pPlayerBufferQueue fail");
            break;
        }

        // get the effect send interface
        result = (*m_pPlayerObject)->GetInterface(m_pPlayerObject, SL_IID_EFFECTSEND, &m_pPlayerEffectSend);
        if (result != SL_RESULT_SUCCESS)
        {
            SoMessageBox("", "SoAudioOpenslManager : get m_pPlayerEffectSend fail");
            break;
        }

        // get the volume interface
        result = (*m_pPlayerObject)->GetInterface(m_pPlayerObject, SL_IID_VOLUME, &m_pPlayerVolume);
        if (result != SL_RESULT_SUCCESS)
        {
            SoMessageBox("", "SoAudioOpenslManager : get m_pPlayerVolume fail");
            break;
        }

        // register callback on the buffer queue
        result = (*m_pPlayerBufferQueue)->RegisterCallback(m_pPlayerBufferQueue, SoAudioOpenslPlayer::CallBack_FillBuffer, this);
        if (result != SL_RESULT_SUCCESS)
        {
            SoMessageBox("", "SoAudioOpenslManager : RegisterCallback fail");
            break;
        }

    } while (0);

    if (result != SL_RESULT_SUCCESS)
    {
        ReleaseOpenslObject();
        return false;
    }
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
        m_pPlayerEffectSend = NULL;
        m_pPlayerVolume = NULL;
    }
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslPlayer::CallBack_FillBuffer(SLAndroidSimpleBufferQueueItf bq, void* context)
{
    SoAudioOpenslPlayer* pPlayer = (SoAudioOpenslPlayer*)context;
    SoAudioResource* pResource = pPlayer->m_pResource;
    if (pResource)
    {
        SLresult result = (*bq)->Enqueue(bq, pResource->GetAudioData(), pResource->GetAudioDataSize());
        if (result == SL_RESULT_BUFFER_INSUFFICIENT)
        {
            //buff不足
        }
    }
}
//--------------------------------------------------------------------------------------------------
bool SoAudioOpenslPlayer::AudioPlayerPlay(SoAudioResource *pResource)
{
    if (pResource == NULL)
    {
        return false;
    }
    const SLuint32 Frequency = pResource->GetAudioFrequency() * 1000;
    if (Frequency != SL_SAMPLINGRATE_44_1)
    {
        SoMessageBox("Error", "SoAudioOpenslPlayer::AudioPlayerPlay : Frequency != SL_SAMPLINGRATE_44_1");
        return false;
    }
    const SLuint32 BitsPerSample = pResource->GetAudioBitsPerSample();
    if (BitsPerSample != SL_PCMSAMPLEFORMAT_FIXED_16)
    {
        SoMessageBox("Error", "SoAudioOpenslPlayer::AudioPlayerPlay : BitsPerSample != SL_PCMSAMPLEFORMAT_FIXED_16");
        return false;
    }
    const SLuint32 ChannelCount = pResource->GetAudioChannelCount();
    if (ChannelCount != 1 && ChannelCount != 2)
    {
        SoMessageBox("Error", "SoAudioOpenslPlayer::AudioPlayerPlay : ChannelCount != 1 && ChannelCount != 2");
        return false;
    }

    SLresult result = (*m_pPlayerBufferQueue)->Enqueue(m_pPlayerBufferQueue, pResource->GetAudioData(), pResource->GetAudioDataSize());
    if (result != SL_RESULT_SUCCESS)
    {
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerPlay : m_pPlayerBufferQueue->Enqueue fail");
        return false;
    }

    // set the player's state to playing
    result = (*m_pPlayerPlay)->SetPlayState(m_pPlayerPlay, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS)
    {
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerPlay : (*m_pPlayerPlay)->SetPlayState fail");
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

    if (m_pResource)
    {
        m_pResource->AudioRemoveRef();
        m_pResource = NULL;
    }

    m_eState = AudioPlayerState_Stop;
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
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerPlay : m_pPlayerBufferQueue->Enqueue fail");
    }

    // set the player's state to playing
    result = (*m_pPlayerPlay)->SetPlayState(m_pPlayerPlay, SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS)
    {
        SoMessageBox("", "SoAudioOpenslPlayer::AudioPlayerPlay : (*m_pPlayerPlay)->SetPlayState fail");
    }

    m_eState = AudioPlayerState_Play;
}
//--------------------------------------------------------------------------------------------------
