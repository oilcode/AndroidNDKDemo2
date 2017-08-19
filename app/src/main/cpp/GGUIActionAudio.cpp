//--------------------------------------------------------------------------------------------------
#include "GGUIActionAudio.h"
#include "SoAudio.h"
//--------------------------------------------------------------------------------------------------
GGUIActionAudio::GGUIActionAudio()
:m_fAudioVolume(1.0f)
,m_fRemainTime(-1.0f)
,m_bAlreadyPlaying(false)
{
	m_eActionType = GGUIAction_Audio;
}
//--------------------------------------------------------------------------------------------------
GGUIActionAudio::~GGUIActionAudio()
{

}
//--------------------------------------------------------------------------------------------------
void GGUIActionAudio::InitActionAudio(const char* szAudioName, float fAudioVolume, float fTime)
{
	if (szAudioName == NULL || szAudioName[0] == 0)
	{
#ifdef SoMessageBoxEnable
		SoMessageBox("Error", "GGUIActionAudio::InitActionAudio : szAudioName == NULL || szAudioName[0] == 0");
#endif
		return;
	}

	// fTime must not be zero
	if (-0.01f < fTime && fTime < 0.01f )
	{
		fTime = 0.01f;
	}

	m_kAudioName = szAudioName;
	m_fAudioVolume = fAudioVolume;
	m_fRemainTime = fTime;
    m_eLifeStep = ActionLife_Running;
	m_bAlreadyPlaying = false;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionAudio::UpdateAction(float fDeltaTime)
{
	if (m_fRemainTime < 0.0f)
	{
		//already finished
		return;
	}

	if (! m_bAlreadyPlaying)
	{
		m_bAlreadyPlaying = true;
		SoAudioPlay(m_kAudioName.GetValue(), m_fAudioVolume, false, false);
	}

	if (m_fRemainTime > fDeltaTime)
	{
        m_fRemainTime -= fDeltaTime;
	}
	else
	{
		m_fRemainTime = -1.0f;
        m_eLifeStep = ActionLife_Finished;
	}
}
//--------------------------------------------------------------------------------------------------
void GGUIActionAudio::ClearAction()
{
    GGUIActionBase::ClearAction();
	m_kAudioName.Clear();
	m_fAudioVolume = 1.0f;
    m_fRemainTime = -1.0f;
	m_bAlreadyPlaying = false;
}
//--------------------------------------------------------------------------------------------------
