#include "pch.h"
#include "CRedHouse2f.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CRedHouse2f::CRedHouse2f()
	: m_pImage(nullptr)
	, IS_Collision(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"HeroHouse2f");

	AddCollider(L"Image\\map\\Building\\HeroHouse2f.Collider");
}

CRedHouse2f::~CRedHouse2f()
{
}

void CRedHouse2f::tick()
{
	CEnvironment::tick();

	// 카메라 범위 연산
	Vec2 CamRange = {};
	CamRange.x = m_pImage->GetWidth();
	CamRange.y = m_pImage->GetHeight();
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CRedHouse2f::render(HDC _dc)
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

void CRedHouse2f::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((1 == GetCollider(0)->GetCollisionCount())
			&& (GetCollider(0)->GetColliderType() == COLLIDER_TYPE::EVENT))
		{
			SceneChange(SCENE_TYPE::REDHOUSESCENE1F);
		}
	}
}

void CRedHouse2f::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		IS_Collision = true;
	}
}

void CRedHouse2f::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	
}