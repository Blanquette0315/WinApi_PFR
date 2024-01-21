#include "pch.h"
#include "CRedHouseScene2F.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"

#include "CRedHouseScene1F.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CRedHouse2f.h"
#include "CPlayer.h"

#include "CSound.h"

CRedHouseScene2F::CRedHouseScene2F()
	: m_pBGM(nullptr)
	, m_pEixtSound(nullptr)
	, m_pInSound(nullptr)
{
	m_pEixtSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingEixt");
	m_pInSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingIn");
	m_pBGM = CResourceMgr::CreateMgr()->FindSound(L"PalletTownTheme");
}

CRedHouseScene2F::~CRedHouseScene2F()
{
}

void CRedHouseScene2F::enter()
{
	CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);

	// �ش� Scene�� Object�� ���� �� ����

	CObject* pRedHouse2f = new CRedHouse2f;
	pRedHouse2f->SetPos(Vec2(-248.f, -112.f));
	AddObject(pRedHouse2f, LAYER_TYPE::BACKGROUND);

	// Player ����
	
	if (dynamic_cast<CRedHouseScene1F*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		m_pInSound->Play(false);
		AddLoadObject(L"Image\\map\\\Building\\HeroHouse2f1fPlayer.Map");
	}
	else
	{
		// ���� ���
		if (nullptr != m_pBGM)
		{
			m_pBGM->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\\Building\\HeroHouse2fDef.Map");
	}

	AddLoadObject(L"Image\\map\\\Building\\HeroHouse2fBed.Map");

	// ī�޶� ����
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// ī�޶� ����Ʈ

	// �浹 üũ ����
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CRedHouseScene2F::exit()
{
	// ������ ȿ����
	m_pEixtSound->Play(false);

	//CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 0.5);

	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CRedHouseScene2F::tick()
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

	/*if (IS_TAP(ENTER))
	{
		SceneChange(SCENE_TYPE::BATTLESCENE);
	}*/
}