//-----------------------------------------------------------------------
#include "AnFileAsset.h"
#include <stdlib.h> //for malloc free
//-----------------------------------------------------------------------
AAssetManager* AnFileAsset::ms_pAssetMgr = 0;
//-----------------------------------------------------------------------
void AnFileAsset::SetAssetMgr(AAssetManager* pAssetMgr)
{
    ms_pAssetMgr = pAssetMgr;
}
//-----------------------------------------------------------------------
AnFileAsset::AnFileAsset()
:m_pAssetFile(0)
{

}
//-----------------------------------------------------------------------
AnFileAsset::~AnFileAsset()
{

}
//-----------------------------------------------------------------------
bool AnFileAsset::InitFile(const char* szFileName, const char* szOpMode)
{
    if (ms_pAssetMgr == 0)
    {
        return false;
    }

    m_pAssetFile = AAssetManager_open(ms_pAssetMgr, szFileName, AASSET_MODE_UNKNOWN);
    return (m_pAssetFile != 0);
}
//-----------------------------------------------------------------------
void AnFileAsset::ClearFile()
{
    if (m_pAssetFile)
    {
        AAsset_close(m_pAssetFile);
        m_pAssetFile = 0;
    }
    if (m_pFileData)
    {
        free(m_pFileData);
        m_pFileData = 0;
    }
}
//-----------------------------------------------------------------------
int AnFileAsset::Read(void* buff, int elementSize, int count)
{
    if (m_pAssetFile == 0)
    {
        return 0;
    }

    return (int)AAsset_read(m_pAssetFile, buff, elementSize * count);
}
//-----------------------------------------------------------------------
int AnFileAsset::Write(const void* buff, int elementSize, int count)
{
    // can not write
    return 0;
}
//-----------------------------------------------------------------------
bool AnFileAsset::Seek(int offset, int origin)
{
    if (m_pAssetFile == 0)
    {
        return false;
    }

    return (AAsset_seek(m_pAssetFile, offset, origin) != -1);
}
//-----------------------------------------------------------------------
int AnFileAsset::Tell()
{
    // can not tell
    return 0;
}
//-----------------------------------------------------------------------
void AnFileAsset::Flush()
{
    // can not flush
}
//-----------------------------------------------------------------------
bool AnFileAsset::IsValid()
{
    return (m_pAssetFile != 0);
}
//-----------------------------------------------------------------------
int AnFileAsset::GetFileSize()
{
    if (m_pAssetFile == 0)
    {
        return 0;
    }

    if (m_nFileSize == 0)
    {
        m_nFileSize = (int)AAsset_getLength(m_pAssetFile);
    }

    return m_nFileSize;
}
//-----------------------------------------------------------------------
unsigned char* AnFileAsset::GetFileData()
{
    if (m_pAssetFile == 0)
    {
        return 0;
    }

    if (m_pFileData == 0)
    {
        const int nFileSize = GetFileSize();
        m_pFileData = (unsigned char*)malloc(nFileSize+1);
        m_pFileData[nFileSize] = 0;
        AAsset_seek(m_pAssetFile, 0, SEEK_SET);
        AAsset_read(m_pAssetFile, m_pFileData, nFileSize);
    }

    return m_pFileData;
}
//-----------------------------------------------------------------------
