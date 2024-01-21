#include "pch.h"
#include "CGrass.h"

#include <cstdlib>
#include <ctime>

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CGrass::CGrass()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
	, m_random(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Grass");

	AddCollider(L"Image\\map\\Environment\\Grass.Collider");
}

CGrass::~CGrass()
{
	CEnvironment::~CEnvironment();
}

void CGrass::tick()
{
	CEnvironment::tick();
}

void CGrass::render(HDC _dc)
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

//void CGrass::CollisionBeginOverlap(CCollider* _pOtherCollider)
//{
//	// Render 기준 Collider 충돌 해제 시 IS_Collision true로 변경
//	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
//	{
//		/*if (!(0 == GetCollider(0)->GetCollisionCount())
//			&& (0 == m_iRe_render))
//		{
//			m_iRe_render++;
//			IS_Collision = true;
//			CEventMgr::CreateMgr()->Re_Render(this);
//		}*/
//
//		// 랜덤 인카운트 (이밴트 콜라이더와 부디쳤을 때만 동작해야한다.
//		srand((unsigned int)time(NULL));
//		m_random = rand() % 10;
//		if (m_random < 2)
//		{
//			// rerender를 해제해주지 않으면 안된다.
//			//CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
//
//			// 그냥 배틀 씬으로 넘겨주면 안된다. (배틀 종료후 이전 플레이어 위치가 바뀌면 안되기 때문.)
//			if (CEngine::CreateMgr()->GetTickOnce())
//			{
//				SceneChange(SCENE_TYPE::BATTLESCENE);
//			}
//		}
//	}
//}

void CGrass::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		srand((unsigned int)time(NULL));
		m_random = rand() % 10;
		if (m_random < 2)
		{
			if (CEngine::CreateMgr()->GetTickOnce())
			{
				SceneChange(SCENE_TYPE::BATTLESCENE);
			}
		}
	}
}

void CGrass::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CGrass::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	// Render 기준 Collider 충돌 해제 시 IS_Collision false로 변경
	/*if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		if ((0 == GetCollider(0)->GetCollisionCount())
			&& (1 == m_iRe_render))
		{
			m_iRe_render = 0;
			IS_Collision = false;
			CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
		}
	}*/
}