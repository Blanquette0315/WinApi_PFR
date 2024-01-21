#include "pch.h"
#include "CToolScene.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CUIMgr.h"
#include "CEventMgr.h"
#include "CResourceMgr.h"

#include "CBackGround.h"

#include "CPanelUI.h"
#include "CButtonUI.h"

#include "CHouseRedRoof.h"
#include "COaksLab.h"
#include "CHouse1.h"
#include "CHouse2.h"
#include "CGym.h"
#include "CCenter.h"
#include "CMart.h"

#include "CBackGround.h"

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
#include "CPlayer.h"
#include "CHouseRedRoofGreen.h"
#include "CWoodFence2.h"
#include "CEscalator1f.h"
#include "CEscalator2f.h"
#include "COak.h"


CToolScene::CToolScene()
	: m_eMode(TOOL_MODE::NONE)
	, m_iCurObject(0)
	, m_vAllObject{}
	, m_COUNT(0)
	, m_rCollider{}
	, m_IS_Render(false)
	, m_arrColliderInfo{}
	, m_eColliderType(COLLIDER_TYPE::NONE)
	, m_pFocusUI(nullptr)
	, m_vPos(800, 800)

	, m_arrObjectInfo{}
	, m_arrObjectPut{}
	, m_NowPos{}
	, m_eLayerType(LAYER_TYPE::PLAYER)
	, m_iObjectCount(0)
	, m_pSelectObjectButton(nullptr)
	, m_iCurScene(0)
	, m_pBackGround(nullptr)

	, m_arrLoadColl{}
{
}

CToolScene::~CToolScene()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)
	{
		SAFE_DELETE(m_vAllObject[i]);
	}

	for (UINT i = 0; i < m_arrObjectPut.size(); ++i)
	{
		SAFE_DELETE(m_arrObjectPut[i]);
	}

	SAFE_DELETE(m_pBackGround);
}

void CToolScene::enter()
{
	// ToolScene에서 사용할 Tool 이미지 로딩
	
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonClose", L"Image\\ToolScene\\Close.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonObjectMode", L"Image\\ToolScene\\ObjectMode.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonColliderMode", L"Image\\ToolScene\\ColliderMode.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonColliderDefualt", L"Image\\ToolScene\\ColliderDefault.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonColliderReRender", L"Image\\ToolScene\\ColliderReRender.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonColliderEvent", L"Image\\ToolScene\\ColliderEvent.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonColliderSet", L"Image\\ToolScene\\ColliderSet.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonSave", L"Image\\ToolScene\\Save.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonLoad", L"Image\\ToolScene\\Load.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonSet", L"Image\\ToolScene\\Set.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonPrev", L"Image\\ToolScene\\Prev.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonNext", L"Image\\ToolScene\\Next.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonLayerPlayer", L"Image\\ToolScene\\LayerPlayer.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonLayerNPC", L"Image\\ToolScene\\LayerNPC.bmp");
	CResourceMgr::CreateMgr()->LoadImg(L"ButtonLayerEnvironment", L"Image\\ToolScene\\LayerEnvironment.bmp");

	// UI 생성
	CreateUI();

	// 작업할 모든 Object 생성
	CreateObject();
	m_eColliderType = COLLIDER_TYPE::DEFAULT;

}

void CToolScene::exit()
{
	DeleteAllObject();
	CCollisionMgr::CreateMgr()->clear();

	// UIMgr 클리어
	CUIMgr::CreateMgr()->clear();

	// 만든 오브젝트 제거
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)
	{
		SAFE_DELETE(m_vAllObject[i]);
	}

	SAFE_DELETE(m_pBackGround);

	for (UINT i = 0; i < m_arrObjectPut.size(); ++i)
	{
		SAFE_DELETE(m_arrObjectPut[i]);
	}
}

void CToolScene::tick()
{
	CScene::tick();

	// Tool Mode Change Key
	if (IS_TAP(NUM_0))
	{
		m_eMode = TOOL_MODE::OBJECTPOS;
		m_pBackGround = new CBackGround;
		m_pBackGround->SetPos(Vec2(0, 0));
		m_iCurObject = 0;
	}
	else if (IS_TAP(NUM_1))
	{
		m_eMode = TOOL_MODE::COLLIDER;
		m_iCurObject = 0;
	}
	else if (IS_TAP(NUM_2))
		m_eMode = TOOL_MODE::ANIMATION;
	else if (IS_TAP(NUM_3))
		m_eMode = TOOL_MODE::NONE;

	if (IS_TAP(O))
	{
		CreateUI();
	}

	if (!(CUIMgr::CreateMgr()->GetFocusedUI() == nullptr))
		m_pFocusUI = CUIMgr::CreateMgr()->GetFocusedUI();

	switch (m_eMode)
	{
	case TOOL_MODE::OBJECTPOS:
		ObjectMode();


		break;
	case TOOL_MODE::COLLIDER:
		ColliderMode();


		break;
	case TOOL_MODE::ANIMATION:

		break;
	}
}

