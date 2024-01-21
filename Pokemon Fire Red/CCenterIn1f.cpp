#include "pch.h"
#include "CCenterIn1f.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CCenterIn1f::CCenterIn1f()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, IS_Event(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"CenterIn1f");

	AddCollider(L"Image\\map\\Building\\CenterIn1f.Collider");
}

CCenterIn1f::~CCenterIn1f()
{
}

void CCenterIn1f::tick()
{
	CEnvironment::tick();

	// 카메라 범위 연산
	Vec2 CamRange = {};
	CamRange.x = m_pImage->GetWidth();
	CamRange.y = m_pImage->GetHeight();
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CCenterIn1f::render(HDC _dc)
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

void CCenterIn1f::CollisionBeginOverlap(CCollider* _pOtherCollider)
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

void CCenterIn1f::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		IS_Collision = true;
	}
}

void CCenterIn1f::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	
}