#pragma once
class CMyString
{

public:
	CMyString();
	CMyString(const char* pszString);
	~CMyString();
	CMyString& operator= (const char* pszString);
	operator char* ();

	char* m_pBuf;
	int nLen = 0;;
};

