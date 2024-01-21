#include "pch.h"
#include "CBackpackScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"

CBackpackScene::CBackpackScene()
{
}

CBackpackScene::~CBackpackScene()
{
}

void CBackpackScene::enter()
{
	// 해당 Scene의 Object들 생성 및 설정

}

void CBackpackScene::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CBackpackScene::tick()
{
	CScene::tick();
}