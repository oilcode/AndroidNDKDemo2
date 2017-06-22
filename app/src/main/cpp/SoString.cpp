//-----------------------------------------------------------------------------
#include "SoString.h"
//-----------------------------------------------------------------------------
void SoString::SetValue(const char* pszString, soint32 nStringLen)
{
	if (nStringLen == 0)
	{
		if (pszString)
		{
			while (pszString[nStringLen])
			{
				++nStringLen;
			}
		}
	}

	if (nStringLen == 0)
	{
		Clear();
		return;
	}

	if (m_nBuffSize < nStringLen+1)
	{
		Reserve(nStringLen+1);
	}

	soint32 i = 0;
	for (; i < nStringLen; ++i)
	{
		m_szBuffer[i] = pszString[i];
	}

	m_szBuffer[i] = 0;
	m_nStringLen = i;
}
//-----------------------------------------------------------------------------
void SoString::Reserve(soint32 nSize)
{
	if (m_nBuffSize >= nSize)
	{
		return;
	}

	char* oldBuffer = m_szBuffer;

	m_szBuffer = (char*)SoMalloc(nSize);
	if (m_szBuffer == 0)
	{
		return;
	}

	m_nBuffSize = nSize;

	if (oldBuffer)
	{
		memcpy(m_szBuffer, oldBuffer, m_nStringLen+1);
		SoFree(oldBuffer);
	}
}
//-----------------------------------------------------------------------------
bool operator < (const SoString& left, const SoString& right)
{
	const soint32 nMinLen = left.GetLength() <= right.GetLength() ? left.GetLength() : right.GetLength();
	for (soint32 i=0; i<=nMinLen; ++i) //注意，这里必须是<=
	{
		if (left.m_szBuffer[i] && right.m_szBuffer[i])
		{
			if (left.m_szBuffer[i] == right.m_szBuffer[i])
			{
				//继续比较；什么也不做。
			}
			else
			{
				return (left.m_szBuffer[i] < right.m_szBuffer[i]);
			}
		}
		else
		{
			//要么left.m_szBuffer[i]为0，要么right.m_szBuffer[i]为0，要么都为0
			if (left.m_szBuffer[i])
			{
				return false;
			}
			if (right.m_szBuffer[i])
			{
				return true;
			}
			return false;
		}
	}
	return false;
}
//-----------------------------------------------------------------------------
