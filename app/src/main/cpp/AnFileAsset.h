//-----------------------------------------------------------------------
#ifndef _AnFileAsset_h_
#define _AnFileAsset_h_
//-----------------------------------------------------------------------
#include <android/asset_manager.h>
#include "SoFile.h"
//-----------------------------------------------------------------------
class AnFileAsset : public SoFile
{
public:
    static void SetAssetMgr(AAssetManager* pAssetMgr);

public:
    AnFileAsset();
    ~AnFileAsset();

    int Read(void* buff, int elementSize, int count);
    int Write(const void* buff, int elementSize, int count);
    bool Seek(int offset, int origin);
    int Tell();
    void Flush();

    bool IsValid();
    int GetFileSize();
    unsigned char* GetFileData();

protected:
    bool InitFile(const char* szFileName, const char* szOpMode);
    void ClearFile();

private:
    static AAssetManager* ms_pAssetMgr;
    AAsset* m_pAssetFile;
};
//-----------------------------------------------------------------------
#endif //_AnFileAsset_h_
//-----------------------------------------------------------------------
