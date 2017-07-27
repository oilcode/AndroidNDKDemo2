//-----------------------------------------------------------------------------
#ifndef _SoCmdLineHelp_h_
#define _SoCmdLineHelp_h_
//-----------------------------------------------------------------------------
class SoCmdLineHelp
{
public:
	//--nCmdLength 字符串长度。可以设置为-1，函数内部会妥善处理。
	static char* GetValueByKey(const char* szCmdLine, const int nCmdLength, const char* szKey);
	static int GetIntByKey(const char* szCmdLine, const int nCmdLength, const char* szKey, const int nDefaultValue);
	static float GetFloatByKey(const char* szCmdLine, const int nCmdLength, const char* szKey, const float fDefaultValue);
};
//-----------------------------------------------------------------------------
#endif //_SoCmdLineHelp_h_
//-----------------------------------------------------------------------------
