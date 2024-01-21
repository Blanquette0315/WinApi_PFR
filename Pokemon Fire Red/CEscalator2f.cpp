#include "pch.h"
#include "CEscalator2f.h"

#include "CResourceMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CImage.h"
#include "CPlayer.h"

CEscalator2f::CEscalator2f()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Escalator2f");

	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"Escalator2fAnimation", m_pImage, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), 128.f, 3, 0.2f);

	GetAnimator()->Play(L"Escalator2fAnimation", true);

	AddCollider(L"Image\\map\\Environment\\Inside\\Escalator2f.Collider");

}

CEscalator2f::~CEscalator2f()
{
	CEnvironment::~CEnvironment();
}


void CEscalator2f::tick()
{
	CEnvironment::tick();
}

void CEscalator2f::render(HDC _dc)
{
	if (IS_Collision)
	{
		GetAnimator()->CuntinuePlay(L"Escalator2fAnimation", true);
		IS_Collision = false;
	}

	CEnvironment::render(_dc);
}


void CEscalator2f::CollisionBeginOverlap(CCollider* _pOtherCollider)
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
			SceneChange(SCENE_TYPE::CENTER1F);
		}
	}
}

void CEscalator2f::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CEscalator2f::CollisionEndOverlap(CCollider* _pOtherCollider)
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