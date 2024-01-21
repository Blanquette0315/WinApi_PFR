#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_llFrequence{}
	, m_llCurCount{}
	, m_llPrevCount{}
	, m_fAccTime(0.f)
	, m_fDeltaTime(0.f)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	QueryPerformanceFrequency(&m_llFrequence);
	QueryPerformanceCounter(&m_llPrevCount);
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequence.QuadPart;

	m_llPrevCount.QuadPart = m_llCurCount.QuadPart;
}

void CTimeMgr::render(HDC _dc)
{
	static int iCount = 0;
	++iCount;


	// 1 초에 한번
	m_fAccTime += m_fDeltaTime;
	if (1.f < m_fAccTime)
	{
		HWND hWnd = CEngine::CreateMgr()->GetMainHwnd();

		wchar_t szFloat[50] = {};
		float FPS = 1.f / m_fDeltaTime;
		swprintf_s(szFloat, 50, L"DeltaTime : %d", iCount);
		int iLen = (int)wcsnlen_s(szFloat, 50);
		//TextOut(_dc, 10, 10, szFloat, iLen);

		SetWindowText(hWnd, szFloat);

		// 누적시간, 카운트 초기화
		m_fAccTime = 0.f;
		iCount = 0;
	}
}