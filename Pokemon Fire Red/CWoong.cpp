#include "pch.h"
#include "CWoong.h"

#include "CSceneMgr.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"

#include "CImage.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CScene.h"

CWoong::CWoong()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
	, m_bEvent(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Oak");

	AddCollider(L"Image\\NPC\\Oak.Collider");
}

CWoong::~CWoong()
{
	CEnvironment::~CEnvironment();
}

void CWoong::tick()
{
	
	CEnvironment::tick();
}

void CWoong::render(HDC _dc)
{
	Vec2 vPos = CCameraMgr::CreateMgr()->GetRenderPos(GetPos());

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (int)vPos.x - 32
		, (int)vPos.y - 80
		, 64, 80
		, m_pImage->GetDC(), 0, 0, 64, 80, tFunc);
	

	CEnvironment::render(_dc);
}

void CWoong::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
}

void CWoong::CollisionEndOverlap(CCollider* _pOtherCollider)
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