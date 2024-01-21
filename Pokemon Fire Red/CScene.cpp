#include "pch.h"
#include "CScene.h"

#include "CPathMgr.h"
#include "CSceneMgr.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CHouseRedRoof.h"
#include "COaksLab.h"
#include "CHouse1.h"
#include "CHouse2.h"
#include "CGym.h"
#include "CCenter.h"
#include "CMart.h"

#include "CFlower.h"
#include "CATree.h"
#include "CAATree.h"
#include "CGrass.h"
#include "CMailBox.h"
#include "CWhiteFence.h"
#include "CWhiteSign.h"
#include "CWoodSign.h"
#include "CWave.h"
#include"CWave1.h"
#include"CWave2.h"
#include"CWave3.h"
#include"CWave4.h"
#include"CWave5.h"
#include"CWave6.h"
#include"CWave7.h"
#include "CWhiteFence1.h"
#include "CWhiteFenceLeftBot.h"
#include "CWhiteFenceLeftTop.h"
#include "CWhiteFenceRightBot.h"
#include "CWhiteFenceRightTop.h"
#include "CWoodFence.h"
#include "CWoodFence1.h"
#include "CWoodFenceLeftBot.h"
#include "CWoodFenceLeftTop.h"
#include "CWoodFenceRightBot.h"
#include "CWoodFenceRightTop.h"
#include "CSmallTree.h"
#include "CPalletWater.h"
#include "CRockTile.h"
#include "CRockTileConer.h"
#include "CMuseum.h"
#include "CHouseBlackRoof.h"
#include "CPewterGym.h"
#include "CGymSign.h"
#include "CBed.h"
#include "CTable.h"
#include "COakBookShelf.h"
#include "COakBookshelfHalf.h"
#include "COakBook.h"
#include "COakMachine.h"
#include "CFlowerpot.h"
#include "COakTable.h"
#include "COakMonsterBall.h"
#include "COakBookshelfHalf1.h"
#include "CCenterSofa.h"
#include "CCenterTable.h"
#include "CMartStand.h"
#include "CMartStand1.h"
#include "CMartTable.h"
#include "CMuseumStand.h"
#include "CMuseumStand1.h"
#include "CMuseumStand2.h"
#include "CMuseumBox.h"
#include "CHouseRedRoofGreen.h"
#include "CWoodFence2.h"
#include "CEscalator1f.h"
#include "CEscalator2f.h"
#include "COak.h"

#include "CBackPackUI.h"

CScene::CScene()
	: m_arrObjectInfo{}
	, m_bMenu_ON(false)
{
}

CScene::~CScene()
{
	DeleteAllObject();
	CEntity::~CEntity();
}


void CScene::tick()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		if (i == (UINT)LAYER_TYPE::PLAYERPOKEMON)
		{
		}
		else
		{
			for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
			{
				m_arrLayer[i][j]->tick();
			}
		}
		
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		if (i == (UINT)LAYER_TYPE::PLAYERPOKEMON)
		{
		}
		else
		{
			vector<CObject*>::iterator iter = m_arrLayer[i].begin();
			for (; iter != m_arrLayer[i].end(); )
			{
				if ((*iter)->IsDead())
				{
					iter = m_arrLayer[i].erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}
	}
}

void CScene::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		if(i == (UINT)LAYER_TYPE::PLAYERPOKEMON)
		{ }
		else
		{
			DeleteObject((LAYER_TYPE)i);
		}
	}
	m_arrObjectInfo.clear();
}

void CScene::DeleteObject(LAYER_TYPE _eType)
{
	vector<CObject*>& vecObj = m_arrLayer[(UINT)_eType];

	for (UINT j = 0; j < vecObj.size(); ++j)
	{
		SAFE_DELETE(vecObj[j]);
	}

	vecObj.clear();
	vector<CObject*>(vecObj).swap(vecObj);
}

void CScene::DeleteUIObject()
{
	vector<CObject*>& vecObj = m_arrLayer[(UINT)LAYER_TYPE::UI];

	for (UINT j = 0; j < vecObj.size(); ++j)
	{
		EventDeleteObject(vecObj[j]);
	}
}

