//-----------------------------------------------------------------------
#ifndef _AnFileInternal_h_
#define _AnFileInternal_h_
//-----------------------------------------------------------------------
#include "SoFile.h"
#include <string>
//-----------------------------------------------------------------------
class AnFileInternal : public SoFile
{
public:
	static void SetInternalPath(const char* szPath);

public:
	AnFileInternal();
	~AnFileInternal();

protected:
	bool InitFile(const char* szFileName, const char* szOpMode);

private:
	//"/data/data/com.ggui.swoosh.fidemo/files/"
	static std::string ms_strInternalPath;
};
//-----------------------------------------------------------------------
#endif //_AnFileInternal_h_
//-----------------------------------------------------------------------
