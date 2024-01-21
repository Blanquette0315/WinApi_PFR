#include "pch.h"
#include "CPidgey.h"

#include "CResourceMgr.h"
#include "CTimeMgr.h"

#include "CImage.h"
#include "CAnimator.h"

#include "CTackle.h"
#include "CGust.h"

CPidgey::CPidgey(UINT _CurLV)
	: m_pImage(nullptr)
	, m_pMiniImage(nullptr)
	, m_eIOType(POKEMON_IO_TYPE::e_NONE)
	, m_fDuration(0.5)
	, m_fFaceTime(0)
	, m_bIOAnim(false)
{
	SetName(L"PIDGEY");

	// ���� �־��ֱ�
	SetCurLv(_CurLV);

	// �⺻ ��ü�� �־��ֱ�
	SetBaseStats(40, 45, 40, 56, 35, 35);

	// Ÿ�� �־��ֱ�
	SetPokemonType(POKEMON_TYPE::NORMAL, POKEMON_TYPE::FLVING);

	// ��ų �־��ֱ�
	AddSkill(0, new CTackle);
	GetSkill(0)->SetOwnerPokemon(this);


	 AddSkill(1, new CGust);
	 GetSkill(1)->SetOwnerPokemon(this);


	// �˸��� �̹��� ����ֱ�
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"PidgevPlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Pidgev");
	}

	// UI Animation �־��ֱ�
	m_pMiniImage = CResourceMgr::CreateMgr()->FindImg(L"PidgevUI");
	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"PidgevUIAnim", m_pMiniImage, Vec2(0, 0), Vec2(95, 85), Vec2(0, 0), 95.f, 2, 0.2, false);


}

CPidgey::~CPidgey()
{
}

void CPidgey::tick()
{
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"PidgevPlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Pidgev");
	}

	CPokemon::tick();
}

void CPidgey::render(HDC _dc)
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
		GetAnimator()->CuntinuePlay(L"PidgevUIAnim", true);
	}

	CPokemon::render(_dc);
}