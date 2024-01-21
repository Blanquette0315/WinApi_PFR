#include "pch.h"
#include "CWave.h"

#include "CResourceMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CImage.h"
#include "CPlayer.h"

CWave::CWave()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Wave");

	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"WaveAnimation", m_pImage, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(0.f, 0.f), 64.f, 8, 0.2f);

	GetAnimator()->Play(L"WaveAnimation", 0, true);

	//AddCollider(L"Image\\map\\Environment\\Wave1.Collider");
}

CWave::~CWave()
{
	CEnvironment::~CEnvironment();
}

void CWave::tick()
{
	CEnvironment::tick();
}

void CWave::render(HDC _dc)
{
	/*if (GetISTool())
	{
		Vec2 vPos = CCameraMgr::CreateMgr()->GetRenderPos(GetPos());

		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = AC_SRC_ALPHA;
		tFunc.SourceConstantAlpha = 255;

		AlphaBlend(_dc, (int)vPos.x - m_pImage->GetWidth() / 2
			, (int)vPos.y - m_pImage->GetHeight()
			, m_pImage->GetWidth(), m_pImage->GetHeight()
			, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
	}*/

	CEnvironment::render(_dc);
}