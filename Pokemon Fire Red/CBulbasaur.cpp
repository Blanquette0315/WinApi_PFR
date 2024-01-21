#include "pch.h"
#include "CBulbasaur.h"

#include "CResourceMgr.h"
#include "CTimeMgr.h"

#include "CImage.h"
#include "CAnimator.h"

#include "CTackle.h"
#include "CVinewhip.h"

CBulbasaur::CBulbasaur(UINT _CurLV)
	: m_pImage(nullptr)
	, m_pMiniImage(nullptr)
	, m_eIOType(POKEMON_IO_TYPE::e_NONE)
	, m_fDuration(0.5)
	, m_fFaceTime(0)
	, m_bIOAnim(false)
{
	SetName(L"BULBASAUR");

	// 레벨 넣어주기
	SetCurLv(_CurLV);

	// 기본 개체값 넣어주기
	SetBaseStats(45, 49, 49, 45, 65, 65);

	// 타입 넣어주기
	SetPokemonType(POKEMON_TYPE::GRASS, POKEMON_TYPE::POISON);

	// 스킬 넣어주기
	AddSkill(0, new CTackle);
	AddSkill(1, new CVinewhip);

	GetSkill(0)->SetOwnerPokemon(this);
	GetSkill(1)->SetOwnerPokemon(this);

	// 알맞은 이미지 골라주기
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BulbasaurPlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Bulbasaur");
	}

	// UI Animation 넣어주기
	m_pMiniImage = CResourceMgr::CreateMgr()->FindImg(L"BulbasaurUI");
	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"BulbasaurUIAnim", m_pMiniImage, Vec2(0, 0), Vec2(100, 85), Vec2(0, 0), 100.f, 2, 0.2, false);


}

CBulbasaur::~CBulbasaur()
{
}

void CBulbasaur::tick()
{
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BulbasaurPlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Bulbasaur");
	}

	CPokemon::tick();
}

void CBulbasaur::render(HDC _dc)
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

		if (m_eIOType == POKEMON_IO_TYPE::e_IN)
		{
			m_bIOAnim = true;
			m_fFaceTime += DT;
			ratio = m_fFaceTime / m_fDuration;

			if (m_fFaceTime >= m_fDuration)
			{
				//m_eIOType = POKEMON_IO_TYPE::e_NONE;
				m_fFaceTime = 0.5;
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
			m_bIOAnim = false;
			m_fFaceTime = 0;
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
		GetAnimator()->CuntinuePlay(L"BulbasaurUIAnim", true);
	}

	CPokemon::render(_dc);
}

/*void CCharmander::ISEvolution()
{
	// 레벨이 16이면 리자드로 진화
	if (16 == GetCurLV())
	{
		// 진화 이밴트 넣어주기
		// 진화 이밴트 진행시 진화하는 Scene이 나오고, UI가 흐름에 맞게 나온다.
		// 진화 후에는 객체가 가지고 있는 이미지가 진화한 이미지로 알맞게 바뀐다.
		// 이름도 바뀐다.
		// 이후 진화에 맞는 개체값을 넣어주는 함수를 추가해 스탯을 재정리 해준다.

	}
	// 레벨이 36이면 리자몽으로 진화한다.
	else if (36 == GetCurLV())
	{

	}
}*/