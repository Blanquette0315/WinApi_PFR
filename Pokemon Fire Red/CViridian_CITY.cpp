#include "pch.h"
#include "CViridian_CITY.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"

#include "CRoad01.h"
#include "CPewter_CITY.h"
#include "CHouse1Scene.h"
#include "CHouse2Scene.h"
#include "CCenter1fScene.h"
#include "CMartScene.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CViridian.h"
#include "CPlayer.h"

#include "CSound.h"

CViridian_CITY::CViridian_CITY()
	: m_pBGM(nullptr)
{
	m_pBGM = CResourceMgr::CreateMgr()->FindSound(L"PewterCityTheme");
	m_pBGM->SetVolume(30);
}

CViridian_CITY::~CViridian_CITY()
{
}

void CViridian_CITY::enter()
{
	// 해당 Scene의 Object들 생성 및 설정

	CObject* pViridian_BackGround = new CViridian;
	pViridian_BackGround->SetPos(Vec2(0.f, 0.f));
	AddObject(pViridian_BackGround, LAYER_TYPE::BACKGROUND);

	// Player 생성
	if (dynamic_cast<CRoad01*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		// 음악 재생
		if (nullptr != m_pBGM)
		{
			m_pBGM->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\City\\ViridianRoad1Player.Map");
	}

	else if (dynamic_cast<CPewter_CITY*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		// 음악 재생
		if (nullptr != m_pBGM)
		{
			m_pBGM->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\City\\ViridianPewterPlayer.Map");
	}

	else if (dynamic_cast<CHouse1Scene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);
		AddLoadObject(L"Image\\map\\City\\ViridianHouse1Player.Map");
	}

	else if (dynamic_cast<CHouse2Scene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);
		AddLoadObject(L"Image\\map\\City\\ViridianHouse2Player.Map");
	}

	else if (dynamic_cast<CCenter1fScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);
		// 음악 재생
		if (nullptr != m_pBGM)
		{
			m_pBGM->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\City\\ViridianCenterPlayer.Map");
	}

	else if (dynamic_cast<CMartScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);
		AddLoadObject(L"Image\\map\\City\\ViridianMartPlayer.Map");
	}

	else
	{
		CObject* pPlayer = new CPlayer;

		pPlayer->SetPos(Vec2(1800.f, 850.f));
		AddObject(pPlayer, LAYER_TYPE::PLAYER);
	}

	AddLoadObject(L"Image\\map\\City\\ViridianHouse.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianBuilding.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianWhiteFenceWi1.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianWhiteFenceWi2.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianAATreeRight.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianAATreeBot1.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianAATreeBot2.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianATree.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianAATreeTop.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianFlower.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianWhiteSign.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianWoodSign.Map"); 
	AddLoadObject(L"Image\\map\\City\\ViridianWhiteFence1.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianWhiteFenceConer.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianSmallTree.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianWhiteFenceConer1.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianGymSign.Map");
	AddLoadObject(L"Image\\map\\City\\ViridianRock.Map");



	// 카메라 설정
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// 카메라 이펙트

	// 충돌 체크 설정
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CViridian_CITY::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CViridian_CITY::tick()
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
}