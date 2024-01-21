#include "pch.h"
#include "CEscalator1f.h"

#include "CResourceMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CImage.h"
#include "CPlayer.h"

CEscalator1f::CEscalator1f()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Escalator1f");

	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"Escalator1fAnimation", m_pImage, Vec2(0.f, 0.f), Vec2(128.f, 160.f), Vec2(0.f, 0.f), 128.f, 3, 0.2f);

	GetAnimator()->Play(L"Escalator1fAnimation", true);

	AddCollider(L"Image\\map\\Environment\\Inside\\Escalator1f.Collider");

}

CEscalator1f::~CEscalator1f()
{
	CEnvironment::~CEnvironment();
}


void CEscalator1f::tick()
{
	CEnvironment::tick();
}

void CEscalator1f::render(HDC _dc)
{
	if (IS_Collision)
	{
		GetAnimator()->CuntinuePlay(L"Escalator1fAnimation", true);
		IS_Collision = false;
	}

	CEnvironment::render(_dc);
}


void CEscalator1f::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())
		&& (1 == GetCollider(0)->GetCollisionCount())
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
			SceneChange(SCENE_TYPE::CENTER2F);
		}
	}
}

void CEscalator1f::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CEscalator1f::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())
		&& (0 == GetCollider(0)->GetCollisionCount())
		&& (1 == m_iRe_render))
	{
		m_iRe_render = 0;
		IS_Collision = false;
		CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
	}
}