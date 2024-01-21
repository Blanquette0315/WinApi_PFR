#include "pch.h"
#include "CRockTomb.h"

#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CImage.h"
#include "CSound.h"


CRockTomb::CRockTomb()
	: m_pImage(nullptr)
	, m_pxImage(nullptr)
	, m_pRockSound(nullptr)
	, m_pRockbgm(nullptr)
	, m_AnimationEnd(false)
	, m_Rock1time(0)
	, m_Rock2time(0)
	, m_Rock3time(0)
	, m_xtime(0)
	, m_Rock2Start(false)
	, m_Rock3Start(false)
	, m_XStart(false)
	, m_bRockSoundON1(false)
	, m_bRockSoundON3(false)
	, m_bRockSoundON2(false)
	, m_bRockbgmOn(false)
{
	SetName(L"ROCK TOMB");
	SetSkillInfo(60, 15, 1, POKEMON_TYPE::ROCK, 0, 0);

	m_pRockSound = CResourceMgr::CreateMgr()->FindSound(L"RockFoll");
	m_pRockbgm = CResourceMgr::CreateMgr()->FindSound(L"RockFollbgm");

	m_pRockSound->SetVolume(100);
	m_pRockbgm->SetVolume(80);

	AddComponent(new CAnimator);
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"RockTomb");
	m_pxImage = CResourceMgr::CreateMgr()->FindImg(L"X");
}

CRockTomb::~CRockTomb()
{
}

void CRockTomb::SkillAct()
{
	CSkill::SkillAct();
	CEventMgr::CreateMgr()->Re_Render(this);
	m_AnimationEnd = true;

	OriPos = GetPos();

	Rock1Pos = OriPos;
	Rock1Pos.y -= 260;

	Rock2Pos = OriPos;
	Rock2Pos.x -= 80;
	Rock2Pos.y -= 260;

	Rock3Pos = OriPos;
	Rock3Pos.x += 80;
	Rock3Pos.y -= 260;

	m_Rock1time = 0;
	m_Rock2time = 0;
	m_Rock3time = 0;
	m_xtime = 0;

	m_Rock2Start = false;
	m_Rock3Start = false;
	m_XStart = false;

	m_bRockSoundON1 = false;
	m_bRockSoundON2 = false;
	m_bRockSoundON3 = false;
	m_bRockbgmOn = false;
}

void CRockTomb::tick()
{
	CSkill::tick();
}

void CRockTomb::render(HDC _dc)
{
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	if (m_AnimationEnd)
	{
		// 2번째 바위
		if (m_Rock2Start)
		{
			Vec2 TemRock2Pos = Rock2Pos;

			if (m_Rock2time < 0.25)
			{
				m_Rock2time += DT;
				TemRock2Pos.y += (203 * (m_Rock2time / 0.25));

				AlphaBlend(_dc, TemRock2Pos.x - 80
					, TemRock2Pos.y
					, 160, 160
					, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);
			}
			else
			{
				if (!m_bRockSoundON2)
				{
					m_pRockSound->Play(false);
					m_bRockSoundON2 = true;
				}

				TemRock2Pos.y += 203;

				AlphaBlend(_dc, TemRock2Pos.x - 80
					, TemRock2Pos.y
					, 160, 160
					, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);
			}
		}

		if (m_Rock1time >= 0.125)
		{
			m_Rock2Start = true;
		}

		// 3번째 바위
		if (m_Rock3Start)
		{
			Vec2 TemRock3Pos = Rock3Pos;

			if (m_Rock3time < 0.25)
			{
				m_Rock3time += DT;
				TemRock3Pos.y += (203 * (m_Rock3time / 0.25));

				AlphaBlend(_dc, TemRock3Pos.x - 80
					, TemRock3Pos.y
					, 160, 160
					, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);
			}
			else
			{
				if (!m_bRockSoundON3)
				{
					m_pRockSound->Play(false);
					m_bRockSoundON3 = true;
				}

				TemRock3Pos.y += 203;

				AlphaBlend(_dc, TemRock3Pos.x - 80
					, TemRock3Pos.y
					, 160, 160
					, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);

					m_XStart = true;
			}
		}

		if (m_Rock2time >= 0.125)
		{
			m_Rock3Start = true;
		}

		// 1번째 바위
		Vec2 TemRock1Pos = Rock1Pos;

		if (m_Rock1time < 0.25)
		{
			if (!m_bRockbgmOn)
			{
				m_pRockbgm->Play(false);
				m_bRockbgmOn = true;
			}

			m_Rock1time += DT;
			TemRock1Pos.y += (203 * (m_Rock1time / 0.25));

			AlphaBlend(_dc, TemRock1Pos.x - 80
				, TemRock1Pos.y
				, 160, 160
				, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);
		}
		else
		{
			if (!m_bRockSoundON1)
			{
				m_pRockSound->Play(false);
				m_bRockSoundON1 = true;
			}
			TemRock1Pos.y += 203;

			AlphaBlend(_dc, TemRock1Pos.x - 80
				, TemRock1Pos.y
				, 160, 160
				, m_pImage->GetDC(), 0, 0, 160, 160, tFunc);
		}

		if (m_XStart)
		{
			m_xtime += DT;

			AlphaBlend(_dc, OriPos.x - 160
				, OriPos.y - 160
				, 320, 320
				, m_pxImage->GetDC(), 0, 0, 320, 320, tFunc);

			if (m_xtime >= 0.25)
			{
				m_pRockbgm->Stop();
				m_AnimationEnd = false;
				CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
			}
		}
	}

	CSkill::render(_dc);
}
