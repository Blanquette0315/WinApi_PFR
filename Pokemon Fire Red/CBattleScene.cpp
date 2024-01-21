#include "pch.h"
#include "CBattleScene.h"

#include "CSceneMgr.h"
#include "CCollisionMgr.h"
#include "CResourceMgr.h"
#include "CBattleMgr.h"
#include "CTimeMgr.h"

#include "CImage.h"
#include "CSound.h"
#include "CGrassBattle.h"
#include "CBattleMessageBox.h"
#include "CPlayerMonsterInfoBox.h"
#include "CMonsterInfoBox.h"
#include "CPlayerActionBox.h"
#include "CBoxArrow.h"

#include "CRoad01.h"

#include "CPlayer.h"

#include "CSkill.h"

#include "CCharmander.h"
#include "CSquirtle.h"
#include "CBulbasaur.h"
#include "CCaterpie.h"
#include "CPidgey.h"
#include "CRattata.h"

CBattleScene::CBattleScene()
	 /*: m_TypeMatrix{
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NON, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NON, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::GREAT, EFFECT_TYPE::NON, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::GREAT},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NON},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NON, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NON, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NON, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK},
		{EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::WEEK, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::GREAT, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::NORMAL, EFFECT_TYPE::WEEK}
}*/
	: m_pBGM(nullptr)
	, m_pWinBGM(nullptr)
	, m_pPlayerPokemonInfo(nullptr)
	, m_pMonsterInfo(nullptr)
	, m_pMessageBox(nullptr)
	, m_pPlayerPokemon(nullptr)
	, m_pTargetPokemon(nullptr)
	, m_fDuration(0)
	, m_bActionBoxOn(false)
	, m_Select(false)
	, m_bSceneAnim(false)
	, m_bEXP(false)
	, m_bWinSound(false)
{
	m_pBGM = CResourceMgr::CreateMgr()->FindSound(L"BattleWildPokemon");
	m_pWinBGM = CResourceMgr::CreateMgr()->FindSound(L"VictoryWildPokemon");
}

CBattleScene::~CBattleScene()
{
	SAFE_DELETE(m_pPlayer);
}


