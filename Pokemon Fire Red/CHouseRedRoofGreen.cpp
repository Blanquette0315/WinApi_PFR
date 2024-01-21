#include "pch.h"
#include "CHouseRedRoofGreen.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CHouseRedRoofGreen::CHouseRedRoofGreen()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"HouseRedRoof");

	AddCollider(L"Image\\map\\Building\\HouseRedRoof.Collider");
}

CHouseRedRoofGreen::~CHouseRedRoofGreen()
{
	CEnvironment::~CEnvironment();
}


void CHouseRedRoofGreen::tick()
{
	CEnvironment::tick();
}

void CHouseRedRoofGreen::render(HDC _dc)
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

void CHouseRedRoofGreen::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	// Scene change
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if (!(0 == GetCollider(0)->GetCollisionCount())
			&& (0 == m_iRe_render))
		{
			m_iRe_render++;
			IS_Collision = true;


			CEventMgr::CreateMgr()->Re_Render(this);
		}
	}

	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((1 == GetCollider(4)->GetCollisionCount())
			&& (GetCollider(4)->GetColliderType() == COLLIDER_TYPE::EVENT))
		{
			SceneChange(SCENE_TYPE::GREENHOUSE);
		}
	}

}

void CHouseRedRoofGreen::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		IS_Collision = true;
	}

}

void CHouseRedRoofGreen::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((0 == GetCollider(0)->GetCollisionCount())
			&& (1 == m_iRe_render))
		{
			m_iRe_render--;
			IS_Collision = false;
			CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
		}
	}
}