#include "pch.h"
#include "CGreenHouseScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CCameraMgr.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CGreenHouse.h"
#include "CPlayer.h"

#include "CSound.h"

CGreenHouseScene::CGreenHouseScene()
	: m_pEixtSound(nullptr)
	, m_pInSound(nullptr)
{
	m_pEixtSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingEixt");
	m_pInSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingIn");
}

CGreenHouseScene::~CGreenHouseScene()
{
}

void CGreenHouseScene::enter()
{
	CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);

	m_pInSound->Play(false);

	// �ش� Scene�� Object�� ���� �� ����

	CObject* pGreenHouse = new CGreenHouse;
	pGreenHouse->SetPos(Vec2(-184.f, -104.f));
	AddObject(pGreenHouse, LAYER_TYPE::BACKGROUND);

	// Player ����
	AddLoadObject(L"Image\\map\\\Building\\GreenHousePalletPlayer.Map");

	AddLoadObject(L"Image\\map\\\Building\\GreenHouse.Map");



	// ī�޶� ����
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// ī�޶� ����Ʈ

	// �浹 üũ ����
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CGreenHouseScene::exit()
{
	m_pEixtSound->Play(false);

	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CGreenHouseScene::tick()
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