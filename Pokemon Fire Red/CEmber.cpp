#include "pch.h"
#include "CEmber.h"


#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CImage.h"
#include "CSound.h"

#include "CPokemon.h"


CEmber::CEmber()
	: m_pImage(nullptr)
	, m_pStartSound(nullptr)
	, m_pEndSound(nullptr)
	, m_AnimationEnd(false)
	, m_fFacetime(0)
	, StartAnimEnd(false)
	, m_bStartSoundON(false)
	, m_bEndSoundON(false)
{
	SetName(L"EMBER");
	SetSkillInfo(40, 25, 1, POKEMON_TYPE::FIRE, 1, 0);

	AddComponent(new CAnimator);
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Ember");
	GetAnimator()->CreateAnimationY(L"EmberAni", m_pImage, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(0.f, 0.f), 160.f, 5, 0.1f, false);
	GetAnimator()->CreateAnimationY(L"EmberAni1", m_pImage, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(60.f, 20.f), 160.f, 5, 0.12f, false);
	GetAnimator()->CreateAnimationY(L"EmberAni2", m_pImage, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(-60.f, 20.f), 160.f, 5, 0.14f, false);

	GetAnimator()->AddMultAnim(L"EmberAni");
	GetAnimator()->AddMultAnim(L"EmberAni1");
	GetAnimator()->AddMultAnim(L"EmberAni2");

	m_pStartSound = CResourceMgr::CreateMgr()->FindSound(L"EmberStart");
	m_pEndSound = CResourceMgr::CreateMgr()->FindSound(L"EmberEnd");
	m_pStartSound->SetVolume(100);
	m_pEndSound->SetVolume(100);
}

CEmber::~CEmber()
{
}

void CEmber::SkillAct()
{
	CSkill::SkillAct();
	
	m_AnimationEnd = true;

	StartAnimEnd = false;

	m_bStartSoundON = false;
	m_bEndSoundON = false;

	m_fFacetime = 0;

	if (GetOwnerPokemon()->GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		SetSkillPos(Vec2(520.f, 420.f), Vec2(880.f, 230.f));
	}
	else
	{
		SetSkillPos(Vec2(740.f, 270.f), Vec2(360.f, 435.f));
	}
	m_vNowPos = m_vStartPos;
	m_vDiff = m_vEndPos - m_vStartPos;

	CEventMgr::CreateMgr()->Re_Render(this);
}

void CEmber::tick()
{
	if (!m_AnimationEnd)
	{
		GetAnimator()->FindAnimation(L"EmberAni")->Reset();
		GetAnimator()->FindAnimation(L"EmberAni1")->Reset();
		GetAnimator()->FindAnimation(L"EmberAni2")->Reset();
	}
	CSkill::tick();
}

void CEmber::render(HDC _dc)
{
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	if (!StartAnimEnd)
	{
		if (GetOwnerPokemon()->GetOwnerType() == OWNER_TYPE::PLAYER)
		{
			if (!m_bStartSoundON)
			{
				m_pStartSound->Play(false);
				m_bStartSoundON = true;
			}

			if (m_fFacetime < 0.5)
			{
				m_fFacetime += DT;
				float temrtio = (0.5 - m_fFacetime) / 0.5;
				float temrtioPos = m_fFacetime / 0.5;
				Vec2 temMovePos = m_vDiff * temrtioPos;

				AlphaBlend(_dc, m_vNowPos.x - ((160 + (480 * temrtio)) / 2) + temMovePos.x
					, m_vNowPos.y - ((160 + (480 * temrtio)) / 2) + temMovePos.y
					, 160 + (480 * temrtio), 160 + (480 * temrtio)
					, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);
			}
			else
			{
				StartAnimEnd = true;
			}
		}
		else
		{
			if (!m_bStartSoundON)
			{
				m_pStartSound->Play(false);
				m_bStartSoundON = true;
			}

			if (m_fFacetime < 0.5)
			{
				m_fFacetime += DT;
				float temrtio = m_fFacetime / 0.5;
				Vec2 temMovePos = m_vDiff * temrtio;

				AlphaBlend(_dc, m_vNowPos.x - ((160 + (480 * temrtio)) / 2) + temMovePos.x
					, m_vNowPos.y - ((160 + (480 * temrtio)) / 2) + temMovePos.y
					, 160 + (480 * temrtio), 160 + (480 * temrtio)
					, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);
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
			if (!m_bEndSoundON)
			{
				m_pEndSound->Play(false);
				m_bEndSoundON = true;
			}

			// GetAnimator()->CuntinuePlay(L"EmberAni", false);

			GetAnimator()->CuntinuePlayMultAnim(false);

			if (GetAnimator()->FindAnimation(L"EmberAni1")->IsFinish())
			{
				CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
				GetAnimator()->MultOff();
				m_AnimationEnd = false;
			}
		}
	}


	CSkill::render(_dc);
}
