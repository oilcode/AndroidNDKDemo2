//-----------------------------------------------------------------------
#include "AnFileInternal.h"
//-----------------------------------------------------------------------
std::string AnFileInternal::ms_strInternalPath;
//-----------------------------------------------------------------------
void AnFileInternal::SetInternalPath(const char* szPath)
{
    if (szPath != 0 && szPath[0] != 0)
    {
        ms_strInternalPath = szPath;
    }
}
//-----------------------------------------------------------------------
AnFileInternal::AnFileInternal()
{

}
//-----------------------------------------------------------------------
AnFileInternal::~AnFileInternal()
{

}
//-----------------------------------------------------------------------
bool AnFileInternal::InitFile(const char* szFileName, const char* szOpMode)
{
    std::string strFullName(ms_strInternalPath);
    strFullName += szFileName;
    m_pFile = fopen(strFullName.c_str(), szOpMode);
    return (m_pFile != 0);
}
//-----------------------------------------------------------------------