void CScene::SetFocusedUI(CObject* _pUI)
{
	// Focused 처리 하려는 UI 를 UI 레이어 벡터안에서 찾아서 지우고
	vector<CObject*>::iterator iter = m_arrLayer[(UINT)LAYER_TYPE::UI].begin();
	for (; iter != m_arrLayer[(UINT)LAYER_TYPE::UI].end(); ++iter)
	{
		if (*iter == _pUI)
		{
			m_arrLayer[(UINT)LAYER_TYPE::UI].erase(iter);
			break;
		}
	}

	// 다시 맨 뒤로 넣는다.
	m_arrLayer[(UINT)LAYER_TYPE::UI].push_back(_pUI);
}

Vec2 CScene::SavePrevScenePos()
{
	return m_arrLayer[(UINT)LAYER_TYPE::PLAYER][0]->SavePrevScenePos();
}

void CScene::ObjectLoad(const wstring& _strRelativePath)
{
	wstring FilePath = CPathMgr::CreateMgr()->GetContentPath();
	FilePath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, FilePath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	// 오브젝트 정보 읽기

	UINT m_iObjectCount = 0;
	fread(&m_iObjectCount, sizeof(UINT), 1, pFile);

	tObjectInfo	ObjectInfo = {};

	for (UINT i = 0; i < m_iObjectCount; ++i)
	{
		ObjectInfo = {};
		fread(&ObjectInfo, sizeof(tObjectInfo), 1, pFile);
		m_arrObjectInfo.push_back(ObjectInfo);
	}

	fclose(pFile);
}

void CScene::AddLoadObject(const wstring& _strRelativePath)
{
	ObjectLoad(_strRelativePath);
	for (UINT i = 0; i < m_arrObjectInfo.size(); ++i)
	{
		OBJECT_TYPE _Type = m_arrObjectInfo[i].ObjectType;
		CObject* pNewObject = NewObject((UINT)_Type);
		pNewObject->SetPos(m_arrObjectInfo[i].ObjectPos);
		AddObject(pNewObject, m_arrObjectInfo[i].ObjectLayer);
	}
	m_arrObjectInfo.clear();
}

