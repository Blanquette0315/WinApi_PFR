#include "pch.h"
#include "CCharmander.h"

#include "CResourceMgr.h"
#include "CTimeMgr.h"

#include "CImage.h"
#include "CAnimator.h"

#include "CScratch.h"
#include "CEmber.h"
#include "CRockTomb.h"

CCharmander::CCharmander(UINT _CurLV)
	: m_pImage(nullptr)
	, m_pMiniImage(nullptr)
	, m_eIOType(POKEMON_IO_TYPE::e_NONE)
	, m_fDuration(0.5)
	, m_fFaceTime(0)
	, m_bIOAnim(false)
{
	SetName(L"CHARMANDER");

	// ���� �־��ֱ�
	SetCurLv(_CurLV);

	// �⺻ ��ü�� �־��ֱ�
	SetBaseStats( 39, 52, 43, 65, 60, 50);

	// Ÿ�� �־��ֱ�
	SetPokemonType(POKEMON_TYPE::FIRE, POKEMON_TYPE::NONE);

	// ��ų �־��ֱ�
	AddSkill(0 ,new CScratch);
	AddSkill(1, new CEmber);
	AddSkill(2, new CRockTomb);

	GetSkill(0)->SetOwnerPokemon(this);
	GetSkill(1)->SetOwnerPokemon(this);
	GetSkill(2)->SetOwnerPokemon(this);

	// �˸��� �̹��� ����ֱ�
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"CharmanderPlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Charmander");
	}

	// UI Animation �־��ֱ�
	m_pMiniImage = CResourceMgr::CreateMgr()->FindImg(L"CharmanderUI");
	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"CharmanderUIAnim", m_pMiniImage, Vec2(0, 0), Vec2(105, 90), Vec2(0, 0), 105.f, 2, 0.2, false);

	
}

CCharmander::~CCharmander()
{
}

void CCharmander::tick()
{
	if (GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"CharmanderPlayer");
	}
	else
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Charmander");
	}

	CPokemon::tick();
}

void CCharmander::render(HDC _dc)
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
		GetAnimator()->CuntinuePlay(L"CharmanderUIAnim", true);
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