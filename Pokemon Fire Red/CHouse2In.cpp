#include "pch.h"
#include "CHouse2In.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CHouse2In::CHouse2In()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, IS_Event(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"House2In");

	AddCollider(L"Image\\map\\Building\\House2In.Collider");
}

CHouse2In::~CHouse2In()
{
}

void CHouse2In::tick()
{
	CEnvironment::tick();

	// 카메라 범위 연산
	Vec2 CamRange = {};
	CamRange.x = m_pImage->GetWidth();
	CamRange.y = m_pImage->GetHeight();
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CHouse2In::render(HDC _dc)
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

void CHouse2In::CollisionBeginOverlap(CCollider* _pOtherCollider)
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

void CHouse2In::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		IS_Collision = true;
	}
}

void CHouse2In::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	
}