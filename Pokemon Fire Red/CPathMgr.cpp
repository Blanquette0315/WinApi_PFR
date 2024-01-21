#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	GetCurrentDirectory(256, m_szContentPath);

	size_t iLen = wcsnlen_s(m_szContentPath, 256);
	for (size_t i = iLen; i > 0; --i)
	{
		if (L'\\' == m_szContentPath[i])
		{
			m_szContentPath[i + 1] = L'\0';
			break;
		}

		continue;
	}

	// 상위 폴더로 나간 뒤 bin -> Resource 폴더로 이동
	wcscat_s(m_szContentPath, L"bin\\Resource\\");
}