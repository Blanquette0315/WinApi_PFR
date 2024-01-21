#include "pch.h"
#include "CHouse2Table.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CHouse2Table::CHouse2Table()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"House2Table");

	AddCollider(L"Image\\map\\Environment\\House2Table.Collider");
}

CHouse2Table::~CHouse2Table()
{
	CEnvironment::~CEnvironment();
}

void CHouse2Table::tick()
{
	CEnvironment::tick();
}

void CHouse2Table::render(HDC _dc)
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

void CHouse2Table::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	// Render 기준 Collider 충돌 해제 시 IS_Collision true로 변경
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

void CHouse2Table::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
	}
}

void CHouse2Table::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	// Render 기준 Collider 충돌 해제 시 IS_Collision false로 변경
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