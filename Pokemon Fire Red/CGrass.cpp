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
//	// Render ���� Collider �浹 ���� �� IS_Collision true�� ����
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
//		// ���� ��ī��Ʈ (�̹�Ʈ �ݶ��̴��� �ε����� ���� �����ؾ��Ѵ�.
//		srand((unsigned int)time(NULL));
//		m_random = rand() % 10;
//		if (m_random < 2)
//		{
//			// rerender�� ���������� ������ �ȵȴ�.
//			//CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
//
//			// �׳� ��Ʋ ������ �Ѱ��ָ� �ȵȴ�. (��Ʋ ������ ���� �÷��̾� ��ġ�� �ٲ�� �ȵǱ� ����.)
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
	// Render ���� Collider �浹 ���� �� IS_Collision false�� ����
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