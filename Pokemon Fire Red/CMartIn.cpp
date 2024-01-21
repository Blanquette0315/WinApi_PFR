#include "pch.h"
#include "CMartIn.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CMartIn::CMartIn()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, IS_Event(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"MartIn");

	AddCollider(L"Image\\map\\Building\\MartIn.Collider");
}

CMartIn::~CMartIn()
{
}

void CMartIn::tick()
{
	CEnvironment::tick();

	// 카메라 범위 연산
	Vec2 CamRange = {};
	CamRange.x = m_pImage->GetWidth();
	CamRange.y = m_pImage->GetHeight();
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CMartIn::render(HDC _dc)
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

void CMartIn::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((1 == GetCollider(0)->GetCollisionCount())
			&& (GetCollider(0)->GetColliderType() == COLLIDER_TYPE::EVENT)
			&& (IS_Event == false))
		{
			IS_Event = true;
			SceneChange(SCENE_TYPE::VIRIDIAN_CITY);
		}
	}
}

void CMartIn::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		IS_Collision = true;
	}
}

void CMartIn::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	
}