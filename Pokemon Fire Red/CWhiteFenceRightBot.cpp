#include "pch.h"
#include "CWhiteFenceRightBot.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CWhiteFenceRightBot::CWhiteFenceRightBot()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"WhiteFenceRightBot");

	AddCollider(L"Image\\map\\Environment\\WhiteFenceRightBot.Collider");
}

CWhiteFenceRightBot::~CWhiteFenceRightBot()
{
	CEnvironment::~CEnvironment();
}

void CWhiteFenceRightBot::tick()
{
	CEnvironment::tick();
}

void CWhiteFenceRightBot::render(HDC _dc)
{
	if (IS_Collision || GetISTool())
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
	}

	CEnvironment::render(_dc);
}

void CWhiteFenceRightBot::CollisionBeginOverlap(CCollider* _pOtherCollider)
{

}

void CWhiteFenceRightBot::CollisionOverlap(CCollider* _pOtherCollider)
{

}

void CWhiteFenceRightBot::CollisionEndOverlap(CCollider* _pOtherCollider)
{

}