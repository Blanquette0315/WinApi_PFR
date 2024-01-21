#include "pch.h"
#include "CHouse1Scene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CHouse1In.h"
#include "CPlayer.h"

#include "CSound.h"

CHouse1Scene::CHouse1Scene()
	: m_pEixtSound(nullptr)
	, m_pInSound(nullptr)
{
	m_pEixtSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingEixt");
	m_pInSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingIn");
}

CHouse1Scene::~CHouse1Scene()
{
}

void CHouse1Scene::enter()
{
	CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);

	m_pInSound->Play(false);

	// �ش� Scene�� Object�� ���� �� ����

	CObject* pHouse1In = new CHouse1In;
	pHouse1In->SetPos(Vec2(-248.f, -136.f));
	AddObject(pHouse1In, LAYER_TYPE::BACKGROUND);

	// Player ����

	AddLoadObject(L"Image\\map\\\Building\\House1ViridianPlayer.Map");
	

	AddLoadObject(L"Image\\map\\\Building\\House1In.Map");

	// ī�޶� ����
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// ī�޶� ����Ʈ

	// �浹 üũ ����
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CHouse1Scene::exit()
{
	m_pEixtSound->Play(false);

	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CHouse1Scene::tick()
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