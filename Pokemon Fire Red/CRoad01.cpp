#include "pch.h"
#include "CRoad01.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CPallet_CITY.h"
#include "CViridian_CITY.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CORoad1.h"
#include "CPlayer.h"

#include "CSound.h"

CRoad01::CRoad01()
	: m_pBGM(nullptr)
{
	m_pBGM = CResourceMgr::CreateMgr()->FindSound(L"RoadtoViridianCity");
	m_pBGM->SetVolume(30);
}

CRoad01::~CRoad01()
{
}

void CRoad01::enter()
{
	// �ش� Scene�� Object�� ���� �� ����

	// BackGround�� Pallet_City ���� 
	CObject* pRoad1_BackGround = new CORoad1;
	pRoad1_BackGround->SetPos(Vec2(0.f, 0.f));
	AddObject(pRoad1_BackGround, LAYER_TYPE::BACKGROUND);

	// Player ����
	if (dynamic_cast<CPallet_CITY*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		// ���� ���
		if (nullptr != m_pBGM)
		{
			m_pBGM->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\City\\Road1PalletPlayer.Map");
	}

	else if (dynamic_cast<CViridian_CITY*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		// ���� ���
		if (nullptr != m_pBGM)
		{
			m_pBGM->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\City\\Road1ViridianPlayer.Map");
	}

	else
	{
		// ���� ���
		if (nullptr != m_pBGM)
		{
			m_pBGM->PlayToBGM(true);
		}

		CObject* pPlayer = new CPlayer;

		pPlayer->SetPos(CSceneMgr::CreateMgr()->GetPlayerPrevPos());
		AddObject(pPlayer, LAYER_TYPE::PLAYER);
	}
	

	AddLoadObject(L"Image\\map\\City\\Road1AATreeRight.Map");
	AddLoadObject(L"Image\\map\\City\\Road1AATreeLeft.Map");
	AddLoadObject(L"Image\\map\\City\\Road1AATreeMid.Map");
	AddLoadObject(L"Image\\map\\City\\Road1ATreeMid.Map");
	AddLoadObject(L"Image\\map\\City\\Road1ATreeTop.Map");
	AddLoadObject(L"Image\\map\\City\\Road1Flower.Map");
	AddLoadObject(L"Image\\map\\City\\Road1WhiteFence.Map");
	AddLoadObject(L"Image\\map\\City\\Road1WhiteSign.Map"); 
	AddLoadObject(L"Image\\map\\City\\Road1Fence.Map");
	AddLoadObject(L"Image\\map\\City\\Road1GrassTop.Map");
	AddLoadObject(L"Image\\map\\City\\Road1GrassMid.Map");
	AddLoadObject(L"Image\\map\\City\\Road1GrassBot.Map");
	


	// ī�޶� ����
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// ī�޶� ����Ʈ

	// �浹 üũ ����
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CRoad01::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CRoad01::tick()
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