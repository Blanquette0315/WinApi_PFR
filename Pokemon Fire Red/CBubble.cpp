#include "pch.h"
#include "CBubble.h"

#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CImage.h"
#include "CSound.h"

#include "CPokemon.h"


CBubble::CBubble()
	: m_pImage(nullptr)
	, m_pStartSound(nullptr)
	, m_pEndSound(nullptr)
	, m_AnimationEnd(false)
	, m_fFacetime(0)
	, StartAnimEnd(false)
	, m_pStartSoundON(false)
	, m_pEndSoundON(false)
{
	SetName(L"BUBBLE");
	SetSkillInfo(40, 30, 1, POKEMON_TYPE::WATER, 1, 0);

	m_pStartSound = CResourceMgr::CreateMgr()->FindSound(L"BubbleStart");
	m_pEndSound = CResourceMgr::CreateMgr()->FindSound(L"BubbleEnd");
	m_pStartSound->SetVolume(100);
	m_pEndSound->SetVolume(100);

	AddComponent(new CAnimator);
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Bubble");
	GetAnimator()->CreateAnimationY(L"BubbleAni", m_pImage, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), 80.f, 3, 0.1f, false);
	GetAnimator()->CreateAnimationY(L"BubbleAni1", m_pImage, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(60.f, 20.f), 80.f, 3, 0.12f, false);
	GetAnimator()->CreateAnimationY(L"BubbleAni2", m_pImage, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(-60.f, -60.f), 80.f, 3, 0.14f, false);

	GetAnimator()->AddMultAnim(L"BubbleAni");
	GetAnimator()->AddMultAnim(L"BubbleAni1");
	GetAnimator()->AddMultAnim(L"BubbleAni2");
}

CBubble::~CBubble()
{
}

void CBubble::SkillAct()
{
	CSkill::SkillAct();

	m_AnimationEnd = true;

	StartAnimEnd = false;
	m_fFacetime = 0;

	m_pStartSoundON = false;
	m_pEndSoundON = false;

	if (GetOwnerPokemon()->GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		SetSkillPos(Vec2(520.f, 460.f), Vec2(860.f, 230.f));
	}
	else
	{
		SetSkillPos(Vec2(840.f, 310.f), Vec2(320.f, 435.f));
	}

	m_vNowPos = m_vStartPos;
	m_vDiff = m_vEndPos - m_vStartPos;

	CEventMgr::CreateMgr()->Re_Render(this);
}

void CBubble::tick()
{
	if (!m_AnimationEnd)
	{
		GetAnimator()->FindAnimation(L"BubbleAni")->Reset();
		GetAnimator()->FindAnimation(L"BubbleAni1")->Reset();
		GetAnimator()->FindAnimation(L"BubbleAni2")->Reset();
	}
	CSkill::tick();
}

