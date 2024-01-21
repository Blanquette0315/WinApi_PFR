#include "pch.h"
#include "CRattata.h"

#include "CResourceMgr.h"
#include "CTimeMgr.h"

#include "CImage.h"
#include "CAnimator.h"

#include "CTackle.h"

CRattata::CRattata(UINT _CurLV)
	: m_pImage(nullptr)
	, m_pMiniImage(nullptr)
	, m_eIOType(POKEMON_IO_TYPE::e_NONE)
	, m_fDuration(0.5)
	, m_fFaceTime(0)
	, m_bIOAnim(false)
{
	SetName(L"RATTATA");

	// ���� �־��ֱ�
	SetCurLv(_CurLV);

	// �⺻ ��ü�� �־��ֱ�
	SetBaseStats(30, 56, 35, 72, 25, 35);

	// Ÿ�� �־��ֱ�
	SetPokemonType(POKEMON_TYPE::NORMAL, POKEMON_TYPE::NONE);

	// ��ų �־��ֱ�
	AddSkill(0, new CTackle);

	GetSkill(0)->SetOwnerPokemon(this);

	// �˸��� �̹��� ����ֱ�
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"RattataPlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Rattata");
	}

	// UI Animation �־��ֱ�
	m_pMiniImage = CResourceMgr::CreateMgr()->FindImg(L"RattataUI");
	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"RattataUIAnim", m_pMiniImage, Vec2(0, 0), Vec2(90, 105), Vec2(0, 0), 90.f, 2, 0.2, false);


}

CRattata::~CRattata()
{
}

void CRattata::tick()
{
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"RattataPlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Rattata");
	}

	CPokemon::tick();
}

void CRattata::render(HDC _dc)
{
	// ��Ʋ������ ����� ���� �̹����� UI���� ����� �̹��� 2������ ��Ȳ���� ������ �������ش�.

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
		GetAnimator()->CuntinuePlay(L"RattataUIAnim", true);
	}

	CPokemon::render(_dc);
}