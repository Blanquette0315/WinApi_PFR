#include "pch.h"
#include "CCenter2fScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CCenterIn2f.h"
#include "CPlayer.h"

#include "CSound.h"

CCenter2fScene::CCenter2fScene()
	: m_pEixtSound(nullptr)
	, m_pInSound(nullptr)
{
	m_pEixtSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingEixt");
	m_pInSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingIn");
}

CCenter2fScene::~CCenter2fScene()
{
}

void CCenter2fScene::enter()
{
	CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);

	m_pInSound->Play(false);

	// �ش� Scene�� Object�� ���� �� ����

	CObject* pCenterIn2f = new CCenterIn2f;
	pCenterIn2f->SetPos(Vec2(-120.f, -80.f));
	AddObject(pCenterIn2f, LAYER_TYPE::BACKGROUND);

	// Player ����
	AddLoadObject(L"Image\\map\\\Building\\CenterIn2fPlayer.Map");

	AddLoadObject(L"Image\\map\\\Building\\CenterIn2f.Map");
	AddLoadObject(L"Image\\map\\\Building\\CenterIn2fEscalator.Map");

	// ī�޶� ����
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// ī�޶� ����Ʈ

	// �浹 üũ ����
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CCenter2fScene::exit()
{
	m_pEixtSound->Play(false);

	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CCenter2fScene::tick()
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