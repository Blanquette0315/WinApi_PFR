#include "pch.h"
#include "CVinewhip.h"

#include "CResourceMgr.h"
#include "CEventMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CImage.h"


CVinewhip::CVinewhip()
	: m_pImage(nullptr)
	, m_pImage2(nullptr)
	, m_AnimationEnd(true)
{
	SetName(L"VINE WHIP");
	SetSkillInfo(45, 25, 1, POKEMON_TYPE::GRASS, 0, 0);

	AddComponent(new CAnimator);
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Vinewhip2");
	m_pImage2 = CResourceMgr::CreateMgr()->FindImg(L"Vinewhip");
	GetAnimator()->CreateAnimationY(L"Vinewhip2Ani", m_pImage, Vec2(0.f, 0.f), Vec2(280.f, 140.f), Vec2(0.f, 0.f), 140.f, 4, 0.1f, false);
	GetAnimator()->CreateAnimationY(L"VinewhipAni", m_pImage2, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(-20.f, 0.f), 160.f, 5, 0.1f, false);
	GetAnimator()->CreateAnimationY(L"VinewhipAni3", m_pImage2, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(100.f, 0.f), 160.f, 5, 0.1f, false);

	GetAnimator()->AddMultAnim(L"VinewhipAni");
	GetAnimator()->AddMultAnim(L"VinewhipAni3");
}

CVinewhip::~CVinewhip()
{
}

void CVinewhip::SkillAct()
{
	CSkill::SkillAct();
	//SetPos(Vec2(880.f, 270.f));
	CEventMgr::CreateMgr()->Re_Render(this);
	m_AnimationEnd = true;
}

void CVinewhip::tick()
{
	if (!m_AnimationEnd)
	{
		GetAnimator()->FindAnimation(L"VinewhipAni")->Reset();
		GetAnimator()->FindAnimation(L"Vinewhip2Ani")->Reset();
		GetAnimator()->FindAnimation(L"VinewhipAni3")->Reset();
	}
	CSkill::tick();
}

void CVinewhip::render(HDC _dc)
{
	if (m_AnimationEnd)
	{
		GetAnimator()->CuntinuePlayMultAnim(false);

		if (GetAnimator()->FindAnimation(L"VinewhipAni")->IsFinish())
		{
			GetAnimator()->MultOff();
			GetAnimator()->CuntinuePlay(L"Vinewhip2Ani", false);

			if (GetAnimator()->FindAnimation(L"Vinewhip2Ani")->IsFinish())
			{
				CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
				GetAnimator()->ReSetCurAnim();
				m_AnimationEnd = false;
			}
		}
	}
	CSkill::render(_dc);
}