void CToolScene::render(HDC _dc)
{
	tSelectPen pen(_dc);
	pen.SetPenColor(PEN_COLOR::GREEN);
	tSelectBrush brush(_dc, BRUSH_COLOR::HOLLOW);

	switch (m_eMode)
	{
	case TOOL_MODE::OBJECTPOS:
	{
		m_pBackGround->render(_dc);
		/*if (m_iCurScene == (UINT)BACKGROUND_TYPE::PALLET)
		{
			m_pBackGround->render(_dc);
		}

		else if (m_iCurScene == (UINT)BACKGROUND_TYPE::ROAD1)
		{
			m_pBackGround->render(_dc);
		}

		else if (m_iCurScene == (UINT)BACKGROUND_TYPE::VIRIDIAN)
		{
			m_pBackGround->render(_dc);
		}

		else if (m_iCurScene == (UINT)BACKGROUND_TYPE::PEWTER)
		{
			m_pBackGround->render(_dc);
		}*/

		for (UINT i = 0; i < m_arrObjectPut.size(); ++i)
		{
			if (!(m_arrObjectPut[i]->IsDead()))
			{
				m_arrObjectPut[i]->render(_dc);
			}
		}

		m_vAllObject[m_iCurObject]->render(_dc);

		break;
	}
	
	case TOOL_MODE::COLLIDER:
		m_vAllObject[m_iCurObject]->render(_dc);
		
		if (m_IS_Render)
		{
			Rectangle(_dc, m_rCollider.left, m_rCollider.top, m_rCollider.right, m_rCollider.bottom);
		}

		
		for (UINT i = 0; i < m_COUNT; i++)
		{
			Rectangle(_dc, m_arrColliderInfo[i].rColliderPos.left,
				m_arrColliderInfo[i].rColliderPos.top,
				m_arrColliderInfo[i].rColliderPos.right,
				m_arrColliderInfo[i].rColliderPos.bottom);
		}


		break;
	case TOOL_MODE::ANIMATION:

		break;
	}

	CScene::render(_dc);
}

void CToolScene::CreateUI()
{
	// UI 만들기
	Vec2 vResolution = CEngine::CreateMgr()->GetResolution();

	// 패널 UI 만들기
	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetScale(Vec2(400.f, 150.f));
	pPanel->SetPos(Vec2(vResolution.x - pPanel->GetScale().x, 0.f));
	m_pFocusUI = pPanel;

	// 버튼 UI 만들기
	// 저장 버튼
	CButtonUI* pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 50.f));
	pButton->SetPos(Vec2(50.f, 50.f));
	// 일단 델리게이트 구조로 설계 중
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::CreateObjectUI);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonObjectMode"));
	pPanel->AddChildUI(pButton);

	// 닫기 버튼 만들기
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(25.f, 25.f));
	pButton->SetPos(Vec2(pPanel->GetScale().x - pButton->GetScale().x, 0.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::CloseUI);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonClose"));
	pPanel->AddChildUI(pButton);

	//열기 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 50.f));
	pButton->SetPos(Vec2(pPanel->GetScale().x - 50.f - pButton->GetScale().x, 50.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::CreateColldierUI);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonColliderMode"));
	pPanel->AddChildUI(pButton);

	// UI를 씬에 넣어줌
	AddObject(pPanel, LAYER_TYPE::UI);
	/*// 패널 하나 더 추가
	CPanelUI* pClonePanel = pPanel->Clone();
	pClonePanel->SetPos(Vec2(pPanel->GetPos().x - 400.f, pPanel->GetPos().y));
	AddObject(pClonePanel, LAYER_TYPE::UI);*/
}

// ======================
// =   ToolScene 공용   =
// ======================

// 모든 오브젝트를 만들어서 주소를 가지고 있다.
void CToolScene::CreateObject()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; ++i)
	{
		m_vAllObject[i] = NewObject(i);
		m_vAllObject[i]->SetISTool();
	}
}

