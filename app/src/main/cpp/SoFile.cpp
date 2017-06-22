//-----------------------------------------------------------------------
#include "SoFile.h"
#include <stdlib.h>
//-----------------------------------------------------------------------
SoFile::SoFile()
:m_pFile(0)
,m_pFileData(0)
,m_nFileSize(0)
{

}
//-----------------------------------------------------------------------
SoFile::~SoFile()
{

}
//-----------------------------------------------------------------------
bool SoFile::InitFile(const char* szFileName, const char* szOpMode)
{
    m_pFile = fopen(szFileName, szOpMode);
    return (m_pFile != 0);
}
//-----------------------------------------------------------------------
void SoFile::ClearFile()
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = 0;
	}
	if (m_pFileData)
    {
        free(m_pFileData);
        m_pFileData = 0;
    }
}
//-----------------------------------------------------------------------
int SoFile::Read(void* buff, int elementSize, int count)
{
	if (m_pFile == 0)
	{
		return 0;
	}

	return (int)fread(buff, elementSize, count, m_pFile);
}
//-----------------------------------------------------------------------
int SoFile::Write(const void* buff, int elementSize, int count)
{
	if (m_pFile == 0)
	{
		return 0;
	}

	return (int)fwrite(buff, elementSize, count, m_pFile);
}
//-----------------------------------------------------------------------
bool SoFile::Seek(int offset, int origin)
{
	if (m_pFile == 0)
	{
		return false;
	}

	return (fseek(m_pFile, offset, origin) == 0);
}
//-----------------------------------------------------------------------
int SoFile::Tell()
{
	if (m_pFile == 0)
	{
		return 0;
	}

	return ftell(m_pFile);
}
//-----------------------------------------------------------------------
void SoFile::Flush()
{
	if (m_pFile)
	{
		fflush(m_pFile);
	}
}
//-----------------------------------------------------------------------
bool SoFile::IsValid()
{
    return (m_pFile != 0);
}
//-----------------------------------------------------------------------
int SoFile::GetFileSize()
{
	if (m_pFile == 0)
	{
		return 0;
	}

	if (m_nFileSize == 0)
	{
		int oldPointer = ftell(m_pFile);
		fseek(m_pFile, 0, SEEK_END);
		m_nFileSize = ftell(m_pFile);
		fseek(m_pFile, oldPointer, SEEK_SET);
	}

	return m_nFileSize;
}
//-----------------------------------------------------------------------
unsigned char* SoFile::GetFileData()
{
	if (m_pFile == 0)
	{
		return 0;
	}

	if (m_pFileData == 0)
	{
        const int nFileSize = GetFileSize();
        m_pFileData = (unsigned char*)malloc(nFileSize+1);
        m_pFileData[nFileSize] = 0;
        fseek(m_pFile, 0, SEEK_SET);
        fread(m_pFileData, 1, nFileSize, m_pFile);
	}

    return m_pFileData;
}
//-----------------------------------------------------------------------
