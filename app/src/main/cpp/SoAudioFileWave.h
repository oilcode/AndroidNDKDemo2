//----------------------------------------------------------------
#ifndef _SoAudioFileWave_h_
#define _SoAudioFileWave_h_
//----------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//----------------------------------------------------------------
class SoFile;
//----------------------------------------------------------------
class SoAudioFileWave
{
public:
	SoAudioFileWave();
	~SoAudioFileWave();

	bool OpenFileWave(const char* szFile);
	void CloseFileWave();

    unsigned char* GetAudioData() const;
	unsigned int GetAudioDataSize() const;
	unsigned int GetFrequency() const;
	unsigned int GetChannelCount() const;
	unsigned int GetChannelMask() const;
	unsigned int GetBitsPerSample() const;
	bool IsFormatPCM() const;
	bool IsFormatExtensible() const;

public:
	struct stFileHeader
	{
		//这四个字符的值必须是'R''I''F''F'。
		char RIFF[4];
		//这个值加上8就等于文件的size。
		unsigned int uiFileLength;
		//这四个字符的值必须是'W''A''V''E'。
		char WAVE[4];
	};
	//一个Wave文件由一个stFileHeader和若干个Chunk组成。
	//每个Chunk由一个stChunkHeader和一个stChunkData组成。
	struct stChunkHeader
	{
		char Flag[4];
		unsigned int uiChunkSize;
	};
	struct stChunkData_FormatPCM
	{
		//值为SoAudioFileWave_Format_PCM，表示PCM格式，这是未压缩的格式。
		//值为SoAudioFileWave_Format_Extensible，表示扩展格式，这是未压缩的格式。
		//其他值，表示某种压缩格式。不支持其他值。
		unsigned short wFormatTag;
		//有几个声道。
		unsigned short wChannelCount;
		//频率。
		unsigned int uiSampleRate;
		//该值等于(uiSampleRate * wChannelCount * wBitsPerSample / 8)。
		unsigned int uiBytePerSecond;
		//该值等于(wChannelCount * wBitsPerSample / 8)。
		unsigned short wBlockAlign;
		//位深，一般值为8，16，32。
		unsigned short wBitsPerSample;
	};
	struct stChunkData_FormatExtensible
	{
		stChunkData_FormatPCM kFormatPCM;
		unsigned short wSize;
		unsigned short wReserved;
		unsigned int uiChannelMask;
		unsigned int GUID_Data1;
		unsigned short GUID_Data2;
		unsigned short GUID_Data3;
		unsigned char GUID_Data4[8];
	};
	struct stChunkData_AudioData
	{
		unsigned char* pData;
		unsigned int uiSize;
	};
	
private:
	bool ReadHeader();
	bool ReadChunk(const char* szFile);

private:
    SoFile* m_pFile;
	stChunkData_FormatExtensible m_stChunkDataFormat;
	stChunkData_AudioData m_stChunkDataAudioData;
};
//----------------------------------------------------------------
#endif //_SoAudioFileWave_h_
//----------------------------------------------------------------