// 오브젝트들을 동적할당 해서 생성함.
CObject* CToolScene::NewObject(UINT _i)
{
	switch (_i)
	{
	case (UINT)OBJECT_TYPE::HOUSEREDROOF:
	{
		return new CHouseRedRoof;
		break;
	}

	case (UINT)OBJECT_TYPE::OAKS_LAB:
	{
		return new COaksLab;
		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE1:
	{
		return new CHouse1;
		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE2:
	{
		return new CHouse2;
		break;
	}

	case (UINT)OBJECT_TYPE::GYM:
	{
		return new CGym;
		break;
	}

	case (UINT)OBJECT_TYPE::CENTER:
	{
		return new CCenter;
		break;
	}

	case (UINT)OBJECT_TYPE::MART:
	{
		return new CMart;
		break;
	}


	case (UINT)OBJECT_TYPE::PALLET:
	{
		CBackGround* pPALLET = new CBackGround;
		pPALLET->SetImage(L"PalletCity");
		return pPALLET;

		break;
	}

	case (UINT)OBJECT_TYPE::ROAD1:
	{
		CBackGround* pROAD1 = new CBackGround;
		pROAD1->SetImage(L"Road1");
		return pROAD1;

		break;
	}

	case (UINT)OBJECT_TYPE::VIRIDIAN:
	{
		CBackGround* pVIRIDIAN = new CBackGround;
		pVIRIDIAN->SetImage(L"ViridianCity");
		return pVIRIDIAN;

		break;
	}

	case (UINT)OBJECT_TYPE::PEWTER:
	{
		CBackGround* pPEWTER = new CBackGround;
		pPEWTER->SetImage(L"PewterCity");
		return pPEWTER;

		break;
	}

	case (UINT)OBJECT_TYPE::REDHOUSE_1F:
	{
		CBackGround* pREDHOUSE_1F = new CBackGround;
		pREDHOUSE_1F->SetImage(L"HeroHouse1f");
		return pREDHOUSE_1F;

		break;
	}

	case (UINT)OBJECT_TYPE::REDHOUSE_2F:
	{
		CBackGround* pREDHOUSE_2F = new CBackGround;
		pREDHOUSE_2F->SetImage(L"HeroHouse2f");
		return pREDHOUSE_2F;

		break;
	}

	case (UINT)OBJECT_TYPE::GREENHOUSE:
	{
		CBackGround* pGREENHOUSE = new CBackGround;
		pGREENHOUSE->SetImage(L"GreenHouse");
		return pGREENHOUSE;

		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE1_IN:
	{
		CBackGround* pHOUSE1_IN = new CBackGround;
		pHOUSE1_IN->SetImage(L"House1In");
		return pHOUSE1_IN;

		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE2_IN:
	{
		CBackGround* pHOUSE2_IN = new CBackGround;
		pHOUSE2_IN->SetImage(L"House2In");
		return pHOUSE2_IN;

		break;
	}

	case (UINT)OBJECT_TYPE::OAKS_LAB_IN:
	{
		CBackGround* pOAKS_LAB_IN = new CBackGround;
		pOAKS_LAB_IN->SetImage(L"OaksLabIn");
		return pOAKS_LAB_IN;

		break;
	}

	case (UINT)OBJECT_TYPE::CENTER_1F:
	{
		CBackGround* pCENTER_1F = new CBackGround;
		pCENTER_1F->SetImage(L"CenterIn1f");
		return pCENTER_1F;

		break;
	}

	case (UINT)OBJECT_TYPE::CENTER_2F:
	{
		CBackGround* pCENTER_2F = new CBackGround;
		pCENTER_2F->SetImage(L"CenterIn2f");
		return pCENTER_2F;

		break;
	}

	case (UINT)OBJECT_TYPE::MART_IN:
	{
		CBackGround* pMART_IN = new CBackGround;
		pMART_IN->SetImage(L"MartIn");
		return pMART_IN;

		break;
	}


	case (UINT)OBJECT_TYPE::FLOWER:
	{
		return new CFlower;
		break;
	}

	case (UINT)OBJECT_TYPE::ATREE:
	{
		return new CATree;
		break;
	}

	case (UINT)OBJECT_TYPE::AATREE:
	{
		return new CAATree;
		break;
	}

	case (UINT)OBJECT_TYPE::GRASS:
	{
		return new CGrass;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE0:
	{
		return new CWave;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE1:
	{
		return new CWave1;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE2:
	{
		return new CWave2;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE3:
	{
		return new CWave3;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE4:
	{
		return new CWave4;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE5:
	{
		return new CWave5;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE6:
	{
		return new CWave6;
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE7:
	{
		return new CWave7;
		break;
	}

	case (UINT)OBJECT_TYPE::MAILBOX:
	{
		return new CMailBox;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITE_FENCE:
	{
		return new CWhiteFence;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITE_SIGN:
	{
		return new CWhiteSign;
		break;
	}

	case (UINT)OBJECT_TYPE::WOOD_SIGN:
	{
		return new CWoodSign;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCE1:
	{
		return new CWhiteFence1;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCELEFTBOT:
	{
		return new CWhiteFenceLeftBot;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCELEFTTOP:
	{
		return new CWhiteFenceLeftTop;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCERIGHTBOT:
	{
		return new CWhiteFenceRightBot;
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCERIGHTTOP:
	{
		return new CWhiteFenceRightTop;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCE:
	{
		return new CWoodFence;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCE1:
	{
		return new CWoodFence1;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCELEFTBOT:
	{
		return new CWoodFenceLeftBot;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCELEFTTOP:
	{
		return new CWoodFenceLeftTop;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCERIGHTBOT:
	{
		return new CWoodFenceRightBot;
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCERIGHTTOP:
	{
		return new CWoodFenceRightTop;
		break;
	}

	case (UINT)OBJECT_TYPE::SMALLTREE:
	{
		return new CSmallTree;
		break;
	}

	case (UINT)OBJECT_TYPE::PALLETWATER:
	{
		return new CPalletWater;
		break;
	}

	case (UINT)OBJECT_TYPE::ROCKTILE:
	{
		return new CRockTile;
		break;
	}
	case (UINT)OBJECT_TYPE::ROCKTILECONER:
	{
		return new CRockTileConer;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUM:
	{
		return new CMuseum;
		break;
	}
	case (UINT)OBJECT_TYPE::HOUSEBLACKROOF:
	{
		return new CHouseBlackRoof;
		break;
	}
	case (UINT)OBJECT_TYPE::PEWTER_GYM:
	{
		return new CPewterGym;
		break;
	}
	case (UINT)OBJECT_TYPE::GYMSIGN:
	{
		return new CGymSign;
		break;
	}
	case (UINT)OBJECT_TYPE::BED:
	{
		return new CBed;
		break;
	}
	case (UINT)OBJECT_TYPE::FLOWERPOT:
	{
		return new CFlowerpot;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOK:
	{
		return new COakBook;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELF:
	{
		return new COakBookShelf;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELFHALF:
	{
		return new COakBookshelfHalf;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKMACHINE:
	{
		return new COakMachine;
		break;
	}
	case (UINT)OBJECT_TYPE::TABLE:
	{
		return new CTable;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKTABLE:
	{
		return new COakTable;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKMONSTERBALL:
	{
		return new COakMonsterBall;
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELFHALF1:
	{
		return new COakBookshelfHalf1;
		break;
	}
	case (UINT)OBJECT_TYPE::CENTERSOFA:
	{
		return new CCenterSofa;
		break;
	}
	case (UINT)OBJECT_TYPE::CENTERTABLE:
	{
		return new CCenterTable;
		break;
	}
	case (UINT)OBJECT_TYPE::MARTSTAND:
	{
		return new CMartStand;
		break;
	}
	case (UINT)OBJECT_TYPE::MARTSTAND1:
	{
		return new CMartStand1;
		break;
	}
	case (UINT)OBJECT_TYPE::MARTTABLE:
	{
		return new CMartTable;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND:
	{
		return new CMuseumStand;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND1:
	{
		return new CMuseumStand1;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND2:
	{
		return new CMuseumStand2;
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMBOX:
	{
		return new CMuseumBox;
		break;
	}
	case (UINT)OBJECT_TYPE::PLAYER:
	{
		return new CPlayer;
		break;
	}
	case (UINT)OBJECT_TYPE::GREENREDHOUSE:
	{
		return new CHouseRedRoofGreen;
		break;
	}
	case (UINT)OBJECT_TYPE::ESCALATOR1F:
	{
		return new CEscalator1f;
		break;
	}
	case (UINT)OBJECT_TYPE::ESCALATOR2F:
	{
		return new CEscalator2f;
		break;
	}
	case (UINT)OBJECT_TYPE::WOODFENCE2:
	{
		return new CWoodFence2;
		break;
	}

	case (UINT)OBJECT_TYPE::OAK:
	{
		return new COak;
		break;
	}

	default:
		break;
	}
}

void CToolScene::CloseUI()
{
	CUI* pUI = CUIMgr::CreateMgr()->GetFocusedUI();
	EventDeleteObject(pUI);
}

// ======================
// =    오브젝트 모드   =
// ======================

void CToolScene::CreateObjectUI()
{
	// UI 만들기
	Vec2 vResolution = CEngine::CreateMgr()->GetResolution();

	// 패널 UI 만들기
	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetScale(Vec2(400.f, 250.f));
	pPanel->SetPos(Vec2(vResolution.x - pPanel->GetScale().x, 0.f));
	// m_pPanelUI = pPanel;

	// 버튼 UI 만들기
	// 닫기 버튼 만들기
	CButtonUI* pButton = new CButtonUI;
	pButton->SetScale(Vec2(25.f, 25.f));
	pButton->SetPos(Vec2(pPanel->GetScale().x - pButton->GetScale().x, 0.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::CloseUI);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonClose"));
	pPanel->AddChildUI(pButton);
	
	// 저장 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 50.f));
	pButton->SetPos(Vec2(50.f, 50.f));
	// 일단 델리게이트 구조로 설계 중
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::ObjectSave);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonSave"));
	pPanel->AddChildUI(pButton);

	//열기 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 50.f));
	pButton->SetPos(Vec2(pPanel->GetScale().x - 50.f - pButton->GetScale().x, 50.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::ObjectLoad);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonLoad"));
	pPanel->AddChildUI(pButton);

	//오브젝트 선택 버튼
	/*m_pSelectObjectButton = new CButtonUI;
	m_pSelectObjectButton->SetScale(Vec2(300.f, 200.f));
	m_pSelectObjectButton->SetPos(Vec2(pPanel->GetScale().x - 350.f, pPanel->GetScale().y - 250.f));
	m_pSelectObjectButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SelectObject);
	pPanel->AddChildUI(m_pSelectObjectButton);*/

	// 오브젝트 레이어 타입 설정 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(25.f, 120.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SetPlayerType);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonLayerPlayer"));
	pPanel->AddChildUI(pButton);

	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(150.f, 120.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SetEnvironmentType);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonLayerEnvironment"));
	pPanel->AddChildUI(pButton);

	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(275.f, 120.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SetNPCType);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonLayerNPC"));
	pPanel->AddChildUI(pButton);


	// 오브젝트 인덱스 - 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(25.f, 180.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::PrevObject);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonPrev"));
	pPanel->AddChildUI(pButton);

	// 오브젝트 확정 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(150.f, 180.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SetObjectPos);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonSet"));
	pPanel->AddChildUI(pButton);

	// 오브젝트 인덱스 + 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(275.f, 180.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::NextObject);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonNext"));
	pPanel->AddChildUI(pButton);

	// UI를 씬에 넣어줌
	AddObject(pPanel, LAYER_TYPE::UI);
}

void CToolScene::ObjectMode()
{
	// 오브젝트 모드시 tick()
	if (IS_TAP(A))
	{
		if (!(m_iCurScene == 0))
		{
			for (UINT i = 0; i < m_arrObjectPut.size(); ++i)
			{
				EventDeleteObject(m_arrObjectPut[i]);
			}
			m_arrObjectPut.clear();
			m_iObjectCount = 0;
			--m_iCurScene;
		}
		
	}
	else if (IS_TAP(D))
	{
		if (!(m_iCurScene == ((UINT)OBJECT_TYPE::END) - 1))
		{
			for (UINT i = 0; i < m_arrObjectPut.size(); ++i)
			{
				EventDeleteObject(m_arrObjectPut[i]);
			}
			m_arrObjectPut.clear();
			m_iObjectCount = 0;
			++m_iCurScene;
		}
	}

	if (!(m_pFocusUI->IsMouseOn()))
	{
		if (IS_TAP(LBTN))
		{
			ClickPos();
		}
	}

	for (UINT i = 0; i < m_arrObjectPut.size(); ++i)
	{
		if (!(m_arrObjectPut[i]->IsDead()))
		{
			m_arrObjectPut[i]->tick();
		}
	}

	if (m_iCurScene == (UINT)BACKGROUND_TYPE::PALLET)
	{
		m_pBackGround->SetImage(L"PalletCity");
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::ROAD1)
	{
		m_pBackGround->SetImage(L"Road1");
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::VIRIDIAN)
	{
		m_pBackGround->SetImage(L"ViridianCity");
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::PEWTER)
	{
		m_pBackGround->SetImage(L"PewterCity");
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::REDHOUSESCENE1F)
	{
		m_pBackGround->SetImage(L"HeroHouse1f");
		m_pBackGround->SetPos(Vec2(-216.f, -104.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::REDHOUSESCENE2F)
	{
		m_pBackGround->SetImage(L"HeroHouse2f");
		m_pBackGround->SetPos(Vec2(-248.f, -112.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::GREENHOUSESCENE)
	{
		m_pBackGround->SetImage(L"GreenHouse");
		m_pBackGround->SetPos(Vec2(-184.f, -104.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::OAKLABSCENE)
	{
		m_pBackGround->SetImage(L"OaksLabIn");
		m_pBackGround->SetPos(Vec2(-184.f, 24.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::HOUSE1SCENE)
	{
		m_pBackGround->SetImage(L"House1In");
		m_pBackGround->SetPos(Vec2(-248.f, -136.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::HOUSE2SCENE)
	{
		m_pBackGround->SetImage(L"House2In");
		m_pBackGround->SetPos(Vec2(-280.f, -136.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::CENTERSCENE1F)
	{
		m_pBackGround->SetImage(L"CenterIn1f");
		m_pBackGround->SetPos(Vec2(-120.f, -80.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::CENTERSCENE2F)
	{
		m_pBackGround->SetImage(L"CenterIn2f");
		m_pBackGround->SetPos(Vec2(-120.f, -80.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::MARTSCENE)
	{
		m_pBackGround->SetImage(L"MartIn");
		m_pBackGround->SetPos(Vec2(-248.f, -112.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::HOUSEBLACKROOFSCENE)
	{
		m_pBackGround->SetImage(L"HouseBlackRoofInside");
		m_pBackGround->SetPos(Vec2(-248.f, -136.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::MUSEUMSCENE1F)
	{
		m_pBackGround->SetImage(L"MuseumInside");
		m_pBackGround->SetPos(Vec2(0.f, -38.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::MUSEUMSCENE2F)
	{
		m_pBackGround->SetImage(L"Museum2f");
		m_pBackGround->SetPos(Vec2(0.f, -80.f));
	}

	else if (m_iCurScene == (UINT)BACKGROUND_TYPE::PEWTERGYMSCENE)
	{
		m_pBackGround->SetImage(L"PewterGymInside");
		m_pBackGround->SetPos(Vec2(-216.f, 0.f));
	}

	m_vPos = CKeyMgr::CreateMgr()->GetMouseRealPos();
	m_vAllObject[m_iCurObject]->SetPos(m_vPos);
	m_vAllObject[m_iCurObject]->tick();
	m_pBackGround->tick();
}

void CToolScene::SelectObject()
{
}

void CToolScene::SetPlayerType()
{
	m_eLayerType = LAYER_TYPE::PLAYER;
}

void CToolScene::SetEnvironmentType()
{
	m_eLayerType = LAYER_TYPE::ENVIRONMENT;
}

void CToolScene::SetNPCType()
{
	m_eLayerType = LAYER_TYPE::NPC;
}

void CToolScene::PrevObject()
{
	if (!(0 == m_iCurObject))
	{
		--m_iCurObject;
	}
}

void CToolScene::SetObjectPos()
{
}

void CToolScene::NextObject()
{
	if (!(m_iCurObject == ((UINT)OBJECT_TYPE::END)-1))
	{
		++m_iCurObject;
	}
}

void CToolScene::ClickPos()
{
	m_vPos = CKeyMgr::CreateMgr()->GetMouseRealPos();

	switch (m_iCurObject)
	{
	case (UINT)OBJECT_TYPE::HOUSEREDROOF:
	{
		m_arrObjectPut.push_back(new CHouseRedRoof);
		break;
	}

	case (UINT)OBJECT_TYPE::OAKS_LAB:
	{
		m_arrObjectPut.push_back(new COaksLab);
		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE1:
	{
		m_arrObjectPut.push_back(new CHouse1);
		break;
	}

	case (UINT)OBJECT_TYPE::HOUSE2:
	{
		m_arrObjectPut.push_back(new CHouse2);
		break;
	}

	case (UINT)OBJECT_TYPE::GYM:
	{
		m_arrObjectPut.push_back(new CGym);
		break;
	}

	case (UINT)OBJECT_TYPE::CENTER:
	{
		m_arrObjectPut.push_back(new CCenter);
		break;
	}

	case (UINT)OBJECT_TYPE::MART:
	{
		m_arrObjectPut.push_back(new CMart);
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
		m_arrObjectPut.push_back(new CFlower);
		break;
	}

	case (UINT)OBJECT_TYPE::ATREE:
	{
		m_arrObjectPut.push_back(new CATree);
		break;
	}

	case (UINT)OBJECT_TYPE::AATREE:
	{
		m_arrObjectPut.push_back(new CAATree);
		break;
	}

	case (UINT)OBJECT_TYPE::GRASS:
	{
		m_arrObjectPut.push_back(new CGrass);
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE0:
	{
		m_arrObjectPut.push_back(new CWave);
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE1:
	{
		m_arrObjectPut.push_back(new CWave1);
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE2:
	{
		m_arrObjectPut.push_back(new CWave2);
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE3:
	{
		m_arrObjectPut.push_back(new CWave3);
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE4:
	{
		m_arrObjectPut.push_back(new CWave4);
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE5:
	{
		m_arrObjectPut.push_back(new CWave5);
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE6:
	{
		m_arrObjectPut.push_back(new CWave6);
		break;
	}

	case (UINT)OBJECT_TYPE::WAVE7:
	{
		m_arrObjectPut.push_back(new CWave7);
		break;
	}

	case (UINT)OBJECT_TYPE::MAILBOX:
	{
		m_arrObjectPut.push_back(new CMailBox);
		break;
	}

	case (UINT)OBJECT_TYPE::WHITE_FENCE:
	{
		m_arrObjectPut.push_back(new CWhiteFence);
		break;
	}

	case (UINT)OBJECT_TYPE::WHITE_SIGN:
	{
		m_arrObjectPut.push_back(new CWhiteSign);
		break;
	}

	case (UINT)OBJECT_TYPE::WOOD_SIGN:
	{
		m_arrObjectPut.push_back(new CWoodSign);
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCE1:
	{
		m_arrObjectPut.push_back(new CWhiteFence1);
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCELEFTBOT:
	{
		m_arrObjectPut.push_back(new CWhiteFenceLeftBot);
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCELEFTTOP:
	{
		m_arrObjectPut.push_back(new CWhiteFenceLeftTop);
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCERIGHTBOT:
	{
		m_arrObjectPut.push_back(new CWhiteFenceRightBot);
		break;
	}

	case (UINT)OBJECT_TYPE::WHITEFENCERIGHTTOP:
	{
		m_arrObjectPut.push_back(new CWhiteFenceRightTop);
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCE:
	{
		m_arrObjectPut.push_back(new CWoodFence);
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCE1:
	{
		m_arrObjectPut.push_back(new CWoodFence1);
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCELEFTBOT:
	{
		m_arrObjectPut.push_back(new CWoodFenceLeftBot);
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCELEFTTOP:
	{
		m_arrObjectPut.push_back(new CWoodFenceLeftTop);
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCERIGHTBOT:
	{
		m_arrObjectPut.push_back(new CWoodFenceRightBot);
		break;
	}

	case (UINT)OBJECT_TYPE::WOODFENCERIGHTTOP:
	{
		m_arrObjectPut.push_back(new CWoodFenceRightTop);
		break;
	}

	case (UINT)OBJECT_TYPE::SMALLTREE:
	{
		m_arrObjectPut.push_back(new CSmallTree);
		break;
	}

	case (UINT)OBJECT_TYPE::PALLETWATER:
	{
		m_arrObjectPut.push_back(new CPalletWater);
		break;
	}

	case (UINT)OBJECT_TYPE::ROCKTILE:
	{
		m_arrObjectPut.push_back(new CRockTile);
		break;
	}
	case (UINT)OBJECT_TYPE::ROCKTILECONER:
	{
		m_arrObjectPut.push_back(new CRockTileConer);
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUM:
	{
		m_arrObjectPut.push_back(new CMuseum);
		break;
	}
	case (UINT)OBJECT_TYPE::HOUSEBLACKROOF:
	{
		m_arrObjectPut.push_back(new CHouseBlackRoof);
		break;
	}
	case (UINT)OBJECT_TYPE::PEWTER_GYM:
	{
		m_arrObjectPut.push_back(new CPewterGym);
		break;
	}
	case (UINT)OBJECT_TYPE::GYMSIGN:
	{
		m_arrObjectPut.push_back(new CGymSign);
		break;
	}
	case (UINT)OBJECT_TYPE::BED:
	{
		m_arrObjectPut.push_back(new CBed);
		break;
	}
	case (UINT)OBJECT_TYPE::FLOWERPOT:
	{
		m_arrObjectPut.push_back(new CFlowerpot);
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOK:
	{
		m_arrObjectPut.push_back(new COakBook);
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELF:
	{
		m_arrObjectPut.push_back(new COakBookShelf);
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELFHALF:
	{
		m_arrObjectPut.push_back(new COakBookshelfHalf);
		break;
	}
	case (UINT)OBJECT_TYPE::OAKMACHINE:
	{
		m_arrObjectPut.push_back(new COakMachine);
		break;
	}
	case (UINT)OBJECT_TYPE::TABLE:
	{
		m_arrObjectPut.push_back(new CTable);
		break;
	}
	case (UINT)OBJECT_TYPE::OAKTABLE:
	{
		m_arrObjectPut.push_back(new COakTable);
		break;
	}
	case (UINT)OBJECT_TYPE::OAKMONSTERBALL:
	{
		m_arrObjectPut.push_back(new COakMonsterBall);
		break;
	}
	case (UINT)OBJECT_TYPE::OAKBOOKSHELFHALF1:
	{
		m_arrObjectPut.push_back(new COakBookshelfHalf1);
		break;
	}
	case (UINT)OBJECT_TYPE::CENTERSOFA:
	{
		m_arrObjectPut.push_back(new CCenterSofa);
		break;
	}
	case (UINT)OBJECT_TYPE::CENTERTABLE:
	{
		m_arrObjectPut.push_back(new CCenterTable);
		break;
	}
	case (UINT)OBJECT_TYPE::MARTSTAND:
	{
		m_arrObjectPut.push_back(new CMartStand);
		break;
	}
	case (UINT)OBJECT_TYPE::MARTSTAND1:
	{
		m_arrObjectPut.push_back(new CMartStand1);
		break;
	}
	case (UINT)OBJECT_TYPE::MARTTABLE:
	{
		m_arrObjectPut.push_back(new CMartTable);
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND:
	{
		m_arrObjectPut.push_back(new CMuseumStand);
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND1:
	{
		m_arrObjectPut.push_back(new CMuseumStand1);
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMSTAND2:
	{
		m_arrObjectPut.push_back(new CMuseumStand2);
		break;
	}
	case (UINT)OBJECT_TYPE::MUSEUMBOX:
	{
		m_arrObjectPut.push_back(new CMuseumBox);
		break;
	}
	case (UINT)OBJECT_TYPE::PLAYER:
	{
		m_arrObjectPut.push_back(new CPlayer);
		break;
	}
	case (UINT)OBJECT_TYPE::GREENREDHOUSE:
	{
		m_arrObjectPut.push_back(new CHouseRedRoofGreen);
		break;
	}
	case (UINT)OBJECT_TYPE::ESCALATOR1F:
	{
		m_arrObjectPut.push_back(new CEscalator1f);
		break;
	}
	case (UINT)OBJECT_TYPE::ESCALATOR2F:
	{
		m_arrObjectPut.push_back(new CEscalator2f);
		break;
	}
	case (UINT)OBJECT_TYPE::WOODFENCE2:
	{
		m_arrObjectPut.push_back(new CWoodFence2);
		break;
	}

	case (UINT)OBJECT_TYPE::OAK:
	{
		m_arrObjectPut.push_back(new COak);
		break;
	}

	default:
		break;
	}

	m_arrObjectPut[m_iObjectCount]->SetPos(m_vPos);
	m_arrObjectPut[m_iObjectCount]->SetISTool();
	m_arrObjectLayerType.push_back(m_eLayerType);
	m_arrObjectType.push_back((OBJECT_TYPE)m_iCurObject);
	++m_iObjectCount;
}


void CToolScene::ObjectSave()
{
	// 정한 object save 설정

	 // open a file name
	OPENFILENAME ofn = {};

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Map\0*.map\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	// 파일 입출력
	FILE* pFile = nullptr;

	// 쓰기 모드로 열기
	_wfopen_s(&pFile, szFilePath, L"wb");

	if (nullptr == pFile)
		return;

	// 오브젝트 포지션 정보
	// 오브젝트 백터에 담겨있는 총 수량을 전달해 준다.
	fwrite(&m_iObjectCount, sizeof(UINT), 1, pFile);

	tObjectInfo temObjectInfo = {};
	// 벡터 전체를 돌면서 전달할 info 구조체에 필요한 정보만 옮겨준다.
	for (UINT i = 0; i < m_iObjectCount; ++i)
	{
		temObjectInfo = {};
		temObjectInfo.ObjectLayer = m_arrObjectLayerType[i];
		temObjectInfo.ObjectPos = m_arrObjectPut[i]->GetPos();
		temObjectInfo.ObjectType = m_arrObjectType[i];

		fwrite(&temObjectInfo, sizeof(tObjectInfo), 1, pFile);
	}

}

void CToolScene::ObjectLoad()
{
	// 이미 만들어진 object pos 파일 열어서 읽어오기
}


// ======================
// =    콜라이더 모드   =
// ======================

void CToolScene::ColliderMode()
{
	// 콜라이더 모드
	// tick 마다 동작함.
	// 콜라이더 모드로 진입하면 오브젝트를 띄워준다.
	// 마우스로 좌클릭 후, 드래그해서 좌클릭을 해제하면 콜라이더가 그려질 lefttop pos, rightbottom pos이 정해진다.

	// 그렇게 정한 콜라이더 포지션 정보는 파일로 저장이되고, 저장된 파일 정보대로 각 오브젝트의 Collider가 적용된다.

	// Collider 모드때 필요한 설정 값
	// ㄴ 콜라이더 타입
	// 콜라이더 타입을 UI에서 선택하고 드래그로 Collider를 그리면 POINT 구조체로 사각형 정보가 들어감.
	// 콜라이더는 동일하게 최대 6개

	// 드래그 하면 사각형이 그려지고 info가 채워짐.


	// 마우스로 설정
	// 화면 타겟 처리 해주어야 함. (안해줘도 괜찮을 듯?)

	if (IS_TAP(A))
	{
		if(!(m_iCurObject == 0))
			--m_iCurObject;
	}
	else if (IS_TAP(D))
	{
		if(!(m_iCurObject == ((UINT)OBJECT_TYPE::END)-1))
			++m_iCurObject;
	}

	// UI가 타겟이 아닌 경우에만 체크 해야한다.
	if(!(m_pFocusUI->IsMouseOn()))
	{

		if (dynamic_cast<CBackGround*>(m_vAllObject[m_iCurObject]))
		{
			if (IS_TAP(LBTN))
			{
				m_rCollider.left = CKeyMgr::CreateMgr()->GetMouseRealPos().x;
				m_rCollider.top = CKeyMgr::CreateMgr()->GetMouseRealPos().y;
				m_IS_Render = false;
			}
			if (IS_RELEASE(LBTN))
			{
				m_rCollider.right = CKeyMgr::CreateMgr()->GetMouseRealPos().x;
				m_rCollider.bottom = CKeyMgr::CreateMgr()->GetMouseRealPos().y;
				m_IS_Render = true;
			}
		}
		else
		{
			if (IS_TAP(LBTN))
			{
				m_rCollider.left = CKeyMgr::CreateMgr()->GetMousePos().x;
				m_rCollider.top = CKeyMgr::CreateMgr()->GetMousePos().y;
				m_IS_Render = false;
			}
			if (IS_RELEASE(LBTN))
			{
				m_rCollider.right = CKeyMgr::CreateMgr()->GetMousePos().x;
				m_rCollider.bottom = CKeyMgr::CreateMgr()->GetMousePos().y;
				m_IS_Render = true;
			}
		}
	}

	if (IS_TAP(ESC))
	{

		m_arrColliderInfo.clear();
		m_COUNT = 0;

		/*for (UINT i = 0; i < MaxCollider; i++)
		{
			m_arrColliderInfo[i].rColliderPos.left = 0;
			m_arrColliderInfo[i].rColliderPos.top = 0;
			m_arrColliderInfo[i].rColliderPos.right = 0;
			m_arrColliderInfo[i].rColliderPos.bottom = 0;
			m_arrColliderInfo[i].eColliderType = COLLIDER_TYPE::NONE;
		}*/
	}
	

	// 현제 작업할 오브젝트를 render해주기 위해 pos를 잡아준다.
	if (dynamic_cast<CBackGround*>(m_vAllObject[m_iCurObject]))
	{
		m_vPos = Vec2(0, 0);
		m_vAllObject[m_iCurObject]->SetPos(m_vPos);
	}
	else
	{
		m_vPos = Vec2(800, 800);
		m_vAllObject[m_iCurObject]->SetPos(m_vPos);
	}
	m_vAllObject[m_iCurObject]->tick();
}

void CToolScene::CreateColldierUI()
{
	// UI 만들기
	Vec2 vResolution = CEngine::CreateMgr()->GetResolution();

	// 패널 UI 만들기
	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetScale(Vec2(400.f, 500.f));
	pPanel->SetPos(Vec2(vResolution.x - pPanel->GetScale().x, 0.f));

	// 닫기 버튼 만들기
	CButtonUI* pButton = new CButtonUI;
	pButton->SetScale(Vec2(25.f, 25.f));
	pButton->SetPos(Vec2(pPanel->GetScale().x - pButton->GetScale().x, 0.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::CloseUI);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonClose"));
	pPanel->AddChildUI(pButton);

	// 버튼 UI 만들기
	// 저장 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 50.f));
	pButton->SetPos(Vec2(50.f, 50.f));
	// 일단 델리게이트 구조로 설계 중
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::ColliderSave);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonSave"));
	pPanel->AddChildUI(pButton);

	//열기 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 50.f));
	pButton->SetPos(Vec2(pPanel->GetScale().x - 50.f - pButton->GetScale().x, 50.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::ColliderLoad);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonLoad"));
	pPanel->AddChildUI(pButton);

	// 콜라이더 타입 정하는 버튼 만들어줌.
		// 디폴트 (25 100 25 100 25 100 25, 20 40)
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(25.f, 120.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SetColliderDef);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonColliderDefualt"));
	pPanel->AddChildUI(pButton);

	// Re-Render
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(150.f, 120.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SetColliderRerender);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonColliderReRender"));
	pPanel->AddChildUI(pButton);

	// Event
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(275.f, 120.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SetColliderEvent);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonColliderEvent"));
	pPanel->AddChildUI(pButton);

	// 콜라이더 셋팅 확인 버튼
	pButton = new CButtonUI;
	pButton->SetScale(Vec2(100.f, 40.f));
	pButton->SetPos(Vec2(25.f, 180.f));
	pButton->SetDeletage(this, (DELEGATE_FUNC)&CToolScene::SetCollider);
	pButton->SetImage(CResourceMgr::CreateMgr()->FindImg(L"ButtonColliderSet"));
	pPanel->AddChildUI(pButton);

	// UI를 씬에 넣어줌
	AddObject(pPanel, LAYER_TYPE::UI);
}

void CToolScene::ColliderSave()
{
	// 콜라이더를 만들 때 전달할 정보 저장
	// 저장할 것, 각 콜라이더의 offset, scale, collidertype

	 // open a file name
	OPENFILENAME ofn = {};

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Collider\0*.collider\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	// 파일 입출력
	FILE* pFile = nullptr;

	// 쓰기 모드로 열기
	_wfopen_s(&pFile, szFilePath, L"wb");

	if (nullptr == pFile)
		return;

	// 콜라이더 정보
	// 전달해야할 것은 콜라이더 offset과 스케일을 배열로 전달한다.

	// 콜라이더 스케일 정보, 포지션 정보를 계산해서 배열에 넣어 보내준다.

	fwrite(&m_COUNT, sizeof(UINT), 1, pFile);
	
	for (UINT i = 0; i < m_arrColliderInfo.size(); ++i)
	{
		Vec2 arrFinalScale = {};
		Vec2 arrFinalOffSet = {};
		COLLIDER_TYPE arrFianlComponentType = {};

		Vec2 realRigthBottom(m_arrColliderInfo[i].rColliderPos.right, m_arrColliderInfo[i].rColliderPos.bottom);
		realRigthBottom = CCameraMgr::CreateMgr()->GetRealPos(realRigthBottom);
		arrFinalScale.x = m_arrColliderInfo[i].rColliderPos.right - m_arrColliderInfo[i].rColliderPos.left;
		arrFinalScale.y = m_arrColliderInfo[i].rColliderPos.bottom - m_arrColliderInfo[i].rColliderPos.top;
		if ((m_vPos.x == 0) && (m_vPos.y == 0))
		{
			arrFinalOffSet.x = (m_arrColliderInfo[i].rColliderPos.right - (arrFinalScale.x / 2));
			arrFinalOffSet.y = (m_arrColliderInfo[i].rColliderPos.bottom - (arrFinalScale.y / 2));
		}
		else
		{
			arrFinalOffSet.x = (realRigthBottom.x - (arrFinalScale.x / 2)) - m_vPos.x;
			arrFinalOffSet.y = (realRigthBottom.y - (arrFinalScale.y / 2)) - m_vPos.y;
		}
		arrFianlComponentType = m_arrColliderInfo[i].eColliderType;
		fwrite(&arrFinalScale, sizeof(Vec2), 1, pFile);
		fwrite(&arrFinalOffSet, sizeof(Vec2), 1, pFile);
		fwrite(&arrFianlComponentType, sizeof(COLLIDER_TYPE), 1, pFile);
	}

	fclose(pFile);
}

void CToolScene::ColliderLoad()
{
	OPENFILENAME ofn = {};

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Collider\0*.collider\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	// 파일 입출력
	FILE* pFile = nullptr;

	// 쓰기 모드로 열기
	_wfopen_s(&pFile, szFilePath, L"wb");

	if (nullptr == pFile)
		return;

	// 콜라이더 정보
	// 전달해야할 것은 콜라이더 offset과 스케일을 배열로 전달한다.

	// 콜라이더 스케일 정보, 포지션 정보를 계산해서 배열에 넣어 보내준다.

	fwrite(&m_COUNT, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < m_arrColliderInfo.size(); ++i)
	{
		Vec2 arrFinalScale = {};
		Vec2 arrFinalOffSet = {};
		COLLIDER_TYPE arrFianlComponentType = {};

		Vec2 realRigthBottom(m_arrColliderInfo[i].rColliderPos.right, m_arrColliderInfo[i].rColliderPos.bottom);
		realRigthBottom = CCameraMgr::CreateMgr()->GetRealPos(realRigthBottom);
		arrFinalScale.x = m_arrColliderInfo[i].rColliderPos.right - m_arrColliderInfo[i].rColliderPos.left;
		arrFinalScale.y = m_arrColliderInfo[i].rColliderPos.bottom - m_arrColliderInfo[i].rColliderPos.top;
		if ((m_vPos.x == 0) && (m_vPos.y == 0))
		{
			arrFinalOffSet.x = (realRigthBottom.x - (arrFinalScale.x / 2));
			arrFinalOffSet.y = (realRigthBottom.y - (arrFinalScale.y / 2));
		}
		else
		{
			arrFinalOffSet.x = (realRigthBottom.x - (arrFinalScale.x / 2)) - m_vPos.x;
			arrFinalOffSet.y = (realRigthBottom.y - (arrFinalScale.y / 2)) - m_vPos.y;
		}
		arrFianlComponentType = m_arrColliderInfo[i].eColliderType;
		fwrite(&arrFinalScale, sizeof(Vec2), 1, pFile);
		fwrite(&arrFinalOffSet, sizeof(Vec2), 1, pFile);
		fwrite(&arrFianlComponentType, sizeof(COLLIDER_TYPE), 1, pFile);
	}

	fclose(pFile);
}

void CToolScene::SetCollider()
{
	tCollider_Info temColliderInfo = {};
	temColliderInfo.rColliderPos = m_rCollider;
	temColliderInfo.eColliderType = m_eColliderType;
	m_arrColliderInfo.push_back(temColliderInfo);
	++m_COUNT;
}