CObject* CScene::NewObject(UINT _Type)
{
	switch (_Type)
	{
	case (UINT)OBJECT_TYPE::HOUSEREDROOF:
	{
		CObject* pHouseRedRoof = new CHouseRedRoof;
		return pHouseRedRoof;
		break;
	}

	case (UINT)OBJECT_TYPE::OAKS_LAB:
	{
		CObject* pOaksLab = new COaksLab;
		return pOaksLab;
		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE1:
	{
		CObject* pHouse1 = new CHouse1;
		return pHouse1;
		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE2:
	{
		CObject* pHouse2 = new CHouse2;
		return pHouse2;
		break;
	}

	case (UINT)OBJECT_TYPE::GYM:
	{
		CObject* pGym = new CGym;
		return pGym;
		break;
	}

	case (UINT)OBJECT_TYPE::CENTER:
	{
		CObject* pCenter = new CCenter;
		return pCenter;
		break;
	}

	case (UINT)OBJECT_TYPE::MART:
	{
		CObject* pMart = new CMart;
		return pMart;
		break;
	}


	case (UINT)OBJECT_TYPE::PALLET:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::ROAD1:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::VIRIDIAN:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::PEWTER:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::REDHOUSE_1F:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::REDHOUSE_2F:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::GREENHOUSE:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE1_IN:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE2_IN:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::OAKS_LAB_IN:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::CENTER_1F:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::CENTER_2F:
	{
		break;
	}

	case (UINT)OBJECT_TYPE::MART_IN:
	{
		break;
	}


	case (UINT)OBJECT_TYPE::FLOWER:
	{
		CObject* pFlower = new CFlower;
		return pFlower;
		break;
	}

	case (UINT)OBJECT_TYPE::ATREE:
	{
		CObject* pATree = new CATree;
		return pATree;
		break;
	}

	case (UINT)OBJECT_TYPE::AATREE:
	{
		CObject* pAATree = new CAATree;
		return pAATree;
		break;
	}

	case (UINT)OBJECT_TYPE::GRASS:
	{
		CObject* pGrass = new CGrass;
		return pGrass;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE0:
	{
		CObject* pWave = new CWave;
		return pWave;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE1:
	{
		CObject* pWave1 = new CWave1;
		return pWave1;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE2:
	{
		CObject* pWave2 = new CWave2;
		return pWave2;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE3:
	{
		CObject* pWave3 = new CWave3;
		return pWave3;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE4:
	{
		CObject* pWave4 = new CWave4;
		return pWave4;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE5:
	{
		CObject* pWave5 = new CWave5;
		return pWave5;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE6:
	{
		CObject* pWave6 = new CWave6;
		return pWave6;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE7:
	{
		CObject* pWave7 = new CWave7;
		return pWave7;
		break;
	}

	case (UINT)OBJECT_TYPE::MAILBOX:
	{
		CObject* pMailBox = new CMailBox;
		return pMailBox;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITE_FENCE:
	{
		CObject* pWhiteFence = new CWhiteFence;
		return pWhiteFence;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITE_SIGN:
	{
		CObject* pWhiteSign = new CWhiteSign;
		return pWhiteSign;
		break;
	}

	case (UINT)OBJECT_TYPE::WOOD_SIGN:
	{
		CObject* pWoodSign = new CWoodSign;
		return pWoodSign;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCE1:
	{
		CObject* pWhiteFence1 = new CWhiteFence1;
		return pWhiteFence1;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCELEFTBOT:
	{
		CObject* pWhiteFenceLeftBot = new CWhiteFenceLeftBot;
		return pWhiteFenceLeftBot;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCELEFTTOP:
	{
		CObject* pWhiteFenceLeftTop = new CWhiteFenceLeftTop;
		return pWhiteFenceLeftTop;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCERIGHTBOT:
	{
		CObject* pWhiteFenceRightBot = new CWhiteFenceRightBot;
		return pWhiteFenceRightBot;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCERIGHTTOP:
	{
		CObject* pWhiteFenceRightTop = new CWhiteFenceRightTop;
		return pWhiteFenceRightTop;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCE:
	{
		CObject* pWoodFence = new CWoodFence;
		return pWoodFence;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCE1:
	{
		CObject* pWoodFence1 = new CWoodFence1;
		return pWoodFence1;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCELEFTBOT:
	{
		CObject* pWoodFenceLeftBot = new CWoodFenceLeftBot;
		return pWoodFenceLeftBot;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCELEFTTOP:
	{
		CObject* pWoodFenceLeftTop = new CWoodFenceLeftTop;
		return pWoodFenceLeftTop;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCERIGHTBOT:
	{
		CObject* pWoodFenceRightBot = new CWoodFenceRightBot;
		return pWoodFenceRightBot;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCERIGHTTOP:
	{
		CObject* pWoodFenceRightTop = new CWoodFenceRightTop;
		return pWoodFenceRightTop;
		break;
	}

	case (UINT)OBJECT_TYPE::SMALLTREE:
	{
		CObject* pSmallTree = new CSmallTree;
		return pSmallTree;
		break;
	}

	case (UINT)OBJECT_TYPE::PALLETWATER:
	{
		CObject* pPalletWater = new CPalletWater;
		return pPalletWater;
		break;
	}

	case (UINT)OBJECT_TYPE::ROCKTILE:
	{
		CObject* pRockTile = new CRockTile;
		return pRockTile;
		break;
	}
	case (UINT)OBJECT_TYPE::ROCKTILECONER:
	{
		CObject* pRockTileConer = new CRockTileConer;
		return pRockTileConer;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUM:
	{
		CObject* pMuseum = new CMuseum;
		return pMuseum;
		break;
	}
	case (UINT)OBJECT_TYPE::HOUSEBLACKROOF:
	{
		CObject* pHouseBlackRoof = new CHouseBlackRoof;
		return pHouseBlackRoof;
		break;
	}
	case (UINT)OBJECT_TYPE::PEWTER_GYM:
	{
		CObject* pPewterGym = new CPewterGym;
		return pPewterGym;
		break;
	}
	case (UINT)OBJECT_TYPE::GYMSIGN:
	{
		CObject* pGymSign = new CGymSign;
		return pGymSign;
		break;
	}
	case (UINT)OBJECT_TYPE::BED:
	{
		CObject* pBed = new CBed;
		return pBed;
		break;
	}
	case (UINT)OBJECT_TYPE::FLOWERPOT:
	{
		CObject* pFlowerpot = new CFlowerpot;
		return pFlowerpot;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOK:
	{
		CObject* pOakBook = new COakBook;
		return pOakBook;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELF:
	{
		CObject* pOakBookShelf = new COakBookShelf;
		return pOakBookShelf;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELFHALF:
	{
		CObject* pOakBookshelfHalf = new COakBookshelfHalf;
		return pOakBookshelfHalf;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKMACHINE:
	{
		CObject* pOakMachine = new COakMachine;
		return pOakMachine;
		break;
	}
	case (UINT)OBJECT_TYPE::TABLE:
	{
		CObject* pTable = new CTable;
		return pTable;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKTABLE:
	{
		CObject* pOakTable = new COakTable;
		return pOakTable;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKMONSTERBALL:
	{
		CObject* pOakMonsterBall = new COakMonsterBall;
		return pOakMonsterBall;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELFHALF1:
	{
		CObject* pOakBookshelfHalf1 = new COakBookshelfHalf1;
		return pOakBookshelfHalf1;
		break;
	}
	case (UINT)OBJECT_TYPE::CENTERSOFA:
	{
		CObject* pCenterSofa = new CCenterSofa;
		return pCenterSofa;
		break;
	}
	case (UINT)OBJECT_TYPE::CENTERTABLE:
	{
		CObject* pCenterTable = new CCenterTable;
		return pCenterTable;
		break;
	}
	case (UINT)OBJECT_TYPE::MARTSTAND:
	{
		CObject* pMartStand = new CMartStand;
		return pMartStand;
		break;
	}
	case (UINT)OBJECT_TYPE::MARTSTAND1:
	{
		CObject* pMartStand1 = new CMartStand1;
		return pMartStand1;
		break;
	}
	case (UINT)OBJECT_TYPE::MARTTABLE:
	{
		CObject* pMartTable = new CMartTable;
		return pMartTable;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND:
	{
		CObject* pMuseumStand = new CMuseumStand;
		return pMuseumStand;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND1:
	{
		CObject* pMuseumStand1 = new CMuseumStand1;
		return pMuseumStand1;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND2:
	{
		CObject* pMuseumStand2 = new CMuseumStand2;
		return pMuseumStand2;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMBOX:
	{
		CObject* pMuseumBox = new CMuseumBox;
		return pMuseumBox;
		break;
	}
	case (UINT)OBJECT_TYPE::PLAYER:
	{
		CObject* pPlayer = new CPlayer;
		return pPlayer;
		break;
	}
	case (UINT)OBJECT_TYPE::GREENREDHOUSE:
	{
		CObject* pHouseRedRoofGreen = new CHouseRedRoofGreen;
		return pHouseRedRoofGreen;
		break;
	}
	case (UINT)OBJECT_TYPE::ESCALATOR1F:
	{
		CObject* pEscalator1f = new CEscalator1f;
		return pEscalator1f;
		break;
	}
	case (UINT)OBJECT_TYPE::ESCALATOR2F:
	{
		CObject* pEscalator2f = new CEscalator2f;
		return pEscalator2f;
		break;
	}
	case (UINT)OBJECT_TYPE::WOODFENCE2:
	{
		CObject* pWoodFence2 = new CWoodFence2;
		return pWoodFence2;
		break;
	}

	case (UINT)OBJECT_TYPE::OAK:
	{
		CObject* pOak = new COak;
		return pOak;
		break;
	}

	default:
		break;
	}
}


void CScene::NewBackPackUI()
{
	CBackPackUI* pBackPackUI = new CBackPackUI;
	pBackPackUI->SetPos(Vec2(0,0)); // 일단은 00으로 잡아두었다 나중에 픽셀 위치 구해서 바꾸어야 함.
	AddObject(pBackPackUI, LAYER_TYPE::UI);
}