void CBattleScene::tick()
{

	// �÷��̾� �ൿ ����
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::PLAYERACTION)
	{
		wstring _msg = L"";
		_msg = L"What will@" + m_pPlayerPokemon->GetName() + L" do?";
		m_pMessageBox->SetText(_msg);
		
		if(m_pMessageBox->IS_Message_End())
		{
			if (!m_bActionBoxOn)
			{
				CUI* pPlayerActionBox = new CPlayerActionBox(m_pPlayerPokemon, m_pPlayer);
				pPlayerActionBox->SetPos(Vec2(601.f, 560.f));
				AddObject(pPlayerActionBox, LAYER_TYPE::UI);
				pPlayerActionBox->SetSkillinfo(m_pPlayerPokemon->GetSkillInfo());

				m_bActionBoxOn = true;
			}
			m_fDuration = 0;
		}
	}

	// ��������
	// ������ ��� ¥�� ���߿� �� ���游 �Ű� ���ָ� �ȴ�.
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::RUN)
	{
		int irand = CBattleMgr::CreateMgr()->GetRunRand();
		m_bActionBoxOn = false;

		if (irand < 1)
		{
			m_pMessageBox->SetText(L"Fail");

			if (m_pMessageBox->IS_Message_End())
			{
				if (m_pMessageBox->IS_Enter())
				{
					CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::OTHERTURN);
					CBattleMgr::CreateMgr()->OtherAct();
				}
			}
		}
		else
		{
			m_pMessageBox->SetText(L"Yes");
			if (m_pMessageBox->IS_Message_End())
			{
				if (m_pMessageBox->IS_Enter())
				{
					if (dynamic_cast<CRoad01*>(CSceneMgr::CreateMgr()->GetPrevScene()))
					{
						SceneChange(SCENE_TYPE::ROAD_01);
					}
					
				}
			}
		}
	}

	// ����

	// ���ϸ� ����
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::POKEMONSHIFT)
	{
		m_bActionBoxOn = false;

		// �޼��� �ڽ��� �޼��� ���
		wstring _msg = L"";
		_msg = _msg + m_pPlayerPokemon->GetName() + L", that's enough!@Come back!";
		m_pMessageBox->SetText(_msg);

		if (!m_pPlayerPokemon->GetIOAnimOnce())
		{
			m_pPlayerPokemon->SetIOType(POKEMON_IO_TYPE::e_OUT);
		}

		if (m_pMessageBox->IS_Message_End())
		{
			if (m_pMessageBox->IS_Enter())
			{
				if (m_pPlayerPokemon->GetIOAnimOnce())
				{
					m_pPlayerPokemon->SetIOType(POKEMON_IO_TYPE::e_NONE);
				}

				m_pPlayerPokemon = CBattleMgr::CreateMgr()->GetPlayerPoke();
				
				CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::POKEMONSHIFT2);
			}
		}
	}
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::POKEMONSHIFT2)
	{
		m_pPlayerPokemon = CBattleMgr::CreateMgr()->GetPlayerPoke();
		wstring _msg = L"";
		_msg = _msg + L"Go! " + m_pPlayerPokemon->GetName() + L"!";
		m_pMessageBox->SetText(_msg);

		if (!m_pPlayerPokemon->GetIOAnimOnce())
		{
			m_pPlayerPokemon->SetIOType(POKEMON_IO_TYPE::e_IN);
		}

		if (m_pMessageBox->IS_Message_End())
		{
			if (m_pMessageBox->IS_Enter())
			{
				if (m_pPlayerPokemon->GetIOAnimOnce())
				{
					m_pPlayerPokemon->SetIOType(POKEMON_IO_TYPE::e_NONE);
				}

				SetResult();
				m_pPlayerPokemon->SetIOAnimOnce();

				CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::OTHERTURN);
				CBattleMgr::CreateMgr()->OtherAct();
				m_Select = true;
			}
		}
	}

	// ����

	// �÷��̾ ��ų�� ����� ���
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::PLAYERUSESKILL)
	{
		m_bActionBoxOn = false;

		// �޼��� �ڽ��� �޼��� ���
		wstring _msg = L"";
		_msg = _msg + m_pPlayerPokemon->GetName() + L" used @" + m_pPlayerPokemon->GetTargetSkill()->GetName();
		m_pMessageBox->SetText(_msg);

		if (m_pMessageBox->IS_Message_End())
		{
			if (m_pMessageBox->IS_Enter())
			{
				m_pMessageBox->SetText(L"");
				CBattleMgr::CreateMgr()->ActSkill();
			}
		}
	}

	// �÷��̾� ��ų ��� �� ������ ������ ��� ���
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::PALYERCALDMG)
	{
		if (!(m_pPlayerPokemon->GetTargetSkill()->IS_Animation_End()))
		{
			SetResult();

			if (m_pTargetPokemon->GetIncapacity()) // Ÿ�� ���ϸ��� �׾���
			{
				CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::OTHERDEADCHECK);
			}
			else
			{
				if (CBattleMgr::CreateMgr()->IS_Player_First())
				{
					CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::OTHERDEADCHECK);
				}
				else
					CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::PLAYERACTION);
			}
		}
	}

	// �÷��̾� ��� üũ
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::PLAYERDEADCHECK)
	{
		// �׾����� üũ
		if (m_pPlayerPokemon->GetIncapacity())
		{
			// �׾����� �ٸ� ���ϸ��� �ִ��� Ȯ��
			// �ٸ� ���ϸ��� ������, ���ϸ� ���� UI�� ����, ���ϸ� �����ϵ����ϱ�
			if (!(CBattleMgr::CreateMgr()->GetPokemonSize() == 1))
			{

			}
			// ������, ��Ʋ ����
			else
			{
				CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::BATTLEEND);
			}

		}
	}

	// ���� ����
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::OTHERTURN)
	{

		// �޼��� �ڽ��� �޼��� ���
		wstring _msg = L"";
		_msg = _msg + m_pTargetPokemon->GetName() + L" used @" + m_pTargetPokemon->GetTargetSkill()->GetName();
		m_pMessageBox->SetText(_msg);

		if (m_pMessageBox->IS_Message_End())
		{
			if (m_pMessageBox->IS_Enter())
			{
				m_pMessageBox->SetText(L"");
				CBattleMgr::CreateMgr()->OtherActSkill();
			}
		}
	}

	// ��밡 ���� �� ������ �ݿ� �� �޼��� ���
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::OTHERCALDMG)
	{
		if (!(m_pTargetPokemon->GetTargetSkill()->IS_Animation_End()))
		{
			SetResult();

			if (CBattleMgr::CreateMgr()->IS_Player_First() || m_Select || (m_pPlayerPokemon->GetTargetSkill() == nullptr))
			{
				CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::PLAYERACTION);
				m_Select = false;
			}
			else
				CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::PLAYERUSESKILL);
		}
	}

	// ��� ���ϸ� ���� üũ
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::OTHERDEADCHECK)
	{
		// �׾����� üũ
		if (m_pTargetPokemon->GetIncapacity())
		{
			// ���� ���
			if (!m_bWinSound)
			{
				if (nullptr != m_pWinBGM)
				{
					m_pWinBGM->PlayToBGM(true);
					m_bWinSound = true;
				}
			}

			// �׾�����, ��Ʋ ���Ḧ �˸��� ����ġ ȹ�� �� ��Ʋ�� ����
			wstring _msg = L"";
			_msg = _msg + L"The Wild " + m_pTargetPokemon->GetName() + L" has fallen!";
			m_pMessageBox->SetText(_msg);

			if (m_pMessageBox->IS_Message_End())
			{
				if (m_pMessageBox->IS_Enter())
				{
					m_pMessageBox->SetText(L"");
					CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::GETEXP);
					m_bEXP = true;
				}
			}
		}
		// ���� ��������� ��� �� ����
		else
		{
			CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::OTHERTURN);
			CBattleMgr::CreateMgr()->OtherAct();
		}
	}

	// ����ġ ȹ��
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::GETEXP)
	{
		m_bWinSound = false;

		if (m_bEXP)
		{
			m_pPlayerPokemon->AddBattleExp(m_pTargetPokemon->GetCurLV(),1);
			m_bEXP = false;
		}
		
		wstring _msg = L"";
		_msg = _msg + m_pTargetPokemon->GetName() + L" gained experience!";
		m_pMessageBox->SetText(_msg);

		if (m_pMessageBox->IS_Message_End())
		{
			if (m_pMessageBox->IS_Enter())
			{
				m_pMessageBox->SetText(L"");
				CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::BATTLEEND);
			}
		}
	}

	// ����
	if (CBattleMgr::CreateMgr()->GetBattle_Type() == BATTLE_TYPE::BATTLEEND)
	{
		if (dynamic_cast<CRoad01*>(CSceneMgr::CreateMgr()->GetPrevScene()))
		{
			SceneChange(SCENE_TYPE::ROAD_01);
		}
	}


	m_pPlayerPokemon->tick();
	CScene::tick();
}

