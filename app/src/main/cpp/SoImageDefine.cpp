//------------------------------------------------------------
#include "SoImageDefine.h"
#include "SoCodeBaseInclude.h"
//------------------------------------------------------------
SoImageFileInfo::SoImageFileInfo()
:pData(0)
,nDataSize(0)
,nWidth(0)
,nHeight(0)
,theFileType(SoImageFile_Invalid)
,theBitDepth(SoImageBitDepth_Invalid)
,theColorType(SoImageColor_Invalid)
{

}
//------------------------------------------------------------
SoImageFileInfo::~SoImageFileInfo()
{
    if (pData)
    {
        SoFree(pData);
        pData = NULL;
    }
}
//------------------------------------------------------------
