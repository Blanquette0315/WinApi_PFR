#include "pch.h"
#include "CRedHouseScene1F.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"

#include "CPallet_CITY.h"
#include "CRedHouseScene2F.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CRedHouse1f.h"
#include "CPlayer.h"

#include "CSound.h"

CRedHouseScene1F::CRedHouseScene1F()
	: m_pEixtSound(nullptr)
	, m_pInSound(nullptr)
{
	m_pEixtSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingEixt");
	m_pInSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingIn");
}

CRedHouseScene1F::~CRedHouseScene1F()
{
}

void CRedHouseScene1F::enter()
{
	CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);
	// 해당 Scene의 Object들 생성 및 설정

	CObject* pRedHouse1f = new CRedHouse1f;
	pRedHouse1f->SetPos(Vec2(-216.f, -104.f));
	AddObject(pRedHouse1f, LAYER_TYPE::BACKGROUND);

	// Player 생성
	if (dynamic_cast<CPallet_CITY*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		// 효과음 진행
		m_pInSound->Play(false);

		AddLoadObject(L"Image\\map\\\Building\\HeroHouse1fPalletPlayer.Map");
	}

	else if (dynamic_cast<CRedHouseScene2F*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\\Building\\HeroHouse1f2fPlayer.Map");
	}

	AddLoadObject(L"Image\\map\\\Building\\HeroHouse1fFlowerTable.Map");


	// 카메라 설정
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// 카메라 이펙트

	// 충돌 체크 설정
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CRedHouseScene1F::exit()
{
	//CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 0.5);
	m_pEixtSound->Play(false);
	

	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CRedHouseScene1F::tick()
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