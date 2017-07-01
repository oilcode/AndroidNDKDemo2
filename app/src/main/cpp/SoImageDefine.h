//------------------------------------------------------------
#ifndef _SoImageDefine_h_
#define _SoImageDefine_h_
//------------------------------------------------------------
//图片文件类型，目前只支持PNG图片
enum SoImageFileType
{
	SoImageFile_Invalid = -1, //无效值
	SoImageFile_PNG, //PNG图片
};
//------------------------------------------------------------
//色彩位深，每个颜色通道占据几个bit。
//目前只支持 RGBA 32位色，每个通道占8位。
enum SoImageBitDepthType
{
	SoImageBitDepth_Invalid = -1, //无效值
	SoImageBitDepth_8,
};
//------------------------------------------------------------
//图片颜色类型
enum SoImageColorType
{
	SoImageColor_Invalid = -1, //无效值
	SoImageColor_RGBA, //RGB颜色，含alpha通道
	SoImageColor_RGB, //RGB颜色
};
//------------------------------------------------------------
//图片信息
struct SoImageFileInfo
{
	unsigned char* pData; //存储图片文件中的图像数据。本内存块由SoImageHelp负责创建，由本结构体负责删除。
    int nDataSize;
	int nWidth; //图片宽度
	int nHeight; //图片高度
	SoImageFileType theFileType;
	SoImageBitDepthType theBitDepth; //色彩位深，目前只支持32位色
	SoImageColorType theColorType; //颜色类型，目前只支持RGBA颜色

	SoImageFileInfo();
	~SoImageFileInfo();
};
//------------------------------------------------------------
#endif //_SoImageDefine_h_
//------------------------------------------------------------
