//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionAudio_h_
#define _GGUIActionAudio_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionAudio : public GGUIActionBase
{
	friend class GGUIActionFactory;

public:
    void InitActionAudio(const char* szAudioName, float fAudioVolume, float fTime);
	virtual void UpdateAction(float fDeltaTime);

protected:
	GGUIActionAudio();
    virtual ~GGUIActionAudio();
    virtual void ClearAction();

protected:
	SoTinyString m_kAudioName;
	float m_fAudioVolume;
	float m_fRemainTime;
	bool m_bAlreadyPlaying;
};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionAudio_h_
//--------------------------------------------------------------------------------------------------
