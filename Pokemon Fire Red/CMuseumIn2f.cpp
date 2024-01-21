#include "pch.h"
#include "CMuseumIn2f.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CMuseumIn2f::CMuseumIn2f()
	: m_pImage(nullptr)
	, IS_Collision(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Museum2f");

	AddCollider(L"Image\\map\\Building\\Museum2f.Collider");
}

CMuseumIn2f::~CMuseumIn2f()
{
}

void CMuseumIn2f::tick()
{
	CEnvironment::tick();

	Vec2 CamRange = {};
	CamRange.x = m_pImage->GetWidth();
	CamRange.y = m_pImage->GetHeight();
	CamRange.y += 44;
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CMuseumIn2f::render(HDC _dc)
{
	Vec2 vPos = CCameraMgr::CreateMgr()->GetRenderPos(GetPos());

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (int)vPos.x
		, (int)vPos.y
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);

	CEnvironment::render(_dc);
}

void CMuseumIn2f::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	// Render 기준 Collider 충돌 해제 시 IS_Collision true로 변경
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if (!(0 == GetCollider(0)->GetCollisionCount()))
		{
			IS_Collision = true;
			CEventMgr::CreateMgr()->Re_Render(this);
		}
	}
}

void CMuseumIn2f::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		IS_Collision = true;
	}
}

void CMuseumIn2f::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	// Render 기준 Collider 충돌 해제 시 IS_Collision false로 변경
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((0 == GetCollider(0)->GetCollisionCount()))
		{

			IS_Collision = false;
			CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
		}
	}
}