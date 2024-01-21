#include "pch.h"
#include "CHouseBlackScene1.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CHouseBlackRoofIn.h"
#include "CPlayer.h"

CHouseBlackScene1::CHouseBlackScene1()
{
}

CHouseBlackScene1::~CHouseBlackScene1()
{
}

void CHouseBlackScene1::enter()
{
	// 해당 Scene의 Object들 생성 및 설정

	CObject* pHouseBlackRoofIn = new CHouseBlackRoofIn;
	pHouseBlackRoofIn->SetPos(Vec2(-248.f, -136.f));
	AddObject(pHouseBlackRoofIn, LAYER_TYPE::BACKGROUND);

	// Player 생성
	CObject* pPlayer = new CPlayer;

	pPlayer->SetPos(Vec2(300.f, 200.f));
	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	AddLoadObject(L"Image\\map\\\Building\\HouseBlackRoofInside.Map");

	// 카메라 설정
	CCameraMgr::CreateMgr()->SetTargetObject(pPlayer);
	// 카메라 이펙트

	// 충돌 체크 설정
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CHouseBlackScene1::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CHouseBlackScene1::tick()
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