#include "pch.h"
#include "CMuseum2fScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CMuseumIn2f.h"
#include "CPlayer.h"

CMuseum2fScene::CMuseum2fScene()
{
}

CMuseum2fScene::~CMuseum2fScene()
{
}

void CMuseum2fScene::enter()
{
	// �ش� Scene�� Object�� ���� �� ����

	CObject* pMuseumIn2f = new CMuseumIn2f;
	pMuseumIn2f->SetPos(Vec2(0.f, -80.f));
	AddObject(pMuseumIn2f, LAYER_TYPE::BACKGROUND);

	// Player ����
	CObject* pPlayer = new CPlayer;

	pPlayer->SetPos(Vec2(200.f, 200.f));
	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	AddLoadObject(L"Image\\map\\\Building\\Museum2f.Map");

	// ī�޶� ����
	CCameraMgr::CreateMgr()->SetTargetObject(pPlayer);
	// ī�޶� ����Ʈ

	// �浹 üũ ����
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CMuseum2fScene::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CMuseum2fScene::tick()
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