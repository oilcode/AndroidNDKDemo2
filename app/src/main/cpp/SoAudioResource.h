//----------------------------------------------------------------
#ifndef _SoAudioResource_h_
#define _SoAudioResource_h_
//----------------------------------------------------------------
enum SoAudioFileType
{
	SoAudioFileType_Invalid = -1,
	SoAudioFileType_Wave,
};
//----------------------------------------------------------------
class SoAudioResource
{
public:
	int GetResourceID() const;
	SoAudioFileType GetFileType() const;
	const char* GetResourceName() const;
	const unsigned char* GetAudioData() const;
	unsigned int GetAudioDataSize() const;
	unsigned int GetAudioFrequency() const;
	unsigned int GetAudioChannelCount() const;
	unsigned int GetAudioBitsPerSample() const;
	float GetAudioTimeLength() const;

    void AudioAddRef();
    void AudioRemoveRef();
    int AudioGetRef() const;

protected:
	friend class SoAudioResourceMgr;
	SoAudioResource();
	~SoAudioResource();
	bool InitAudioResource();
    void SetResourceID(int nId);
    void SetResourceName(const char* szResourceName);
	void ClearAudioResource();
	bool LoadFileWave();

private:
	const char* m_szResourceName;
    unsigned char* m_pAudioData;
	int m_nResourceId;
	SoAudioFileType m_eFileType;
	//音频数据大小。
	unsigned int m_uiAudioDataSize;
	//频率。
	unsigned int m_uiAudioFrequency;
	//声道个数。
	unsigned int m_uiAudioChannelCount;
	//位深，一般值为8，16，32。
	unsigned int m_uiAudioBitsPerSample;
	//音频数据播放多少秒钟。
	float m_fAudioTimeLength;
	//引用计数。
	int m_nRefCount;
};
//----------------------------------------------------------------
inline void SoAudioResource::AudioAddRef()
{
	++m_nRefCount;
}
//----------------------------------------------------------------
inline void SoAudioResource::AudioRemoveRef()
{
	--m_nRefCount;
}
//----------------------------------------------------------------
inline int SoAudioResource::AudioGetRef() const
{
	return m_nRefCount;
}
//----------------------------------------------------------------
inline void SoAudioResource::SetResourceID(int nId)
{
    m_nResourceId = nId;
}
//----------------------------------------------------------------
inline int SoAudioResource::GetResourceID() const
{
	return m_nResourceId;
}
//----------------------------------------------------------------
inline SoAudioFileType SoAudioResource::GetFileType() const
{
	return m_eFileType;
}
//----------------------------------------------------------------
inline void SoAudioResource::SetResourceName(const char* szResourceName)
{
    m_szResourceName = szResourceName;
}
//----------------------------------------------------------------
inline const char* SoAudioResource::GetResourceName() const
{
	return m_szResourceName;
}
//----------------------------------------------------------------
inline const unsigned char* SoAudioResource::GetAudioData() const
{
	return m_pAudioData;
}
//----------------------------------------------------------------
inline unsigned int SoAudioResource::GetAudioDataSize() const
{
	return m_uiAudioDataSize;
}
//----------------------------------------------------------------
inline unsigned int SoAudioResource::GetAudioFrequency() const
{
	return m_uiAudioFrequency;
}
//----------------------------------------------------------------
inline unsigned int SoAudioResource::GetAudioChannelCount() const
{
	return m_uiAudioChannelCount;
}
//----------------------------------------------------------------
inline unsigned int SoAudioResource::GetAudioBitsPerSample() const
{
	return m_uiAudioBitsPerSample;
}
//----------------------------------------------------------------
inline float SoAudioResource::GetAudioTimeLength() const
{
	return m_fAudioTimeLength;
}
//----------------------------------------------------------------
#endif //_SoAudioResource_h_
//----------------------------------------------------------------
