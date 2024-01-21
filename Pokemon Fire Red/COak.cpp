#include "pch.h"
#include "COak.h"

#include "CSceneMgr.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"

#include "CImage.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CScene.h"

COak::COak()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
	, m_eLBRT(LBRT::BOT)
	, m_bEvent(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Oak");

	AddCollider(L"Image\\NPC\\Oak.Collider");
}

COak::~COak()
{
	CEnvironment::~CEnvironment();
}

void COak::tick()
{
	if (m_bEvent && (IS_TAP(ENTER)))
	{
		CSceneMgr::CreateMgr()->GetCurScene()->SetEvent(true);
		m_bEvent = false;
	}

	CEnvironment::tick();
}

void COak::render(HDC _dc)
{
	Vec2 vPos = CCameraMgr::CreateMgr()->GetRenderPos(GetPos());

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	if (m_eLBRT == LBRT::BOT)
	{
		AlphaBlend(_dc, (int)vPos.x - 32
			, (int)vPos.y - 80
			, 64, 80
			, m_pImage->GetDC(), 0, 0, 64, 80, tFunc);
	}
	else if (m_eLBRT == LBRT::LEFT)
	{
		AlphaBlend(_dc, (int)vPos.x - 32
			, (int)vPos.y - 80
			, 64, 80
			, m_pImage->GetDC(), 0, 80, 64, 80, tFunc);
	}
	else if (m_eLBRT == LBRT::RIGHT)
	{
		AlphaBlend(_dc, (int)vPos.x - 32
			, (int)vPos.y - 80
			, 64, 80
			, m_pImage->GetDC(), 0, 160, 64, 80, tFunc);
	}
	else if (m_eLBRT == LBRT::TOP)
	{
		AlphaBlend(_dc, (int)vPos.x - 32
			, (int)vPos.y - 80
			, 64, 80
			, m_pImage->GetDC(), 0, 240, 64, 80, tFunc);
	}

	CEnvironment::render(_dc);
}

void COak::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if (!(0 == GetCollider(0)->GetCollisionCount())
			&& (0 == m_iRe_render))
		{
			m_iRe_render++;
			IS_Collision = true;
			CEventMgr::CreateMgr()->Re_Render(this);
		}

		if (!(0 == GetCollider(2)->GetCollisionCount()))
		{
			m_eLBRT = LBRT::LEFT;
			m_bEvent = true;
		}
		else if (!(0 == GetCollider(3)->GetCollisionCount()))
		{
			m_eLBRT = LBRT::BOT;
			m_bEvent = true;
		}
		else if (!(0 == GetCollider(4)->GetCollisionCount()))
		{
			m_eLBRT = LBRT::RIGHT;
			m_bEvent = true;
		}
		else if (!(0 == GetCollider(5)->GetCollisionCount()))
		{
			m_eLBRT = LBRT::TOP;
			m_bEvent = true;
		}
	}
}

void COak::CollisionEndOverlap(CCollider* _pOtherCollider)
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
