#include "pch.h"
#include "CWave6.h"

#include "CResourceMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CImage.h"
#include "CPlayer.h"

CWave6::CWave6()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Wave");

	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"WaveAnimation", m_pImage, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(0.f, 0.f), 64.f, 8, 0.2f);

	GetAnimator()->Play(L"WaveAnimation", 6, true);

	AddCollider(L"Image\\map\\Environment\\Wave1.Collider");
}

CWave6::~CWave6()
{
}


void CWave6::tick()
{
	CEnvironment::tick();
}

void CWave6::render(HDC _dc)
{
	CEnvironment::render(_dc);
}