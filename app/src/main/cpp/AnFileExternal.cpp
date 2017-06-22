//-----------------------------------------------------------------------
#include "AnFileExternal.h"
//-----------------------------------------------------------------------
std::string AnFileExternal::ms_strExternalPath;
//-----------------------------------------------------------------------
void AnFileExternal::SetExternalPath(const char* szPath)
{
    if (szPath != 0 && szPath[0] != 0)
    {
        ms_strExternalPath = szPath;
    }
}
//-----------------------------------------------------------------------
AnFileExternal::AnFileExternal()
{

}
//-----------------------------------------------------------------------
AnFileExternal::~AnFileExternal()
{

}
//-----------------------------------------------------------------------
bool AnFileExternal::InitFile(const char* szFileName, const char* szOpMode)
{
    std::string strFullName(ms_strExternalPath);
    strFullName += szFileName;
    m_pFile = fopen(strFullName.c_str(), szOpMode);
    return (m_pFile != 0);
}
//-----------------------------------------------------------------------
