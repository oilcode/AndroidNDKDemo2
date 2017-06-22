//-----------------------------------------------------------------------
#ifndef _AnFileExternal_h_
#define _AnFileExternal_h_
//-----------------------------------------------------------------------
#include "SoFile.h"
#include <string>
//-----------------------------------------------------------------------
class AnFileExternal : public SoFile
{
public:
	static void SetExternalPath(const char* szPath);

public:
    AnFileExternal();
    ~AnFileExternal();

protected:
	bool InitFile(const char* szFileName, const char* szOpMode);

private:
    //"/storage/sdcard0/"
	static std::string ms_strExternalPath;
};
//-----------------------------------------------------------------------
#endif //_AnFileExternal_h_
//-----------------------------------------------------------------------
