#include "pch.h"
#include "CRedHouse1f.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CRedHouse1f::CRedHouse1f()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, IS_Event(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"HeroHouse1f");

	AddCollider(L"Image\\map\\Building\\HeroHouse1f.Collider");
}

CRedHouse1f::~CRedHouse1f()
{
}

void CRedHouse1f::tick()
{
	CEnvironment::tick();

	// 카메라 범위 연산
	Vec2 CamRange = {};
	CamRange.x = m_pImage->GetWidth();
	CamRange.y = m_pImage->GetHeight();
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CRedHouse1f::render(HDC _dc)
{
	
	Vec2 vPos = CCameraMgr::CreateMgr()->GetRenderPos(GetPos());
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (UINT)vPos.x
		, (UINT)vPos.y
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);

	CEnvironment::render(_dc);
}

void CRedHouse1f::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	// Scene change
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((1 == GetCollider(0)->GetCollisionCount())
			&& (GetCollider(0)->GetColliderType() == COLLIDER_TYPE::EVENT)
			&& (IS_Event == false))
		{
			IS_Event = true;
			SceneChange(SCENE_TYPE::PALLET_CITY);
		}
	}

	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((1 == GetCollider(1)->GetCollisionCount())
			&& (GetCollider(1)->GetColliderType() == COLLIDER_TYPE::EVENT))
		{
			SceneChange(SCENE_TYPE::REDHOUSESCENE2F);
		}
	}
}

void CRedHouse1f::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		IS_Collision = true;
	}
}

void CRedHouse1f::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	// Render 기준 Collider 충돌 해제 시 IS_Collision false로 변경
	
}