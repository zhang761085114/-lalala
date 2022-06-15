#include "CMyString.h"
#include <string>

CMyString::CMyString()
{
	m_pBuf = nullptr;
}

CMyString::CMyString(const char* pszString)
{
	nLen = strlen(pszString);
	m_pBuf = new char[nLen + 1];
	strcpy_s(m_pBuf, nLen + 1, pszString);
}

CMyString::~CMyString()
{
	if (m_pBuf != nullptr) {

		delete m_pBuf;
		nLen = 0;
		m_pBuf = nullptr;
	}
}

CMyString& CMyString::operator=(const char* pszString)
{

	if (nLen < strlen(pszString)) {

		delete[] m_pBuf;
		nLen = strlen(pszString);
		m_pBuf = new char[nLen + 1];
		strcpy_s(m_pBuf, nLen + 1, pszString);
		return *this;
	}
	nLen = strlen(pszString);
	strcpy_s(m_pBuf, nLen + 1, pszString);
	return *this;
}

CMyString::operator char* ()
{
	return m_pBuf;
}

