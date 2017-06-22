//-----------------------------------------------------------------------
#ifndef _SoFile_h_
#define _SoFile_h_
//-----------------------------------------------------------------------
#include <stdio.h>
//-----------------------------------------------------------------------
class SoFile
{
	friend class SoFileHelp;

public:
    SoFile();
	virtual ~SoFile();

	virtual int Read(void* buff, int elementSize, int count);
	virtual int Write(const void* buff, int elementSize, int count);
	virtual bool Seek(int offset, int origin);
	virtual int Tell();
	virtual void Flush();

	virtual bool IsValid();
	virtual int GetFileSize();
	virtual unsigned char* GetFileData();

protected:
	virtual bool InitFile(const char* szFileName, const char* szOpMode);
	virtual void ClearFile();

protected:
	FILE* m_pFile;
    unsigned char* m_pFileData;
    int m_nFileSize;
};
//-----------------------------------------------------------------------
#endif //_SoFile_h_
//-----------------------------------------------------------------------
