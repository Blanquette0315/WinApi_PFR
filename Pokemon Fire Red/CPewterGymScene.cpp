#include "pch.h"
#include "CPewterGymScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CPewterGymIn.h"
#include "CPlayer.h"

CPewterGymScene::CPewterGymScene()
{
}

CPewterGymScene::~CPewterGymScene()
{
}

void CPewterGymScene::enter()
{
	// 해당 Scene의 Object들 생성 및 설정

	CObject* pPewterGymIn = new CPewterGymIn;
	pPewterGymIn->SetPos(Vec2(-216.f, 0.f));
	AddObject(pPewterGymIn, LAYER_TYPE::BACKGROUND);

	// Player 생성
	CObject* pPlayer = new CPlayer;

	pPlayer->SetPos(Vec2(200.f, 200.f));
	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	//AddLoadObject(L"Image\\map\\\Building\\HeroHouse2fBed.Map");

	// 카메라 설정
	CCameraMgr::CreateMgr()->SetTargetObject(pPlayer);
	// 카메라 이펙트

	// 충돌 체크 설정
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CPewterGymScene::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CPewterGymScene::tick()
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