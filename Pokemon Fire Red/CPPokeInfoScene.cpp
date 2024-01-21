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
	// 해당 Scene의 Object들 생성 및 설정

}

void CPPokeInfoScene::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// 설정 했던 카메라를 해제 해준다.
	CCameraMgr::CreateMgr()->SetTargetObject(nullptr);
}

void CPPokeInfoScene::tick()
{
	CScene::tick();
}