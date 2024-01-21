#include "pch.h"
#include "CScratch.h"

#include "CResourceMgr.h"
#include "CEventMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CImage.h"
#include "CSound.h"


CScratch::CScratch()
	: m_pImage(nullptr)
	, m_pSound(nullptr)
	, m_AnimationEnd(false)
	, m_bSoundON(false)
{
	SetName(L"SCRATCH");
	SetSkillInfo(40, 35, 1, POKEMON_TYPE::NORMAL, 0, 0);

	AddComponent(new CAnimator);
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Scratch");
	GetAnimator()->CreateAnimationY(L"ScratchAni", m_pImage, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(0.f, 0.f), 160.f, 5, 0.1f, false);

	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"HIT");
	m_pSound->SetVolume(100);
}

CScratch::~CScratch()
{
}

void CScratch::SkillAct()
{
	CSkill::SkillAct();
	//SetPos(Vec2(880.f, 270.f));
	CEventMgr::CreateMgr()->Re_Render(this);
	m_AnimationEnd = true;
	m_bSoundON = false;
}

void CScratch::tick()
{
	if (!m_AnimationEnd)
	{
		GetAnimator()->FindAnimation(L"ScratchAni")->Reset();
	}
	CSkill::tick();
}

void CScratch::render(HDC _dc)
{
	if (m_AnimationEnd)
	{
		if (!m_bSoundON)
		{
			m_pSound->Play(false);
			m_bSoundON = true;
		}

 		GetAnimator()->CuntinuePlay(L"ScratchAni", false);
		if (GetAnimator()->FindAnimation(L"ScratchAni")->IsFinish())
		{
			CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
			m_AnimationEnd = false;
		}
	}
	CSkill::render(_dc);
}
