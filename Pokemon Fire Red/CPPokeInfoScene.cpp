#include "pch.h"
#include "CPPokeInfoScene.h"

#include "CEngine.h"

#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"

CPPokeInfoScene::CPPokeInfoScene()
{
}

CPPokeInfoScene::~CPPokeInfoScene()
{
}

void CPPokeInfoScene::enter()
{
	// �ش� Scene�� Object�� ���� �� ����

}

void CPPokeInfoScene::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// ���� �ߴ� ī�޶� ���� ���ش�.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CPPokeInfoScene::tick()
{
	CScene::tick();
}