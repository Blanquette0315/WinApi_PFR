#include "pch.h"
#include "CFlower.h"

#include "CResourceMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CImage.h"
#include "CPlayer.h"

CFlower::CFlower()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Flower");

	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"FlowerAnimation", m_pImage, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(0.f, 0.f), 64.f, 5, 0.2f);

	GetAnimator()->Play(L"FlowerAnimation", true);

	AddCollider(L"Image\\map\\Environment\\Flower.Collider");

}

CFlower::~CFlower()
{
	CEnvironment::~CEnvironment();
}


void CFlower::tick()
{
	CEnvironment::tick();
}

void CFlower::render(HDC _dc)
{
	if (IS_Collision)
	{
		GetAnimator()->CuntinuePlay(L"FlowerAnimation", true);
		IS_Collision = false;
	}

	CEnvironment::render(_dc);
}


void CFlower::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())
		&& (0 == m_iRe_render))
	{
		m_iRe_render++;
		IS_Collision = true;
		CEventMgr::CreateMgr()->Re_Render(this);
	}
}

void CFlower::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CFlower::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())
		&& (1 == m_iRe_render))
	{
		m_iRe_render = 0;
		IS_Collision = false;
		CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
	}
}