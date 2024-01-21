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
	// �ش� Scene�� Object�� ���� �� ����

}

void CBackpackScene::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CBackpackScene::tick()
{
	CScene::tick();
}