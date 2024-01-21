#include "pch.h"
#include "CEngine.h"

#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResourceMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CUIMgr.h"
#include "CEventMgr.h"
#include "CSoundMgr.h"

#include "CResource.h"
#include "CImage.h"
#include "CSound.h"


CEngine::CEngine()
	: m_hMainWindow(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
	, m_pBackBuffer(nullptr)
	, m_bTickOnce(false)
{

}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWindow, m_hDC);

	for (UINT i = 0; i < (UINT)PEN_COLOR::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CEngine::init(HWND _hwnd, UINT _Width,  UINT _Hight)
{
	m_hMainWindow = _hwnd;

	m_hDC = GetDC(m_hMainWindow);

	m_ptResolution.x = _Width;
	m_ptResolution.y = _Hight;

	RECT rt = { 0, 0, (LONG)_Width , (LONG)_Hight };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_hMainWindow, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWindow, true);

	CreateDefaultGDIObject();

	// 이중 버퍼
	m_pBackBuffer = CResourceMgr::CreateMgr()->CreateImg(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	
	// ==========
	// =  Init  =
	// ==========

	CPathMgr::CreateMgr()->init();
	CSoundMgr::CreateMgr()->init();
	CResourceMgr::CreateMgr()->init();
	CTimeMgr::CreateMgr()->init();
	CKeyMgr::CreateMgr()->init();

	CCameraMgr::CreateMgr()->init();

	CSceneMgr::CreateMgr()->init();
}

void CEngine::tick()
{
	// ==========
	// = UpDate =
	// ==========
	CTimeMgr::CreateMgr()->tick();
	CKeyMgr::CreateMgr()->tick();
	CSceneMgr::CreateMgr()->tick();

	CCameraMgr::CreateMgr()->tick();

	CUIMgr::CreateMgr()->tick();

	CCollisionMgr::CreateMgr()->tick();


	// ==========
	// = Render =
	// ==========

	// 버퍼 클리어 
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_pBackBuffer->GetDC(), m_arrBrush[(UINT)BRUSH_COLOR::BLACK]);
	Rectangle(m_pBackBuffer->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	SelectObject(m_pBackBuffer->GetDC(), hPrevBrush);

	CSceneMgr::CreateMgr()->render(m_pBackBuffer->GetDC());
	CEventMgr::CreateMgr()->render(m_pBackBuffer->GetDC());
	CTimeMgr::CreateMgr()->render(m_pBackBuffer->GetDC());
	CCameraMgr::CreateMgr()->render(m_pBackBuffer->GetDC());

	// 완성된 BackBuffer를 MainBuffer로 옮겨주기
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pBackBuffer->GetDC(), 0, 0, SRCCOPY);

	if(!m_bTickOnce)
		m_bTickOnce = true;

	// EventMgr
	CEventMgr::CreateMgr()->tick();

}

void CEngine::CreateDefaultGDIObject()
{
	// 자주 쓸 색상의 펜 생성
	m_arrPen[(UINT)PEN_COLOR::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_COLOR::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_COLOR::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// 자주 쓸 Brush 생성
	m_arrBrush[(UINT)BRUSH_COLOR::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::MAGENTA] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
}