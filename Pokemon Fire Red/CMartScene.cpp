#include "pch.h"
#include "CMartScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CMartIn.h"
#include "CPlayer.h"

CMartScene::CMartScene()
{
}

CMartScene::~CMartScene()
{
}

void CMartScene::enter()
{
	// �ش� Scene�� Object�� ���� �� ����

	CObject* pMartIn = new CMartIn;
	pMartIn->SetPos(Vec2(-248.f, -112.f));
	AddObject(pMartIn, LAYER_TYPE::BACKGROUND);

	// Player ����
	AddLoadObject(L"Image\\map\\\Building\\MartInPlayer.Map");

	AddLoadObject(L"Image\\map\\\Building\\MartIn.Map");

	// ī�޶� ����
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// ī�޶� ����Ʈ

	// �浹 üũ ����
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CMartScene::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CMartScene::tick()
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