#include "pch.h"
#include "CCaterpie.h"

#include "CResourceMgr.h"
#include "CTimeMgr.h"

#include "CImage.h"
#include "CAnimator.h"

#include "CTackle.h"

CCaterpie::CCaterpie(UINT _CurLV)
	: m_pImage(nullptr)
	, m_pMiniImage(nullptr)
	, m_eIOType(POKEMON_IO_TYPE::e_NONE)
	, m_fDuration(0.5)
	, m_fFaceTime(0)
	, m_bIOAnim(false)
{
	SetName(L"CATERPIE");

	// 레벨 넣어주기
	SetCurLv(_CurLV);

	// 기본 개체값 넣어주기
	SetBaseStats(45, 30, 35, 45, 20, 20);

	// 타입 넣어주기
	SetPokemonType(POKEMON_TYPE::BUG, POKEMON_TYPE::NONE);

	// 스킬 넣어주기
	AddSkill(0, new CTackle);

	GetSkill(0)->SetOwnerPokemon(this);

	// 알맞은 이미지 골라주기
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"CaterpiePlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Caterpie");
	}

	// UI Animation 넣어주기
	m_pMiniImage = CResourceMgr::CreateMgr()->FindImg(L"CaterpieUI");
	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"CaterpieUIAnim", m_pMiniImage, Vec2(0, 0), Vec2(70, 80), Vec2(0, 0), 70.f, 2, 0.2, false);


}

CCaterpie::~CCaterpie()
{
}

void CCaterpie::tick()
{
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"CaterpiePlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Caterpie");
	}

	CPokemon::tick();
}

void CCaterpie::render(HDC _dc)
{
	// 배틀씬에서 사용할 랜더 이미지와 UI에서 사용할 이미지 2가지의 상황으로 나뉘에 랜더해준다.

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	if (GetPokSceneType() == POKEMONSCENE_TYPE::BATTLE)
	{
		Vec2 vPos = GetPos();
		float ratio = 0;
		m_bIOAnim = true;

		if (m_eIOType == POKEMON_IO_TYPE::e_IN)
		{
			m_fFaceTime += DT;
			ratio = m_fFaceTime / m_fDuration;

			if (m_fFaceTime >= m_fDuration)
			{
				m_eIOType = POKEMON_IO_TYPE::e_NONE;
				m_fFaceTime = 0;
			}
		}
		else if (m_eIOType == POKEMON_IO_TYPE::e_OUT)
		{
			m_fFaceTime += DT;
			ratio = (m_fDuration - m_fFaceTime) / m_fDuration;
			m_bIOAnim = true;
		}
		else if (m_eIOType == POKEMON_IO_TYPE::e_NONE)
		{
			ratio = 1;
		}

		AlphaBlend(_dc, vPos.x - (m_pImage->GetWidth() / 2) * ratio
			, vPos.y - (m_pImage->GetHeight() / 2) * ratio
			, m_pImage->GetWidth() * ratio, m_pImage->GetHeight() * ratio
			, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
	}
	else if (GetPokSceneType() == POKEMONSCENE_TYPE::UI)
	{
		SetPos(GetPos() - Vec2(0, m_pMiniImage->GetHeight() / 2));
		GetAnimator()->CuntinuePlay(L"CaterpieUIAnim", true);
	}

	CPokemon::render(_dc);
}