#include "pch.h"
#include "CSquirtle.h"

#include "CResourceMgr.h"
#include "CTimeMgr.h"

#include "CImage.h"
#include "CAnimator.h"

#include "CTackle.h"
#include "CBubble.h"
#include "CWaterGun.h"

CSquirtle::CSquirtle(UINT _CurLV)
	: m_pImage(nullptr)
	, m_pMiniImage(nullptr)
	, m_eIOType(POKEMON_IO_TYPE::e_NONE)
	, m_fDuration(0.5)
	, m_fFaceTime(0)
	, m_bIOAnim(false)
{
	SetName(L"SQUIRTLE");

	// ���� �־��ֱ�
	SetCurLv(_CurLV);

	// �⺻ ��ü�� �־��ֱ�
	SetBaseStats(44, 48, 65, 43, 50, 64);

	// Ÿ�� �־��ֱ�
	SetPokemonType(POKEMON_TYPE::WATER, POKEMON_TYPE::NONE);

	// ��ų �־��ֱ�
	AddSkill(0, new CTackle);
	AddSkill(1, new CBubble);

	GetSkill(0)->SetOwnerPokemon(this);
	GetSkill(1)->SetOwnerPokemon(this);

	if (_CurLV >= 5)
	{
		AddSkill(2, new CWaterGun);
		GetSkill(2)->SetOwnerPokemon(this);
	}

	// �˸��� �̹��� ����ֱ�
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"SquirtlePlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Squirtle");
	}

	// UI Animation �־��ֱ�
	m_pMiniImage = CResourceMgr::CreateMgr()->FindImg(L"SquirtleUI");
	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"SquirtleUIAnim", m_pMiniImage, Vec2(0, 0), Vec2(105, 85), Vec2(0, 0), 105.f, 2, 0.2, false);


}

CSquirtle::~CSquirtle()
{
}

void CSquirtle::tick()
{
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"SquirtlePlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Squirtle");
	}

	CPokemon::tick();
}

void CSquirtle::render(HDC _dc)
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
		GetAnimator()->CuntinuePlay(L"SquirtleUIAnim", true);
	}

	CPokemon::render(_dc);
}

/*void CCharmander::ISEvolution()
{
	// ������ 16�̸� ���ڵ�� ��ȭ
	if (16 == GetCurLV())
	{
		// ��ȭ �̹�Ʈ �־��ֱ�
		// ��ȭ �̹�Ʈ ����� ��ȭ�ϴ� Scene�� ������, UI�� �帧�� �°� ���´�.
		// ��ȭ �Ŀ��� ��ü�� ������ �ִ� �̹����� ��ȭ�� �̹����� �˸°� �ٲ��.
		// �̸��� �ٲ��.
		// ���� ��ȭ�� �´� ��ü���� �־��ִ� �Լ��� �߰��� ������ ������ ���ش�.

	}
	// ������ 36�̸� ���ڸ����� ��ȭ�Ѵ�.
	else if (36 == GetCurLV())
	{

	}
}*/