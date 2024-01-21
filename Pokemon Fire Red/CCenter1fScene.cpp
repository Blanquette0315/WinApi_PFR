#include "pch.h"
#include "CCenter1fScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCameraMgr.h"

#include "CViridian_CITY.h"
#include "CPewter_CITY.h"
#include "CCenter2fScene.h"

#include "CMenuUI.h"
#include "CMenuArrow.h"

#include "CCenterIn1f.h"
#include "CPlayer.h"

#include "CSound.h"

CCenter1fScene::CCenter1fScene()
	: m_pBgm(nullptr)
	, m_pEixtSound(nullptr)
	, m_pInSound(nullptr)
{
	m_pBgm = CResourceMgr::CreateMgr()->FindSound(L"PokemonCenter");
	m_pEixtSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingEixt");
	m_pInSound = CResourceMgr::CreateMgr()->FindSound(L"BulidingIn");
}

CCenter1fScene::~CCenter1fScene()
{
}

void CCenter1fScene::enter()
{
	CCameraMgr::CreateMgr()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.8);

	// 해당 Scene의 Object들 생성 및 설정

	CObject* pCenterIn1f = new CCenterIn1f;
	pCenterIn1f->SetPos(Vec2(-120.f, -80.f));
	AddObject(pCenterIn1f, LAYER_TYPE::BACKGROUND);

	// Player 생성
	if ((dynamic_cast<CViridian_CITY*>(CSceneMgr::CreateMgr()->GetPrevScene()))
		|| (dynamic_cast<CPewter_CITY*>(CSceneMgr::CreateMgr()->GetPrevScene())))
	{
		m_pInSound->Play(false);

		// 음악 재생
		if (nullptr != m_pBgm)
		{
			m_pBgm->PlayToBGM(true);
		}

		AddLoadObject(L"Image\\map\\\Building\\CenterIn1fPlayer.Map");
	}

	else if (dynamic_cast<CCenter2fScene*>(CSceneMgr::CreateMgr()->GetPrevScene()))
	{
		AddLoadObject(L"Image\\map\\\Building\\CenterIn1f2fPlayer.Map");
	}

	AddLoadObject(L"Image\\map\\\Building\\CenterIn1f.Map");
	AddLoadObject(L"Image\\map\\\Building\\CenterIn1fEscalator.Map");

	// 카메라 설정
	CCameraMgr::CreateMgr()->SetTargetObject(GetPlayer());
	// 카메라 이펙트

	// 충돌 체크 설정
	CCollisionMgr::CreateMgr()->clear();

	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENVIRONMENT);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::ENVIRONMENT, LAYER_TYPE::PLAYER);
	CCollisionMgr::CreateMgr()->CollisionLayerCheck(LAYER_TYPE::BACKGROUND, LAYER_TYPE::PLAYER);
}

void CCenter1fScene::exit()
{
	m_pEixtSound->Play(false);

	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CCenter1fScene::tick()
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