#include "pch.h"
#include "CSceneMgr.h"
#include "CEventMgr.h"

#include "CPallet_CITY.h"
#include "CToolScene.h"
#include "CRoad01.h"
#include "CViridian_CITY.h"
#include "CPewter_CITY.h"
#include "CRedHouseScene1F.h"
#include "CRedHouseScene2F.h"
#include "CGreenHouseScene.h"
#include "COakLabScene.h"
#include "CHouse1Scene.h"
#include "CHouse2Scene.h"
#include "CCenter1fScene.h"
#include "CCenter2fScene.h"
#include "CMartScene.h"
#include "CHouseBlackScene.h"
#include "CHouseBlackScene1.h"
#include "CMuseum1fScene.h"
#include "CMuseum2fScene.h"
#include "CPewterGymScene.h"
#include "CBattleScene.h"

#include "CPokemon.h"


CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
	, m_pPrevScene(nullptr)
	, PlayerPrevPos{}
	, m_arrItem{}
{
	/*struct ITEM_INFO
	{
		UINT NUMBER;
		wstring Name;
	};*/

	ITEM_INFO ITEM1 = {};
	ITEM1.Name = L"POTION";
	ITEM1.NUMBER = 1;

	ITEM_INFO ITEM2 = {};
	ITEM2.Name = L"CANDY";
	ITEM2.NUMBER = 99;

	m_arrItem[0] = ITEM1;
	m_arrItem[1] = ITEM2;

}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < (UINT)SCENE_TYPE::END; ++i)

	{
		if (nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}

	for (int i = 0; i < m_arrNowPokemon.size(); ++i)
	{
		SAFE_DELETE(m_arrNowPokemon[i]);
	}
}

void CSceneMgr::init()
{
	// 일단은 Pallet_CITY에서 플레이어 동작, 애니메이션 동작, 툴작업들을 기초를 만들 것이다.
	m_arrScene[(UINT)SCENE_TYPE::PALLET_CITY] = new CPallet_CITY;
	m_arrScene[(UINT)SCENE_TYPE::ROAD_01] = new CRoad01;
	m_arrScene[(UINT)SCENE_TYPE::TOOL_SCENE] = new CToolScene;
	m_arrScene[(UINT)SCENE_TYPE::VIRIDIAN_CITY] = new CViridian_CITY;
	m_arrScene[(UINT)SCENE_TYPE::PEWTER_CITY] = new CPewter_CITY;

	m_arrScene[(UINT)SCENE_TYPE::BATTLESCENE] = new CBattleScene;

	m_arrScene[(UINT)SCENE_TYPE::REDHOUSESCENE1F] = new CRedHouseScene1F;
	m_arrScene[(UINT)SCENE_TYPE::REDHOUSESCENE2F] = new CRedHouseScene2F;
	m_arrScene[(UINT)SCENE_TYPE::GREENHOUSE] = new CGreenHouseScene;
	m_arrScene[(UINT)SCENE_TYPE::OAKLAB] = new COakLabScene;
	m_arrScene[(UINT)SCENE_TYPE::HOUSE1] = new CHouse1Scene;
	m_arrScene[(UINT)SCENE_TYPE::HOUSE2] = new CHouse2Scene;
	m_arrScene[(UINT)SCENE_TYPE::CENTER1F] = new CCenter1fScene;
	m_arrScene[(UINT)SCENE_TYPE::CENTER2F] = new CCenter2fScene;
	m_arrScene[(UINT)SCENE_TYPE::MART] = new CMartScene;
	m_arrScene[(UINT)SCENE_TYPE::HOUSEBLACKROOF] = new CHouseBlackScene;
	m_arrScene[(UINT)SCENE_TYPE::HOUSEBLACKROOF1] = new CHouseBlackScene1;
	m_arrScene[(UINT)SCENE_TYPE::MUSEUM1F] = new CMuseum1fScene;
	m_arrScene[(UINT)SCENE_TYPE::MUSEUM2F] = new CMuseum2fScene;
	m_arrScene[(UINT)SCENE_TYPE::PEWTERGYM] = new CPewterGymScene;

	ChangeScene(SCENE_TYPE::REDHOUSESCENE2F);
}

void CSceneMgr::tick()
{
	m_pCurScene->tick();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

CPokemon* CSceneMgr::GetPokemon(int index)
{
	return m_arrNowPokemon[index];
}

void CSceneMgr::AddPokemon(CPokemon* _Obj)
{
	m_arrNowPokemon.push_back(_Obj);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	if (nullptr != m_pCurScene)
	{
		if (_eNext == SCENE_TYPE::BATTLESCENE)
		{
			PlayerPrevPos = m_pCurScene->SavePrevScenePos();
		}

		m_pPrevScene = m_pCurScene;
		m_pCurScene->exit();
		CEventMgr::CreateMgr()->DeleteReRenderM();
	}

	m_pCurScene = m_arrScene[(UINT)_eNext];

	CEngine::CreateMgr()->SetTickOnce(false);
	m_pCurScene->enter();
}