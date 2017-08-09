//----------------------------------------------------------------
#include "GGUIFileGGM.h"
//----------------------------------------------------------------
GGUIFileGGM::GGUIFileGGM()
:m_pFile(0)
,m_pFileBuff(0)
,m_nFileSize(0)
,m_nReadPointer(0)
,m_fTexWidth(256.0f)
,m_fTexHeight(256.0f)
,m_fFontSize(24.0f)
,m_fFontHeight(32.0f)
{

}
//----------------------------------------------------------------
GGUIFileGGM::~GGUIFileGGM()
{
	CloseGgmFile();
}
//----------------------------------------------------------------
bool GGUIFileGGM::ReadGgmFile(const char *szFileName)
{
	if (szFileName == 0 || szFileName[0] == 0)
	{
		return false;
	}
	m_pFile = SoFileHelp::CreateFile(szFileName, "rt");
	if (m_pFile == 0)
	{
		return false;
	}
	//
	m_pFileBuff = (char*)m_pFile->GetFileData();
	m_nFileSize = m_pFile->GetFileSize();
	m_nReadPointer = 0;
	return true;
}
//----------------------------------------------------------------
bool GGUIFileGGM::GetTextureName(std::string& strTextureName)
{
	m_nReadPointer = 0;
	const char* szFirstLine = ReadNextFileLine();
	if (szFirstLine)
	{
		strTextureName = SoCmdLineHelp::GetValueByKey(szFirstLine, -1, "Texture");
        m_fTexWidth = (float)SoCmdLineHelp::GetIntByKey(szFirstLine, -1, "TexWidth", 256);
        m_fTexHeight = (float)SoCmdLineHelp::GetIntByKey(szFirstLine, -1, "TexHeight", 256);
        m_fFontSize = (float)SoCmdLineHelp::GetIntByKey(szFirstLine, -1, "FontSize", 24);
        m_fFontHeight = (float)SoCmdLineHelp::GetIntByKey(szFirstLine, -1, "FontHeight", 32);
		return true;
	}
	else
	{
		return false;
	}
}
//----------------------------------------------------------------
bool GGUIFileGGM::GetNextImageRect(SoTinyString& kName, stImageRect& kRect)
{
	char* szLine = ReadNextFileLine();
	if (szLine == 0)
	{
		return false;
	}

	const int nSplitIndex = SoStrChr(szLine, '=');
	if (nSplitIndex == -1)
	{
		return false;
	}

	szLine[nSplitIndex] = 0;
	const char* szRectName = szLine;
	const char* szRectData = szLine + nSplitIndex + 1;
	//
    kName = SoStrSlim(szRectName);
	float fX = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "x", 0);
	float fY = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "y", 0);
	float fW = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "w", 0);
	float fH = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "h", 0);
	kRect.left = fX / m_fTexWidth;
	kRect.right = (fX + fW) / m_fTexWidth;
	kRect.top = fY / m_fTexHeight;
	kRect.bottom = (fY + fH) / m_fTexHeight;
	kRect.width = fW;
	kRect.height = fH;
	return true;
}
//----------------------------------------------------------------
bool GGUIFileGGM::GetNextImageFontRect(SoTinyString& kName, stImageFontRect& kRect)
{
	char* szLine = ReadNextFileLine();
	if (szLine == 0)
	{
		return false;
	}

	const int nSplitIndex = SoStrChr(szLine, '=');
	if (nSplitIndex == -1)
	{
		return false;
	}

	szLine[nSplitIndex] = 0;
	const char* szRectName = szLine;
	const char* szRectData = szLine + nSplitIndex + 1;
	//
    const char* szValue = SoStrSlim(szRectName);
    //空格符号特殊处理
    if (szValue[0] == 's' && szValue[1] == 'p' && szValue[2] == 'a' && szValue[3] == 'c' && szValue[4] == 'e')
    {
        //是“space”，是空格
        kName.SetValue(" ");
    }
    else
    {
        kName.SetValue(szValue);
    }
    //
    float fX = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "x", 0);
    float fY = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "y", 0);
    float fW = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "w", 0);
    float fH = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "h", 0);
    kRect.left = fX / m_fTexWidth;
    kRect.right = (fX + fW) / m_fTexWidth;
    kRect.top = fY / m_fTexHeight;
    kRect.bottom = (fY + fH) / m_fTexHeight;
	kRect.width = fW;
	kRect.height = fH;
	kRect.offsetX = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "ox", 0);
	kRect.offsetY = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "oy", 0);
	kRect.advanceX = (float)SoCmdLineHelp::GetIntByKey(szRectData, -1, "ax", 0);
	return true;
}
//----------------------------------------------------------------
int GGUIFileGGM::GetImageRectCount()
{
	if (m_pFileBuff == 0)
	{
		return 0;
	}

	int nRectCount = 0;
	for (int i = 0; i < m_nFileSize; ++i)
	{
		if (m_pFileBuff[i] == '{')
		{
			++nRectCount;
		}
	}
	return nRectCount;
}
//----------------------------------------------------------------
float GGUIFileGGM::GetFontSize()
{
    return m_fFontSize;
}
//----------------------------------------------------------------
float GGUIFileGGM::GetFontHeight()
{
    return m_fFontHeight;
}
//----------------------------------------------------------------
void GGUIFileGGM::CloseGgmFile()
{
    SoFileHelp::DeleteFile(m_pFile);
    m_pFileBuff = 0;
	m_nFileSize = 0;
	m_nReadPointer = 0;
	m_fTexWidth = 256.0f;
	m_fTexHeight = 256.0f;
	m_fFontSize = 24.0f;
	m_fFontHeight = 32.0f;
}
//----------------------------------------------------------------
char* GGUIFileGGM::ReadNextFileLine()
{
	if (m_pFileBuff == 0)
	{
		return 0;
	}
	if (m_nReadPointer >= m_nFileSize)
	{
		return 0;
	}
	//
	const int nOldPointer = m_nReadPointer;
	for (int i = m_nReadPointer; i < m_nFileSize; ++i)
	{
		if (m_pFileBuff[i] == '\n')
		{
			m_pFileBuff[i] = 0;
			m_nReadPointer = i + 1;
			break;
		}
	}
	return (m_pFileBuff+nOldPointer);
}
//----------------------------------------------------------------