void CBattleScene::render(HDC _dc)
{
	CScene::render(_dc);

	if (m_pPlayerPokemon->IsDead())
	{
		//iter = m_arrLayer[i].erase(iter);
	}
	else
	{
		if(!(m_pPlayerPokemon->GetPokSceneType() == POKEMONSCENE_TYPE::UI))
			m_pPlayerPokemon->render(_dc);
	}
}

void CBattleScene::enter()
{
	// ���� ���
	if (nullptr != m_pBGM)
	{
		m_pBGM->PlayToBGM(true);
	}

	// �ʿ� BackGround �̹��� ����
	CObject* pGrassBattle = new CGrassBattle;
	pGrassBattle->SetPos(Vec2(0.f, 0.f));
	AddObject(pGrassBattle, LAYER_TYPE::BACKGROUND);

	// ������Ʈ
	m_pPlayer = new CPlayer;
	for (int i = 0; i < m_pPlayer->GetNowPokemonSize(); ++i)
	{
		m_pPlayerPokemon = m_pPlayer->GetNowPokemon(i);
		m_pPlayerPokemon->SetPos(Vec2(360.f, 475.f));
		m_pPlayerPokemon->SetAddPos();
		m_pPlayerPokemon->SetPokSceneType(POKEMONSCENE_TYPE::BATTLE);
		CBattleMgr::CreateMgr()->PlayerPokemoninit(m_pPlayerPokemon);
		AddObject(m_pPlayerPokemon, LAYER_TYPE::PLAYERPOKEMON);
	}
	m_pPlayerPokemon = m_pPlayer->GetNowPokemon(0);

	// ������ ���ϸ� ���� ����
	srand(time(NULL));
	int i_rand = rand() % 3;
	int lev_rand = rand() % (5 - 3 + 1) + 3;
	switch (i_rand)
	{
	case 0:
	{
		CPokemon* pOtherPokemon = new CCaterpie(lev_rand);
		m_pTargetPokemon = pOtherPokemon;
		break;
	}
	case 1:
	{
		CPokemon* pOtherPokemon = new CPidgey(lev_rand);
		m_pTargetPokemon = pOtherPokemon;
		break;
	}
	case 2:
	{
		CPokemon* pOtherPokemon = new CRattata(lev_rand);
		m_pTargetPokemon = pOtherPokemon;
		break;
	}
	default:
		break;
	}
	m_pTargetPokemon->SetPos(Vec2(880.f, 270.f));
	m_pTargetPokemon->SetPokSceneType(POKEMONSCENE_TYPE::BATTLE);
	m_pTargetPokemon->SetOwnerType(OWNER_TYPE::WILD);
	AddObject(m_pTargetPokemon, LAYER_TYPE::MONSTER);

	// �޼��� �ڽ�
	CUI* pBattleMessageBox = new CBattleMessageBox;
	pBattleMessageBox->SetPos(Vec2(0.f, 560.f));
	pBattleMessageBox->SetText(L"What will@CHARMANDER do?");
	AddObject(pBattleMessageBox, LAYER_TYPE::UI);
	m_pMessageBox = pBattleMessageBox;
	CBattleMgr::CreateMgr()->SetMessageBox(pBattleMessageBox);

	CUI* pPlayerMonsterInfoBox = new CPlayerMonsterInfoBox;
	pPlayerMonsterInfoBox->SetPos(Vec2(630.f, 370.f));
	AddObject(pPlayerMonsterInfoBox, LAYER_TYPE::UI);
	m_pPlayerPokemonInfo = pPlayerMonsterInfoBox;

	CUI* pMonsterInfoBox = new CMonsterInfoBox;
	pMonsterInfoBox->SetPos(Vec2(65.f, 80.f));
	AddObject(pMonsterInfoBox, LAYER_TYPE::UI);
	m_pMonsterInfo = pMonsterInfoBox;

	/*CUI* pPlayerActionBox = new CPlayerActionBox(pCharmander);
	pPlayerActionBox->SetPos(Vec2(601.f, 560.f));
	AddObject(pPlayerActionBox, LAYER_TYPE::UI);
	pPlayerActionBox->SetSkillinfo(pCharmander->GetSkillInfo());*/

	CBattleMgr::CreateMgr()->SetPlayerPoke(m_pPlayerPokemon);
	CBattleMgr::CreateMgr()->SetTargetPoke(m_pTargetPokemon);

	pPlayerMonsterInfoBox->SetOutName(m_pPlayerPokemon->GetName());
	pPlayerMonsterInfoBox->SetOutLevel(m_pPlayerPokemon->GetCurLV());
	pPlayerMonsterInfoBox->SetOutMaxHP(m_pPlayerPokemon->GetMaxHP());
	pPlayerMonsterInfoBox->SetOutCurHP(m_pPlayerPokemon->GetCurHP());
	pPlayerMonsterInfoBox->SetOutMaxExp(m_pPlayerPokemon->GetMaxExp());
	pPlayerMonsterInfoBox->SetOutCurExp(m_pPlayerPokemon->GetCurExp());

	pMonsterInfoBox->SetOutName(m_pTargetPokemon->GetName());
	pMonsterInfoBox->SetOutLevel(m_pTargetPokemon->GetCurLV());
	pMonsterInfoBox->SetOutMaxHP(m_pTargetPokemon->GetMaxHP());
	pMonsterInfoBox->SetOutCurHP(m_pTargetPokemon->GetCurHP());


	CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::PLAYERACTION);
}

void CBattleScene::exit()
{
	SAFE_DELETE(m_pPlayer);
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();
	CBattleMgr::CreateMgr()->BattleMgrEixt();
}


void CBattleScene::SetResult()
{
	m_pPlayerPokemonInfo->SetOutName(m_pPlayerPokemon->GetName());
	m_pPlayerPokemonInfo->SetOutLevel(m_pPlayerPokemon->GetCurLV());
	m_pPlayerPokemonInfo->SetOutMaxHP(m_pPlayerPokemon->GetMaxHP());
	m_pPlayerPokemonInfo->SetOutCurHP(m_pPlayerPokemon->GetCurHP());
	m_pPlayerPokemonInfo->SetOutMaxExp(m_pPlayerPokemon->GetMaxExp());
	m_pPlayerPokemonInfo->SetOutCurExp(m_pPlayerPokemon->GetCurExp());

	m_pMonsterInfo->SetOutName(m_pTargetPokemon->GetName());
	m_pMonsterInfo->SetOutLevel(m_pTargetPokemon->GetCurLV());
	m_pMonsterInfo->SetOutMaxHP(m_pTargetPokemon->GetMaxHP());
	m_pMonsterInfo->SetOutCurHP(m_pTargetPokemon->GetCurHP());
}