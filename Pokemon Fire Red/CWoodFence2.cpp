#include "pch.h"
#include "CWoodFence2.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CWoodFence2::CWoodFence2()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"WoodFence2");

	AddCollider(L"Image\\map\\Environment\\WoodFence2.Collider");
}

CWoodFence2::~CWoodFence2()
{
	CEnvironment::~CEnvironment();
}

void CWoodFence2::tick()
{
	CEnvironment::tick();
}

void CWoodFence2::render(HDC _dc)
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

void CWoodFence2::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	// Render ���� Collider �浹 ���� �� IS_Collision true�� ����
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
}

void CWoodFence2::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
	}
}

void CWoodFence2::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	// Render ���� Collider �浹 ���� �� IS_Collision false�� ����
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((0 == GetCollider(0)->GetCollisionCount())
			&& (1 == m_iRe_render))
		{
			m_iRe_render = 0;
			IS_Collision = false;
			CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
		}
	}
}