#include "pch.h"
#include "CWaterGun.h"

#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CImage.h"
#include "CSound.h"

#include "CPokemon.h"


CWaterGun::CWaterGun()
	: m_pImage(nullptr)
	, m_pHit(nullptr)
	, m_pOtherImage(nullptr)
	, m_pSoundStart(nullptr)
	, m_pSoundEnd(nullptr)
	, m_AnimationEnd(false)
	, m_fFacetime(0)
	, StartAnimEnd(false)
	, m_bSoundStartON(false)
	, m_bSoundEndON(false)
{
	SetName(L"WATER GUN");
	SetSkillInfo(40, 25, 1, POKEMON_TYPE::WATER, 1, 0);

	m_pSoundStart = CResourceMgr::CreateMgr()->FindSound(L"WaterGunStart");
	m_pSoundEnd = CResourceMgr::CreateMgr()->FindSound(L"WaterGunEnd");
	m_pSoundStart->SetVolume(100);
	m_pSoundEnd->SetVolume(100);

	AddComponent(new CAnimator);
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"WaterGun");
	m_pOtherImage = CResourceMgr::CreateMgr()->FindImg(L"WaterGunOther");
	m_pHit = CResourceMgr::CreateMgr()->FindImg(L"WaterGunHit");
	GetAnimator()->CreateAnimationY(L"WaterGunAni", m_pImage, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(0.f, 0.f), 160.f, 5, 0.1f, false);
	GetAnimator()->CreateAnimationY(L"WaterGunHitAni", m_pHit, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(0.f, 0.f), 160.f, 5, 0.1f, false);
	GetAnimator()->CreateAnimationY(L"WaterGunHitAni1", m_pHit, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(60.f, 30.f), 160.f, 5, 0.12f, false);
	GetAnimator()->CreateAnimationY(L"WaterGunHitAni2", m_pHit, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(-60.f, -60.f), 160.f, 5, 0.14f, false);

	GetAnimator()->AddMultAnim(L"WaterGunHitAni");
	GetAnimator()->AddMultAnim(L"WaterGunHitAni1");
	GetAnimator()->AddMultAnim(L"WaterGunHitAni2");
}

CWaterGun::~CWaterGun()
{
}

void CWaterGun::SkillAct()
{
	CSkill::SkillAct();

	m_AnimationEnd = true;

	StartAnimEnd = false;

	m_bSoundStartON = false;
	m_bSoundEndON = false;

	m_fFacetime = 0;

	if (GetOwnerPokemon()->GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		SetSkillPos(Vec2(520.f, 420.f), Vec2(880.f, 260.f));
	}
	else
	{
		SetSkillPos(Vec2(740.f, 270.f), Vec2(430.f, 465.f));
	}
	m_vNowPos = m_vStartPos;
	m_vDiff = m_vEndPos - m_vStartPos;

	CEventMgr::CreateMgr()->Re_Render(this);
}

void CWaterGun::tick()
{
	if (!m_AnimationEnd)
	{
		GetAnimator()->FindAnimation(L"WaterGunAni")->Reset();
		GetAnimator()->FindAnimation(L"WaterGunHitAni")->Reset();
		GetAnimator()->FindAnimation(L"WaterGunHitAni1")->Reset();
		GetAnimator()->FindAnimation(L"WaterGunHitAni2")->Reset();
	}
	CSkill::tick();
}

void CWaterGun::render(HDC _dc)
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
			if (m_fFacetime < 0.5)
			{
				if (!m_bSoundStartON)
				{
					m_pSoundStart->Play(false);
					m_bSoundStartON = true;
				}

				m_fFacetime += DT;
				float temrtio = (0.5 - m_fFacetime) / 0.5;
				float temrtioPos = m_fFacetime / 0.5;
				Vec2 temMovePos = m_vDiff * temrtioPos;

				AlphaBlend(_dc, m_vNowPos.x - ((80 + (160 * temrtio)) / 2) + temMovePos.x
					, m_vNowPos.y - ((80 + (160 * temrtio)) / 2) + temMovePos.y
					, 80 + (160 * temrtio), 80 + (160 * temrtio)
					, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);
			}
			else
			{
				/*GetAnimator()->CuntinuePlay(L"WaterGunAni", false);
				if (GetAnimator()->FindAnimation(L"WaterGunAni")->IsFinish())
				{
					GetAnimator()->ReSetCurAnim();
					StartAnimEnd = true;
				}*/
				StartAnimEnd = true;
			}
		}
		else
		{
			if (m_fFacetime < 0.5)
			{
				if (!m_bSoundStartON)
				{
					m_pSoundStart->Play(false);
					m_bSoundStartON = true;
				}

				m_fFacetime += DT;
				float temrtio = m_fFacetime / 0.5;
				Vec2 temMovePos = m_vDiff * temrtio;

				AlphaBlend(_dc, m_vNowPos.x - ((80 + (160 * temrtio)) / 2) + temMovePos.x
					, m_vNowPos.y - ((80 + (160 * temrtio)) / 2) + temMovePos.y
					, 80 + (160 * temrtio), 80 + (160 * temrtio)
					, m_pOtherImage->GetDC(), 0, 0, 160, 160, tFunc);
			}
			else
			{
				/*GetAnimator()->CuntinuePlay(L"WaterGunAni", false);
				if (GetAnimator()->FindAnimation(L"WaterGunAni")->IsFinish())
				{
					GetAnimator()->ReSetCurAnim();
					StartAnimEnd = true;
				}*/
				StartAnimEnd = true;
			}
		}
	}
	else
	{
		if (m_AnimationEnd)
		{
			if (!m_bSoundEndON)
			{
				m_pSoundEnd->Play(false);
				m_bSoundEndON = true;
			}

			GetAnimator()->CuntinuePlayMultAnim(false);

			if (GetAnimator()->FindAnimation(L"WaterGunHitAni2")->IsFinish())
			{
				CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
				GetAnimator()->MultOff();
				GetAnimator()->ReSetCurAnim();
				m_AnimationEnd = false;
			}
		}
	}


	CSkill::render(_dc);
}