//------------------------------------------------------------
#ifndef _SoImagePNG_h_
#define _SoImagePNG_h_
//------------------------------------------------------------
struct SoImageFileInfo;
//------------------------------------------------------------
class SoImagePNG
{
public:
	static bool LoadFromFile(const char* pszFileName, SoImageFileInfo* pImageInfo);
	static bool LoadFromFileData(const unsigned char* pFileData, const int nFileSize, SoImageFileInfo* pImageInfo);
};
//------------------------------------------------------------
#endif //_SoImagePNG_h_
//------------------------------------------------------------
