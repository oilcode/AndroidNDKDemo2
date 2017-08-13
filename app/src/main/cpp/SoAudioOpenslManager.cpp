//--------------------------------------------------------------------------------------------------
#include "SoAudioOpenslManager.h"
#include "SoAudioResourceMgr.h"
#include "SoMessageBox.h"
//--------------------------------------------------------------------------------------------------
SoAudioOpenslManager* SoAudioOpenslManager::ms_pInstance = NULL;
//--------------------------------------------------------------------------------------------------
bool SoAudioOpenslManager::CreateAudioOpenslManager()
{
	bool br = true;
	if (ms_pInstance == NULL)
	{
		ms_pInstance = SoNew SoAudioOpenslManager;
		if (ms_pInstance && ms_pInstance->InitAudioOpenslManager())
		{
			br = true;
		}
		else
		{
			ReleaseAudioOpenslManager();
			br = false;
		}
	}
	return br;
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslManager::ReleaseAudioOpenslManager()
{
	if (ms_pInstance)
	{
		ms_pInstance->ClearAudioOpenslManager();
		SoDelete ms_pInstance;
		ms_pInstance = NULL;
	}
}
//--------------------------------------------------------------------------------------------------
SoAudioOpenslManager::SoAudioOpenslManager()
:m_pSLObject(NULL)
,m_pSLEngine(NULL)
,m_pOutputMixObject(NULL)
{

}
//--------------------------------------------------------------------------------------------------
SoAudioOpenslManager::~SoAudioOpenslManager()
{

}
//--------------------------------------------------------------------------------------------------
bool SoAudioOpenslManager::InitAudioOpenslManager()
{
	SLresult result = SL_RESULT_SUCCESS;
	do
	{
		result = slCreateEngine(&m_pSLObject, 0, NULL, 0, NULL, NULL);
		if (result != SL_RESULT_SUCCESS)
		{
			SoMessageBox("", "SoAudioOpenslManager : slCreateEngine fail");
			break;
		}

		result = (*m_pSLObject)->Realize(m_pSLObject, SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS)
		{
			SoMessageBox("", "SoAudioOpenslManager : (*m_pSLObject)->Realize fail");
			break;
		}

		result = (*m_pSLObject)->GetInterface(m_pSLObject, SL_IID_ENGINE, &m_pSLEngine);
		if (result != SL_RESULT_SUCCESS)
		{
			SoMessageBox("", "SoAudioOpenslManager : (*m_pSLObject)->GetInterface fail");
			break;
		}

		const SLInterfaceID ids[1] = { SL_IID_ENVIRONMENTALREVERB };
		const SLboolean req[1] = { SL_BOOLEAN_FALSE };
		result = (*m_pSLEngine)->CreateOutputMix(m_pSLEngine, &m_pOutputMixObject, 1, ids, req);
		if (result != SL_RESULT_SUCCESS)
		{
			SoMessageBox("", "SoAudioOpenslManager : CreateOutputMix fail");
			break;
		}

		result = (*m_pOutputMixObject)->Realize(m_pOutputMixObject, SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS)
		{
			SoMessageBox("", "SoAudioOpenslManager : (*m_pOutputMixObject)->Realize fail");
			break;
		}

	} while (0);

	if (result != SL_RESULT_SUCCESS)
	{
		ClearAudioOpenslManager();
		return false;
	}

    if (PreparePlayerArray() == false)
    {
        ClearAudioOpenslManager();
        return false;
    }

	return true;
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslManager::ClearAudioOpenslManager()
{
	if (m_pOutputMixObject)
	{
		(*m_pOutputMixObject)->Destroy(m_pOutputMixObject);
		m_pOutputMixObject = NULL;
	}
	if (m_pSLObject)
	{
		(*m_pSLObject)->Destroy(m_pSLObject);
		m_pSLObject = NULL;
		m_pSLEngine = NULL;
	}
}
//--------------------------------------------------------------------------------------------------
bool SoAudioOpenslManager::PreparePlayerArray()
{
    if (m_kPlayerArray.InitArray(sizeof(SoAudioOpenslPlayer*), 32, 10) == false)
    {
        return false;
    }

    SoAudioOpenslPlayer* pPlayer = NULL;
    const int nCount = 6;
    for (int i = 0; i < nCount; ++i)
    {
        pPlayer = SoNew SoAudioOpenslPlayer;
        if (pPlayer == NULL)
        {
            continue;
        }

        if (pPlayer->CreateOpenslObject() == false)
        {
            SoDelete pPlayer;
            pPlayer = NULL;
            continue;
        }

        const int nAudioId = m_kPlayerArray.FillAt(-1, &pPlayer);
        pPlayer->SetAudioID(nAudioId);
    }

    return true;
}
//--------------------------------------------------------------------------------------------------
SoAudioOpenslPlayer* SoAudioOpenslManager::FindEmptyPlayer()
{
    const int nCount = m_kPlayerArray.GetCapacity();
    SoAudioOpenslPlayer* pPlayer = NULL;
    for (int i = 0; i < nCount; ++i)
    {
        pPlayer = GetAudioPlayer(i);
        if (pPlayer && pPlayer->IsUnused())
        {
            return pPlayer;
        }
    }
    return NULL;
}
//--------------------------------------------------------------------------------------------------
SoAudioOpenslPlayer* SoAudioOpenslManager::GetAudioPlayer(int nAudioId)
{
    void* pElement = m_kPlayerArray.GetAt(nAudioId);
    if (pElement)
    {
        return (*((SoAudioOpenslPlayer**)pElement));
    }
    else
    {
        return NULL;
    }
}
//--------------------------------------------------------------------------------------------------
int SoAudioOpenslManager::AudioPlay(const char* szResourceName, bool bLoop, bool bEndEvent)
{
    SoAudioResource* pResource = SoAudioResourceMgr::Get()->CreateAudioResource(SoTinyString(szResourceName));
    if (pResource == NULL)
    {
        return -1;
    }

    SoAudioOpenslPlayer* pPlayer = FindEmptyPlayer();
    if (pPlayer == NULL)
    {
        return -1;
    }

    if (pPlayer->AudioPlayerPlay(pResource) == false)
    {
        return -1;
    }

    return pPlayer->GetAudioID();
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslManager::AudioStop(int nAudioId)
{
    SoAudioOpenslPlayer* pPlayer = GetAudioPlayer(nAudioId);
    if (pPlayer == NULL)
    {
        return;
    }

    pPlayer->AudioPlayerStop();
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslManager::AudioPause(int nAudioId)
{
    SoAudioOpenslPlayer* pPlayer = GetAudioPlayer(nAudioId);
    if (pPlayer == NULL)
    {
        return;
    }

    pPlayer->AudioPlayerPause();
}
//--------------------------------------------------------------------------------------------------
void SoAudioOpenslManager::AudioResume(int nAudioId)
{
    SoAudioOpenslPlayer* pPlayer = GetAudioPlayer(nAudioId);
    if (pPlayer == NULL)
    {
        return;
    }

    pPlayer->AudioPlayerResume();
}
//--------------------------------------------------------------------------------------------------
