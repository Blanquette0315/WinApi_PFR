#include "pch.h"
#include "COaksLabIn.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

COaksLabIn::COaksLabIn()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, IS_Event(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"OaksLabIn");

	AddCollider(L"Image\\map\\Building\\OaksLabIn.Collider");
}

COaksLabIn::~COaksLabIn()
{
}

void COaksLabIn::tick()
{
	CEnvironment::tick();

	Vec2 CamRange = {};
	CamRange.x = m_pImage->GetWidth();
	CamRange.y = m_pImage->GetHeight();
	CamRange.y += 44;
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void COaksLabIn::render(HDC _dc)
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

void COaksLabIn::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
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
}

void COaksLabIn::CollisionOverlap(CCollider* _pOtherCollider)
{
	
}

void COaksLabIn::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	
}