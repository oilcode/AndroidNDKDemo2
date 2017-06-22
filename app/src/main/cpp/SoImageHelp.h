//------------------------------------------------------------
#ifndef _SoImageHelp_h_
#define _SoImageHelp_h_
//------------------------------------------------------------
#include "SoImageDefine.h"
//------------------------------------------------------------
class SoImageHelp
{
public:
	//从磁盘上加载指定的图片文件。
	//--pszFileName 图片文件名，包含路径。
	//--pImageInfo [out] 获取图片文件的各个数据。
	//加载成功返回true，否则返回false。
	//函数内部会申请内存，用于存储图像数据，但是该内存的释放由外界负责。
	static bool LoadImageFile(const char* pszFileName, SoImageFileInfo* pImageInfo);

	//检测文件的类型。
	static SoImageFileType CheckFileType(const char* pszFileName);

};
//------------------------------------------------------------
#endif //_SoImageHelp_h_
//------------------------------------------------------------
