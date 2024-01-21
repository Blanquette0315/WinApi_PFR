#include "pch.h"
#include "CWave1.h"

#include "CResourceMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CImage.h"
#include "CPlayer.h"

CWave1::CWave1()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Wave");

	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"WaveAnimation", m_pImage, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(0.f, 0.f), 64.f, 8, 0.2f);

	GetAnimator()->Play(L"WaveAnimation", 1, true);

	AddCollider(L"Image\\map\\Environment\\Wave1.Collider");
}

CWave1::~CWave1()
{
}


void CWave1::tick()
{
	CEnvironment::tick();
}

void CWave1::render(HDC _dc)
{
	CEnvironment::render(_dc);
}