//----------------------------------------------------------------
#include "SoAudioResource.h"
#include "SoAudioFileWave.h"
//----------------------------------------------------------------
SoAudioResource::SoAudioResource()
:m_szResourceName("")
,m_pAudioData(NULL)
,m_nResourceId(-1)
,m_eFileType(SoAudioFileType_Invalid)
,m_uiAudioDataSize(0)
,m_uiAudioFrequency(0)
,m_uiAudioChannelCount(0)
,m_uiAudioBitsPerSample(0)
,m_fAudioTimeLength(0.0f)
,m_nRefCount(0)
{

}
//----------------------------------------------------------------
SoAudioResource::~SoAudioResource()
{
    ClearAudioResource();
}
//----------------------------------------------------------------
bool SoAudioResource::InitAudioResource()
{
	if (m_szResourceName == 0 || m_szResourceName[0] == 0)
	{
		return false;
	}

	m_eFileType = SoAudioFileType_Wave;
	//
	bool bLoadSuccess = false;
	if (m_eFileType == SoAudioFileType_Wave)
	{
		bLoadSuccess = LoadFileWave();
	}
	//
	if (bLoadSuccess == false)
	{
        ClearAudioResource();
	}
	return bLoadSuccess;
}
//----------------------------------------------------------------
void SoAudioResource::ClearAudioResource()
{
    if (m_pAudioData)
    {
        free(m_pAudioData);
        m_pAudioData = NULL;
    }
    m_szResourceName = "";
    m_nResourceId = -1;
	m_eFileType = SoAudioFileType_Invalid;
    m_uiAudioDataSize = 0;
	m_uiAudioFrequency = 0;
	m_uiAudioChannelCount = 0;
	m_uiAudioBitsPerSample = 0;
	m_fAudioTimeLength = 0.0f;
	m_nRefCount = 0;
}
//----------------------------------------------------------------
bool SoAudioResource::LoadFileWave()
{
	SoAudioFileWave kFileWave;
	if (kFileWave.OpenFileWave(m_szResourceName) == false)
	{
		return false;
	}
    //
    const unsigned int dataSize = kFileWave.GetAudioDataSize();
    if (dataSize == 0)
    {
        return false;
    }
    //
    m_pAudioData = (unsigned char*)malloc(dataSize);
    if (m_pAudioData == NULL)
    {
        return false;
    }
    memcpy(m_pAudioData, kFileWave.GetAudioData(), dataSize);
    m_uiAudioDataSize = dataSize;
	//
	m_uiAudioFrequency = kFileWave.GetFrequency();
	m_uiAudioChannelCount = kFileWave.GetChannelCount();
	m_uiAudioBitsPerSample = kFileWave.GetBitsPerSample();
	m_fAudioTimeLength = ((float)m_uiAudioDataSize) / ((float)(m_uiAudioFrequency * m_uiAudioChannelCount * m_uiAudioBitsPerSample / 8));
	return true;
}
//----------------------------------------------------------------
