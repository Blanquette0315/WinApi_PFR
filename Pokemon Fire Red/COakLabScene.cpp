#include "pch.h"
#include "COakLabScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "COaksLabIn.h"
#include "CPlayer.h"
#include "COak.h"

#include "CCharmander.h"
#include "CBulbasaur.h"
#include "CSquirtle.h"

#include "CCaterpie.h"
#include "CRattata.h"
#include "CPidgey.h"

#include "CBattleMessageBox.h"
#include "COakLabUI.h"

#include "CSound.h"

COakLabScene::COakLabScene()
	: m_pMsgBox(nullptr)
	, m_bEvent(false)
	, m_pEixtSound(nullptr)
	, m_pInSound(nullptr)
{
	m_pEixtSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingEixt");
	m_pInSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingIn");
}

COakLabScene::~COakLabScene()
{
}

void COakLabScene::enter()
{
	CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);

	m_pInSound->Play(false);

	CSound* pBGM = CResourceMgr::CreateMgr()->FindSound(L"OakLaboratory");
	if (nullptr != pBGM)
	{
		//pBGM->Play(true);
		pBGM->SetVolume(30);
		pBGM->PlayToBGM(true);
		//pBGM->SetPosition(90.f);
	}

	// 해당 Scene의 Object들 생성 및 설정

	CObject* pOaksLabIn = new COaksLabIn;
	pOaksLabIn->SetPos(Vec2(-184.f, 24.f));
	AddObject(pOaksLabIn, LAYER_TYPE::BACKGROUND);

	// Player 생성
	AddLoadObject(L"Image\\map\\\Building\\OaksLabInPalletPlayer.Map");

	AddLoadObject(L"Image\\map\\\Building\\OaksLabIn.Map");
	AddLoadObject(L"Image\\map\\\Building\\OaksLabIn1.Map");
	AddLoadObject(L"Image\\map\\\Building\\OaksLabInOak.Map");

	// 카메라 설정
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// 카메라 이펙트

	// 충돌 체크 설정
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::NPC, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::NPC);
}

void COakLabScene::exit()
{
	m_pEixtSound->Play(false);

	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void COakLabScene::AddPokemonEvent(int _i)
{
	if (_i == 0)
	{
		CPokemon* temPokemon = new CCharmander(5);
		CSceneMgr::CreateMgr()->AddPokemon(temPokemon);
		//GetPlayer()->AddPokemon(temPokemon);
	}
	else if (_i == 1)
	{
		CPokemon* temPokemon = new CBulbasaur(5);
		CSceneMgr::CreateMgr()->AddPokemon(temPokemon);
		//GetPlayer()->AddPokemon(temPokemon);
	}
	else if (_i == 2)
	{
		CPokemon* temPokemon = new CSquirtle(5);
		CSceneMgr::CreateMgr()->AddPokemon(temPokemon);
		//GetPlayer()->AddPokemon(temPokemon);
	}

	// 나중에 지워야함. 발표를 위해서 캐터피, 구구, 꼬렛도 넣어주는 것.
	else if (_i == 3)
	{
		CPokemon* temPokemon = new CCaterpie(5);
		CSceneMgr::CreateMgr()->AddPokemon(temPokemon);
		//GetPlayer()->AddPokemon(temPokemon);
	}
	else if (_i == 4)
	{
		CPokemon* temPokemon = new CRattata(5);
		CSceneMgr::CreateMgr()->AddPokemon(temPokemon);
		//GetPlayer()->AddPokemon(temPokemon);
	}
	else if (_i == 5)
	{
		CPokemon* temPokemon = new CPidgey(5);
		CSceneMgr::CreateMgr()->AddPokemon(temPokemon);
		//GetPlayer()->AddPokemon(temPokemon);
	}

	DeleteUIObject();
	m_pMsgBox = nullptr;
}

void COakLabScene::tick()
{
	CScene::tick();

	if ((GetMenuISOn() == false) && IS_TAP(ESC))
	{
		SetMenuOn(true);
		CMenuUI* pMenuUI = new CMenuUI;
		Vec2 vPos = CEngine::CreateMgr()->GetResolution();
		vPos.x = vPos.x - 1 - 264;
		vPos.y = 1;
		pMenuUI->SetPos(vPos);
		AddObject(pMenuUI, LAYER_TYPE::UI);

		CMenuArrow* pMenuArrow = new CMenuArrow;
		vPos = pMenuUI->GetPos();
		vPos += Vec2(30, 45);
		pMenuArrow->SetPos(vPos);
		pMenuUI->AddChildUI(pMenuArrow);
	}

	if (m_bEvent && (IS_TAP(ENTER)))
	{
		SetMenuOn(true);
		m_pMsgBox = new CBattleMessageBox;
		m_pMsgBox->SetPos(Vec2(0, 560.f));
		m_pMsgBox->SetText(L"Choose a Pokemon");
		AddObject(m_pMsgBox, LAYER_TYPE::UI);
		m_bEvent = false;
	}

	if (!(m_pMsgBox == nullptr))
	{
		if (m_pMsgBox->IS_Message_End())
		{
			if (IS_TAP(ENTER))
			{
				COakLabUI* TemUI = new COakLabUI;
				AddObject(TemUI, LAYER_TYPE::UI);
				TemUI->SetISfocus(true);
			}
		}
	}
}