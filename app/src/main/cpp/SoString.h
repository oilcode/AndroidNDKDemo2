//-----------------------------------------------------------------------------
#ifndef _SoString_h_
#define _SoString_h_
//-----------------------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//-----------------------------------------------------------------------------
class SODLL SoString
{
public:
	SoString();
	SoString(const char* pszString);
	SoString(const SoString& other);
	~SoString();

	void SetValue(const char* pszString, soint32 nStringLen = 0);
	const char* GetValue() const;
	soint32 GetLength() const;

	char* GetBuffer();
	soint32 GetBufferSize() const;

	void Reserve(soint32 nSize);
	void Clear();

	//用等号赋值操作
	void operator = (const char* pszString);
	void operator = (const SoString& other);

	//<运算符的重载方法有两种：
	//1，成员函数 bool operator < (const SoString& other);
	//2，全局函数 friend bool operator < (const SoString& left, const SoString& right);
	//这两种方法都支持这样的表达式 bool br = TinyStr1 < TinyStr2;
	//STL容器在排序时会使用到<运算符，只有第2种方法才支持STL容器。
	friend bool operator < (const SoString& left, const SoString& right);

private:
	char* m_szBuffer;
	soint32 m_nBuffSize;
	soint32 m_nStringLen;
};
//-----------------------------------------------------------------------------
inline SoString::SoString()
:m_szBuffer(0)
,m_nBuffSize(0)
,m_nStringLen(0)
{

}
//-----------------------------------------------------------------------------
inline SoString::SoString(const char* pszString)
:m_szBuffer(0)
,m_nBuffSize(0)
,m_nStringLen(0)
{
	SetValue(pszString);
}
//-----------------------------------------------------------------------------
inline SoString::SoString(const SoString& other)
:m_szBuffer(0)
,m_nBuffSize(0)
,m_nStringLen(0)
{
	SetValue(other.GetValue());
}
//-----------------------------------------------------------------------------
inline SoString::~SoString()
{
	if (m_szBuffer)
	{
		SoFree(m_szBuffer);
		m_szBuffer = 0;
	}
}
//-----------------------------------------------------------------------------
inline const char* SoString::GetValue() const
{
	return m_szBuffer ? m_szBuffer : "";
}
//-----------------------------------------------------------------------------
inline soint32 SoString::GetLength() const
{
	return m_nStringLen;
}
//-----------------------------------------------------------------------------
inline char* SoString::GetBuffer()
{
	return m_szBuffer;
}
//-----------------------------------------------------------------------------
inline soint32 SoString::GetBufferSize() const
{
	return m_nBuffSize;
}
//-----------------------------------------------------------------------------
inline void SoString::Clear()
{
	if (m_szBuffer)
	{
		m_szBuffer[0] = 0;
	}
	m_nStringLen = 0;
}
//-----------------------------------------------------------------------------
inline void SoString::operator = (const char* pszString)
{
	//if (pszString != 0 && (&(m_szBuffer[0]) == &(pszString[0])))
	//{
	//	//不能把自己赋值给自己
	//	return;
	//}
	//else
	//{
	//	SetValue(pszString);
	//}
	//“把自己赋值给自己”这种情况几乎不会出现；
	//即使出现，执行 SetValue() 函数也不会出错。
	//所以就不要执行if判断了。
	SetValue(pszString);
}
//-----------------------------------------------------------------------------
inline void SoString::operator = (const SoString& other)
{
	//if (this == &other)
	//{
	//	//不能把自己赋值给自己
	//	return;
	//}
	//else
	//{
	//	SetValue(other.GetValue());
	//}
	//“把自己赋值给自己”这种情况几乎不会出现；
	//即使出现，执行 SetValue() 函数也不会出错。
	//所以就不要执行if判断了。
	SetValue(other.GetValue());
}
//-----------------------------------------------------------------------------
#endif //_SoString_h_
//-----------------------------------------------------------------------------
