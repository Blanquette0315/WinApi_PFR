#include "pch.h"
#include "CGust.h"

#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CImage.h"
#include "CSound.h"


CGust::CGust()
	: m_pImage(nullptr)
	, m_pWindSound(nullptr)
	, m_AnimationEnd(false)
	, m_fFacetime(0)
{
	SetName(L"GUST");
	SetSkillInfo(40, 35, 1, POKEMON_TYPE::FLVING, 1, 0);

	AddComponent(new CAnimator);
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Gust");
	GetAnimator()->CreateAnimationY(L"GustAni", m_pImage, Vec2(0.f, 0.f), Vec2(160.f, 320.f), Vec2(0.f, 0.f), 160.f, 3, 0.1f, false);

	m_pWindSound = CResourceMgr::CreateMgr()->FindSound(L"Gust3");
	m_pWindSound->SetVolume(100);
}

CGust::~CGust()
{
}

void CGust::SkillAct()
{
	CSkill::SkillAct();
	CEventMgr::CreateMgr()->Re_Render(this);
	m_AnimationEnd = true;
	OriPos = GetPos();
	EndPos1.x = OriPos.x - 130;
	EndPos1.y = OriPos.y;
	EndPos2.x = OriPos.x + 130;
	EndPos2.y = OriPos.y;
	m_fFacetime = 0;

	m_pSoundON = false;
}

void CGust::tick()
{
	if (!m_AnimationEnd)
	{
		GetAnimator()->FindAnimation(L"GustAni")->Reset();
		m_fFacetime = 0;
	}
	CSkill::tick();
}

void CGust::render(HDC _dc)
{
	if (m_AnimationEnd)
	{
		if (!m_pSoundON)
		{
			m_pWindSound->Play(false);
			m_pSoundON = true;
		}

		GetAnimator()->CuntinuePlay(L"GustAni", true);
		m_fFacetime += DT;

		if (m_fFacetime < 0.125)
		{
			Vec2 TemPos = OriPos;

			TemPos.x -= (130 * (m_fFacetime / 0.125));
			SetPos(TemPos);
		}
		else if ((m_fFacetime >= 0.125) && (m_fFacetime < 0.25))
		{
			Vec2 TemPos = EndPos1;

			TemPos.x += (130 * ((m_fFacetime - 0.125) / 0.125));
			SetPos(TemPos);
		}
		else if ((m_fFacetime >= 0.25) && (m_fFacetime < 0.375))
		{
			Vec2 TemPos = OriPos;

			TemPos.x += (130 * ((m_fFacetime - 0.25) / 0.125));
			SetPos(TemPos);
		}
		else if ((m_fFacetime >= 0.375) && (m_fFacetime < 0.5))
		{
			Vec2 TemPos = EndPos2;

			TemPos.x -= (130 * ((m_fFacetime - 0.375) / 0.125));
			SetPos(TemPos);
		}

		else if ((m_fFacetime >= 0.5) && (m_fFacetime < 0.625))
		{
			Vec2 TemPos = OriPos;

			TemPos.x -= (130 * ((m_fFacetime - 0.5) / 0.125));
			SetPos(TemPos);
		}
		else if ((m_fFacetime >= 0.625) && (m_fFacetime < 0.75))
		{
			Vec2 TemPos = EndPos1;

			TemPos.x += (130 * ((m_fFacetime - 0.625) / 0.125));
			SetPos(TemPos);
		}
		else if ((m_fFacetime >= 0.75) && (m_fFacetime < 0.875))
		{
			Vec2 TemPos = OriPos;

			TemPos.x += (130 * ((m_fFacetime - 0.75) / 0.125));
			SetPos(TemPos);
		}
		else if ((m_fFacetime >= 0.875) && (m_fFacetime < 1.0))
		{
			Vec2 TemPos = EndPos2;

			TemPos.x -= (130 * ((m_fFacetime - 0.875) / 0.125));
			SetPos(TemPos);
		}
		else if (m_fFacetime >= 1.0)
		{
			SetPos(OriPos);
			GetAnimator()->CuntinuePlay(L"GustAni", false);
			if (GetAnimator()->FindAnimation(L"GustAni")->IsFinish())
			{
				if (m_pSoundON)
				{
					m_pWindSound->Stop();
				}

				CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
				GetAnimator()->ReSetCurAnim();
				m_AnimationEnd = false;
			}
		}
	}
	CSkill::render(_dc);
}
