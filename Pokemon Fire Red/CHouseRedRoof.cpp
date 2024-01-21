#include "pch.h"
#include "CHouseRedRoof.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CHouseRedRoof::CHouseRedRoof()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"HouseRedRoof");

	/*AddCollider(new CCollider);
	GetCollider(0)->SetOffset(Vec2(0,-119));
	GetCollider(0)->SetScale(Vec2(304,238));
	GetCollider(0)->SetColliderType(COLLIDER_TYPE::DEFAULT);

	AddCollider(new CCollider);
	GetCollider(1)->SetOffset(Vec2(0, -154));
	GetCollider(1)->SetScale(Vec2(m_pImage->GetWidth(), m_pImage->GetHeight()));
	GetCollider(1)->SetColliderType(COLLIDER_TYPE::RE_RENDER);*/

	// ������ ��� ������ �ݶ��̴� FinalPos, Scale�� ���� �´�.

	AddCollider(L"Image\\map\\Building\\HouseRedRoof.Collider");
}

CHouseRedRoof::~CHouseRedRoof()
{
	CEnvironment::~CEnvironment();
}


void CHouseRedRoof::tick()
{
	CEnvironment::tick();
}

void CHouseRedRoof::render(HDC _dc)
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

void CHouseRedRoof::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	// ���ʰ� �浹 �� SceneChange �̹�Ʈ�� �߻� �ؾ��Ѵ�.

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

		if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
		{
			if ((1 == GetCollider(4)->GetCollisionCount())
				&& (GetCollider(4)->GetColliderType() == COLLIDER_TYPE::EVENT))
			{
				SceneChange(SCENE_TYPE::REDHOUSESCENE1F);
			}
		}
	}
}

void CHouseRedRoof::CollisionOverlap(CCollider* _pOtherCollider)
{
	// ImegeRender
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner()))
	{
		IS_Collision = true;
	}

}

void CHouseRedRoof::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	// Render ���� Collider �浹 ���� �� IS_Collision false�� ����
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
