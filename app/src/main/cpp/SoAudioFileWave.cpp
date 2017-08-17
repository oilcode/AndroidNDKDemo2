//----------------------------------------------------------------
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
//----------------------------------------------------------------
#include "SoAudioFileWave.h"
#include "SoFileHelp.h"
#include "SoStringHelp.h"
#include "SoMessageBox.h"
//----------------------------------------------------------------
#define SoAudioFileWave_Format_PCM 1
#define SoAudioFileWave_Format_Extensible 0xFFFE
//----------------------------------------------------------------
SoAudioFileWave::SoAudioFileWave()
:m_pFile(NULL)
{
	memset(&m_stChunkDataFormat, 0, sizeof(stChunkData_FormatExtensible));
	memset(&m_stChunkDataAudioData, 0, sizeof(stChunkData_AudioData));
}
//----------------------------------------------------------------
SoAudioFileWave::~SoAudioFileWave()
{
	CloseFileWave();
}
//----------------------------------------------------------------
bool SoAudioFileWave::OpenFileWave(const char* szFile)
{
	if (szFile == 0 || szFile[0] == 0)
	{
#ifdef SoMessageBoxEnable
		SoMessageBox("Error", "SoAudioFileWave::OpenFileWave : szFile == 0 || szFile[0] == 0");
#endif
		return false;
	}

	m_pFile = SoFileHelp::CreateFile(szFile, "rb");
	if (m_pFile == 0)
	{
#ifdef SoMessageBoxEnable
        const char* strText = SoStrFmt("SoAudioFileWave::OpenFileWave : CreateFile fail [%s]", szFile);
        SoMessageBox("Error", strText);
#endif
		return false;
	}

	if (ReadHeader() == false)
	{
#ifdef SoMessageBoxEnable
        const char* strText = SoStrFmt("SoAudioFileWave::OpenFileWave : ReadHeader() fail [%s]", szFile);
        SoMessageBox("Error", strText);
#endif
		CloseFileWave();
		return false;
	}

	if (ReadChunk(szFile) == false)
	{
		CloseFileWave();
		return false;
	}

	//关闭文件。
    SoFileHelp::DeleteFile(m_pFile);

	if (m_stChunkDataAudioData.uiSize == 0
        || m_stChunkDataFormat.kFormatPCM.uiSampleRate == 0
        || m_stChunkDataFormat.kFormatPCM.wChannelCount == 0
        || m_stChunkDataFormat.kFormatPCM.wBitsPerSample == 0)
    {
#ifdef SoMessageBoxEnable
        const char* strText = SoStrFmt("SoAudioFileWave::OpenFileWave : data format is invalid is ZERO [%s]", szFile);
        SoMessageBox("Error", strText);
#endif
        return false;
    }

	return true;
}
//----------------------------------------------------------------
void SoAudioFileWave::CloseFileWave()
{
	if (m_pFile)
	{
        SoFileHelp::DeleteFile(m_pFile);
	}
	if (m_stChunkDataAudioData.pData)
	{
		delete [] m_stChunkDataAudioData.pData;
		m_stChunkDataAudioData.pData = 0;
	}
	memset(&m_stChunkDataFormat, 0, sizeof(stChunkData_FormatExtensible));
	memset(&m_stChunkDataAudioData, 0, sizeof(stChunkData_AudioData));
}
//----------------------------------------------------------------
unsigned char* SoAudioFileWave::GetAudioData() const
{
	return m_stChunkDataAudioData.pData;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetAudioDataSize() const
{
	return m_stChunkDataAudioData.uiSize;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetFrequency() const
{
	return m_stChunkDataFormat.kFormatPCM.uiSampleRate;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetChannelCount() const
{
	return m_stChunkDataFormat.kFormatPCM.wChannelCount;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetChannelMask() const
{
	return m_stChunkDataFormat.uiChannelMask;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetBitsPerSample() const
{
	return m_stChunkDataFormat.kFormatPCM.wBitsPerSample;
}
//----------------------------------------------------------------
bool SoAudioFileWave::IsFormatPCM() const
{
	return (m_stChunkDataFormat.kFormatPCM.wFormatTag == SoAudioFileWave_Format_PCM);
}
//----------------------------------------------------------------
bool SoAudioFileWave::IsFormatExtensible() const
{
	return (m_stChunkDataFormat.kFormatPCM.wFormatTag == SoAudioFileWave_Format_Extensible);
}
//----------------------------------------------------------------
bool SoAudioFileWave::ReadHeader()
{
	stFileHeader kHeader;
	memset(&kHeader, 0, sizeof(stFileHeader));
    m_pFile->Read(&kHeader, 1, sizeof(stFileHeader));
	if (kHeader.RIFF[0] == 'R'
		&& kHeader.RIFF[1] == 'I' 
		&& kHeader.RIFF[2] == 'F' 
		&& kHeader.RIFF[3] == 'F'
		&& kHeader.WAVE[0] == 'W'
		&& kHeader.WAVE[1] == 'A' 
		&& kHeader.WAVE[2] == 'V'
		&& kHeader.WAVE[3] == 'E')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//----------------------------------------------------------------
bool SoAudioFileWave::ReadChunk(const char* szFile)
{
	bool br = true;
	stChunkHeader kHeader;
	memset(&kHeader, 0, sizeof(stChunkHeader));
	while (m_pFile->Read(&kHeader, 1, sizeof(stChunkHeader)) == sizeof(stChunkHeader))
	{
		if (kHeader.Flag[0] == 'f'
			&& kHeader.Flag[1] == 'm'
			&& kHeader.Flag[2] == 't'
			&& kHeader.Flag[3] == ' ')
		{
			if (kHeader.uiChunkSize <= sizeof(stChunkData_FormatExtensible))
			{
                m_pFile->Read(&m_stChunkDataFormat, 1, kHeader.uiChunkSize);
				if (m_stChunkDataFormat.kFormatPCM.wFormatTag != SoAudioFileWave_Format_PCM
					&& m_stChunkDataFormat.kFormatPCM.wFormatTag != SoAudioFileWave_Format_Extensible)
				{
#ifdef SoMessageBoxEnable
                    const char* strText = SoStrFmt("SoAudioFileWave::ReadChunk : DataFormat is invalid [%s][%d]", szFile, m_stChunkDataFormat.kFormatPCM.wFormatTag);
                    SoMessageBox("Error", strText);
#endif
					br = false;
					break;
				}
			}
			else
			{
				//这里不要结束循环，而是跳过这个Chunk，继续循环。
                m_pFile->Seek(kHeader.uiChunkSize, SEEK_CUR);
			}
		}
		else if (kHeader.Flag[0] == 'd'
			&& kHeader.Flag[1] == 'a'
			&& kHeader.Flag[2] == 't'
			&& kHeader.Flag[3] == 'a')
		{
			m_stChunkDataAudioData.pData = new unsigned char[kHeader.uiChunkSize];
			if (m_stChunkDataAudioData.pData)
			{
                m_pFile->Read(m_stChunkDataAudioData.pData, 1, kHeader.uiChunkSize);
				m_stChunkDataAudioData.uiSize = kHeader.uiChunkSize;
			}
			else
			{
#ifdef SoMessageBoxEnable
                const char* strText = SoStrFmt("SoAudioFileWave::ReadChunk : create data buffer fail [%s][%u]", szFile, kHeader.uiChunkSize);
                SoMessageBox("Error", strText);
#endif
				br = false;
				break;
			}
		}
		else
		{
			//其他Chunk
            m_pFile->Seek(kHeader.uiChunkSize, SEEK_CUR);
		}
		//在文件结构中，每个Chunk的size都是2的整数倍，
		//如果kHeader.uiChunkSize不是2的整数倍，则需要使文件指针后移一个字节。
		if (kHeader.uiChunkSize & 1)
		{
            m_pFile->Seek(1, SEEK_CUR);
		}
	}
	//
	return br;
}
//----------------------------------------------------------------