void CBubble::render(HDC _dc)
{

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	if (!StartAnimEnd)
	{
		// 기술 사용음
		if (!m_pStartSoundON)
		{
			m_pStartSound->Play(false);
			m_pStartSoundON = true;
		}

		if (GetOwnerPokemon()->GetOwnerType() == OWNER_TYPE::PLAYER)
		{
			if (m_fFacetime < 1.0)
			{
				m_fFacetime += DT;
				float temrtio = (1.0 - m_fFacetime) / 1.0;
				float temrtioPos = m_fFacetime / 1.0;
				Vec2 temMovePos = m_vDiff * temrtioPos;

				float fUpTime = 0;
				
				if (fUpTime >= 0.125)
				{
					fUpTime = 0;
				}
				else
				{
					fUpTime += DT;
				}
				float temUPrtio = 20 * (fUpTime / 0.125);

				// 위 아래로 흔들기
				if (temrtioPos < 0.125)
				{
					m_vNowPos.y += temUPrtio;
				}
				else if ((0.125 <= temrtioPos) && (temrtioPos < 0.25))
				{
					m_vNowPos.y -= temUPrtio;
				}
				else if ((0.25 <= temrtioPos) && (temrtioPos < 0.375))
				{
					m_vNowPos.y -= temUPrtio;
				}
				else if ((0.375 <= temrtioPos) && (temrtioPos < 0.5))
				{
					m_vNowPos.y += temUPrtio;
				}
				else if ((0.5 <= temrtioPos) && (temrtioPos < 0.625))
				{
					m_vNowPos.y += temUPrtio;
				}
				else if ((0.625 <= temrtioPos) && (temrtioPos < 0.75))
				{
					m_vNowPos.y -= temUPrtio;
				}
				else if ((0.75 <= temrtioPos) && (temrtioPos < 0.875))
				{
					m_vNowPos.y -= temUPrtio;
				}
				else if ((0.875 <= temrtioPos) && (temrtioPos < 1.0))
				{
					m_vNowPos.y += temUPrtio;
				}

				AlphaBlend(_dc, m_vNowPos.x - ((120 * temrtio) / 2) + temMovePos.x
					, m_vNowPos.y - ((120 * temrtio) / 2) + temMovePos.y
					, 40 + (80 * temrtio), 40 + (80 * temrtio)
					, m_pImage->GetDC(), 0, 0, 80, 80, tFunc);
			}
			else
			{
				StartAnimEnd = true;
			}
		}
		else
		{
			if (m_fFacetime < 1.0)
			{
				m_fFacetime += DT;
				float temrtio = (1.0 - m_fFacetime) / 1.0;
				float temrtioPos = m_fFacetime / 1.0;
				Vec2 temMovePos = m_vDiff * temrtioPos;

				float fUpTime = 0;

				if (fUpTime >= 0.125)
				{
					fUpTime = 0;
				}
				else
				{
					fUpTime += DT;
				}
				float temUPrtio = 20 * (fUpTime / 0.125);

				// 위 아래로 흔들기
				if (temrtioPos < 0.125)
				{
					m_vNowPos.y += temUPrtio;
				}
				else if ((0.125 <= temrtioPos) && (temrtioPos < 0.25))
				{
					m_vNowPos.y -= temUPrtio;
				}
				else if ((0.25 <= temrtioPos) && (temrtioPos < 0.375))
				{
					m_vNowPos.y -= temUPrtio;
				}
				else if ((0.375 <= temrtioPos) && (temrtioPos < 0.5))
				{
					m_vNowPos.y += temUPrtio;
				}
				else if ((0.5 <= temrtioPos) && (temrtioPos < 0.625))
				{
					m_vNowPos.y += temUPrtio;
				}
				else if ((0.625 <= temrtioPos) && (temrtioPos < 0.75))
				{
					m_vNowPos.y -= temUPrtio;
				}
				else if ((0.75 <= temrtioPos) && (temrtioPos < 0.875))
				{
					m_vNowPos.y -= temUPrtio;
				}
				else if ((0.875 <= temrtioPos) && (temrtioPos < 1.0))
				{
					m_vNowPos.y += temUPrtio;
				}

				AlphaBlend(_dc, m_vNowPos.x - ((120 * temrtio) / 2) + temMovePos.x
					, m_vNowPos.y - ((120 * temrtio) / 2) + temMovePos.y
					, 120 - (80 * temrtio), 120 - (80 * temrtio)
					, m_pImage->GetDC(), 0, 0, 80, 80, tFunc);
			}
			else
			{
				StartAnimEnd = true;
			}
		}

	}
	else
	{
		if (m_AnimationEnd)
		{
			// GetAnimator()->CuntinuePlay(L"EmberAni", false);

			// 기술 사용음
			if (!m_pEndSoundON)
			{
				m_pEndSound->Play(false);
				m_pEndSoundON = true;
			}

			GetAnimator()->CuntinuePlayMultAnim(false);

			if (GetAnimator()->FindAnimation(L"BubbleAni1")->IsFinish())
			{
				CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
				GetAnimator()->MultOff();
				m_AnimationEnd = false;
			}
		}
	}


	CSkill::render(_dc);
}
