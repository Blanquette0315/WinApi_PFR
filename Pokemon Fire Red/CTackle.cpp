#include "pch.h"
#include "CTackle.h"

#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CImage.h"
#include "CSound.h"

#include "CPokemon.h"


CTackle::CTackle()
	: m_pImage(nullptr)
	, m_pSound(nullptr)
	, m_AnimationEnd(false)
	, m_PosEnd(false)
	, m_bSoundON(false)
	, m_facetime(0)
{
	SetName(L"TACKLE");
	SetSkillInfo(40, 35, 1, POKEMON_TYPE::NORMAL, 0, 0);

	AddComponent(new CAnimator);
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Tackle");
	GetAnimator()->CreateAnimationY(L"TackleAni", m_pImage, Vec2(0.f, 0.f), Vec2(160.f, 160.f), Vec2(0.f, 0.f), 160.f, 5, 0.1f, false);

	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"HIT");
	m_pSound->SetVolume(100);
}

CTackle::~CTackle()
{
}

void CTackle::SkillAct()
{
	CSkill::SkillAct();
	//SetPos(Vec2(880.f, 270.f));
	CEventMgr::CreateMgr()->Re_Render(this);
	m_AnimationEnd = true;
	OrigPos = GetOwnerPokemon()->GetPos();
	EndPos.x = OrigPos.x + 100;
	EndPos.y = OrigPos.y;
	ElseEndPos.x = OrigPos.x - 100;
	ElseEndPos.y  = OrigPos.y;

	m_bSoundON = false;
}

void CTackle::tick()
{
	if (!m_AnimationEnd)
	{
		GetAnimator()->FindAnimation(L"TackleAni")->Reset();
		m_facetime = 0;
	}
	CSkill::tick();
}

void CTackle::render(HDC _dc)
{
	m_facetime += DT;
	if (GetOwnerPokemon()->GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		if (m_facetime <= 0.25)
		{
			Vec2 PokePos = OrigPos;

			PokePos.x += (100 * (m_facetime / 0.25));
			GetOwnerPokemon()->SetPos(PokePos);
		}
		else if ((m_facetime > 0.25) && (m_facetime <= 0.5))
		{
			Vec2 PokePos = EndPos;

			PokePos.x -= (100 * ((m_facetime - 0.25) / 0.25));
			GetOwnerPokemon()->SetPos(PokePos);
		}
		else if (m_facetime >= 0.5)
		{
			m_PosEnd = true;
			GetOwnerPokemon()->SetPos(OrigPos);
		}
		
	}
	else if (!(GetOwnerPokemon()->GetOwnerType() == OWNER_TYPE::PLAYER))
	{
		if (m_facetime < 0.25)
		{
			Vec2 PokePos = OrigPos;

			PokePos.x -= (100 * (m_facetime / 0.25));
			GetOwnerPokemon()->SetPos(PokePos);
		}
		else if ((m_facetime >= 0.25) && (m_facetime < 0.5))
		{
			Vec2 PokePos = ElseEndPos;

			PokePos.x += (100 * ((m_facetime - 0.25) / 0.25));
			GetOwnerPokemon()->SetPos(PokePos);
		}
		else if (m_facetime >= 0.5)
		{
			m_PosEnd = true;
			GetOwnerPokemon()->SetPos(OrigPos);
		}
	}
	
	if (m_PosEnd)
	{
		if (!m_bSoundON)
		{
			m_pSound->Play(false);
			m_bSoundON = true;
		}

		GetAnimator()->CuntinuePlay(L"TackleAni", false);
		if (GetAnimator()->FindAnimation(L"TackleAni")->IsFinish())
		{
			CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
			GetAnimator()->ReSetCurAnim();
			m_AnimationEnd = false;
			m_PosEnd = false;
		}
	}
	CSkill::render(_dc);
}
