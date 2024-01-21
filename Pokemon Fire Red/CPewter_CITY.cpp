#include "pch.h"
#include "CPewter_CITY.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CViridian_CITY.h"
#include "CMuseum1fScene.h"
#include "CPewterGymScene.h"
#include "CHouseBlackScene1.h"
#include "CHouseBlackScene.h"
#include "CCenter1fScene.h"
#include "CMartScene.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CPewter.h"
#include "CPlayer.h"

CPewter_CITY::CPewter_CITY()
{
}

CPewter_CITY::~CPewter_CITY()
{
}

void CPewter_CITY::enter()
{
	// 해당 Scene의 Object들 생성 및 설정

	CObject* pPewter_BackGround = new CPewter;
	pPewter_BackGround->SetPos(Vec2(0.f, 0.f));
	AddObject(pPewter_BackGround, LAYER_TYPE::BACKGROUND);

	// Player 생성
	if (dynamic_cast<CViridian_CITY*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\City\\PewterViridianPlayer.Map");
	}

	else if (dynamic_cast<CMuseum1fScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\City\\PewterMuseumPlayer.Map");
	}

	else if (dynamic_cast<CPewterGymScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\City\\PewterGymPlayer.Map");
	}

	else if (dynamic_cast<CHouseBlackScene1*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\City\\PewterBlackHouse1Player.Map");
	}

	else if (dynamic_cast<CHouseBlackScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\City\\PewterBlackHousePlayer.Map");
	}

	else if (dynamic_cast<CCenter1fScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\City\\PewterCenterPlayer.Map");
	}

	else if (dynamic_cast<CMartScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\City\\PewterMartPlayer.Map");
	}

	else
	{
		CObject* pPlayer = new CPlayer;

		pPlayer->SetPos(Vec2(1800.f, 800.f));
		AddObject(pPlayer, LAYER_TYPE::PLAYER);
	}

	AddLoadObject(L"Image\\map\\City\\PewterAATreeRight.Map");
	AddLoadObject(L"Image\\map\\City\\PewterATreeTop.Map");
	AddLoadObject(L"Image\\map\\City\\PewterAATreeLeft.Map");
	AddLoadObject(L"Image\\map\\City\\PewterAATreeBot.Map");
	AddLoadObject(L"Image\\map\\City\\PewterAATreeMid.Map");
	AddLoadObject(L"Image\\map\\City\\PewterATreeMid.Map");
	AddLoadObject(L"Image\\map\\City\\PewterATreeRight.Map");
	AddLoadObject(L"Image\\map\\City\\PewterMuseum.Map");
	AddLoadObject(L"Image\\map\\City\\PewterWoodFenceTop.Map");
	AddLoadObject(L"Image\\map\\City\\PewterWoodFenceMid.Map");
	AddLoadObject(L"Image\\map\\City\\PewterWoodFenceConer.Map");
	AddLoadObject(L"Image\\map\\City\\PewterWoodFence1.Map");
	AddLoadObject(L"Image\\map\\City\\PewterSmallTree.Map");
	AddLoadObject(L"Image\\map\\City\\PewterWhiteSign.Map");
	AddLoadObject(L"Image\\map\\City\\PewterWoodSign.Map");
	AddLoadObject(L"Image\\map\\City\\PewterFlower.Map");
	AddLoadObject(L"Image\\map\\City\\PewterBuilding.Map");
	AddLoadObject(L"Image\\map\\City\\PewterWhiteSign1.Map");
	AddLoadObject(L"Image\\map\\City\\PewterGym.Map");
	AddLoadObject(L"Image\\map\\City\\PewterWoodfence2.Map");



	// 카메라 설정
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// 카메라 이펙트

	// 충돌 체크 설정
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CPewter_CITY::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CPewter_CITY::tick()
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