#include "pch.h"
#include "CWave4.h"

#include "CResourceMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CImage.h"
#include "CPlayer.h"

CWave4::CWave4()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Wave");

	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"WaveAnimation", m_pImage, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(0.f, 0.f), 64.f, 8, 0.2f);

	GetAnimator()->Play(L"WaveAnimation", 4, true);

	AddCollider(L"Image\\map\\Environment\\Wave1.Collider");
}

CWave4::~CWave4()
{
}


void CWave4::tick()
{
	CEnvironment::tick();
}

void CWave4::render(HDC _dc)
{
	CEnvironment::render(_dc);
}