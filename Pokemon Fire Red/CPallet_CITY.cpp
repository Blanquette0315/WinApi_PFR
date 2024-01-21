#include "pch.h"
#include "CPallet_CITY.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"

#include "CRoad01.h"
#include "COakLabScene.h"
#include "CGreenHouseScene.h"
#include "CRedHouseScene1F.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CPallet.h"
#include "CPlayer.h"
#include "CHouseRedRoof.h"
#include "CFlower.h"

#include "CSound.h"

CPallet_CITY::CPallet_CITY()
	: m_pBGM(nullptr)
{
	m_pBGM = CResourceMgr::CreateMgr()->FindSound(L"PalletTownTheme");
	m_pBGM->SetVolume(30);
}

CPallet_CITY::~CPallet_CITY()
{
}

void CPallet_CITY::enter()
{
	// 해당 Scene의 Object들 생성 및 설정

	// BackGround로 Pallet_City 생성 
	CObject* pPallet_City_BackGround = new CPallet;
	pPallet_City_BackGround->SetPos(Vec2(0.f, 0.f));
	AddObject(pPallet_City_BackGround, LAYER_TYPE::BACKGROUND);

	// Player 생성
	if (dynamic_cast<CRoad01*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		// 음악 재생
		if (nullptr != m_pBGM)
		{	
			m_pBGM->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\City\\PalletRoad1Player.Map");
	}

	else if (dynamic_cast<COakLabScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);
		// 음악 재생
		if (nullptr != m_pBGM)
		{
			m_pBGM->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\City\\PalletOakLabPlayer.Map");
	}

	else if (dynamic_cast<CGreenHouseScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);
		AddLoadObject(L"Image\\map\\City\\PalletGreenHousePlayer.Map");
	}

	else if (dynamic_cast<CRedHouseScene1F*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);
		AddLoadObject(L"Image\\map\\City\\PalletHeroHousePlayer.Map");
	}
	
	/*else
	{
		CObject* pPlayer = new CPlayer;

		pPlayer->SetPos(Vec2(800.f, 400.f));
		AddObject(pPlayer, LAYER_TYPE::PLAYER);
	}*/

	// 환경체 생성
	AddLoadObject(L"Image\\map\\City\\PalletBuilding.Map");
	AddLoadObject(L"Image\\map\\City\\PalletRedRoof.Map");
	AddLoadObject(L"Image\\map\\City\\PalletWhiteFence.Map");
	AddLoadObject(L"Image\\map\\City\\PalletWoodSign.Map");
	AddLoadObject(L"Image\\map\\City\\PalletMailBox.Map");
	AddLoadObject(L"Image\\map\\City\\PalletFlower.Map");
	AddLoadObject(L"Image\\map\\City\\PalletWhiteSign.Map");
	AddLoadObject(L"Image\\map\\City\\PalletATree.Map");
	AddLoadObject(L"Image\\map\\City\\PalletAATreeLeft.Map");
	AddLoadObject(L"Image\\map\\City\\PalletAATreeRight.Map");
	AddLoadObject(L"Image\\map\\City\\PalletATreeBottom.Map");
	AddLoadObject(L"Image\\map\\City\\PalletWave.Map");
	AddLoadObject(L"Image\\map\\City\\PalletWater.Map");

	// 카메라 설정
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// 카메라 이펙트

	// 충돌 체크 설정
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BACKGROUND);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CPallet_CITY::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CPallet_CITY::tick()
{
	CScene::tick();

	if (IS_TAP(T))
	{
		SceneChange(SCENE_TYPE::TOOL_SCENE);
	}

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