#include "pch.h"
#include "CMenuUI.h"

#include "CSceneMgr.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"

#include "CImage.h"
#include "CScene.h"

CMenuUI::CMenuUI()
	: m_pImage(nullptr)
	, m_vecChildUI{}
	, m_CurMenuType(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Menu");
}

CMenuUI::~CMenuUI()
{
}

void CMenuUI::tick()
{

	m_vecChildUI = GetChildUI();
	// S키를 누르면 목차가 위로 이동한다.
	if (IS_TAP(S) && (m_CurMenuType < (UINT)MENU_TYPE::CLOSE))
	{
		Vec2 vPos = m_vecChildUI[0]->GetPos();
		vPos += Vec2(0.f, 64.f);
		m_vecChildUI[0]->SetPos(vPos);
		m_CurMenuType++;
	}
	// W키를 누르면 목차가 아래로 이동한다.
	else if (IS_TAP(W) && (m_CurMenuType > (UINT)MENU_TYPE::POKEMON))
	{
		Vec2 vPos = m_vecChildUI[0]->GetPos();
		vPos -= Vec2(0.f, 64.f);
		m_vecChildUI[0]->SetPos(vPos);
		m_CurMenuType--;
	}
	// 앤터 키를 누르면 지금 화살표가 가리키고 있는 UIScene으로 바꿔준다.
	else if (IS_TAP(ENTER))
	{
		switch (m_CurMenuType)
		{
		case (UINT)MENU_TYPE::POKEMON:
		{

			//CSceneMgr::CreateMgr()->GetCurScene()->SetMenuOn(false);
			break;
		}
		case (UINT)MENU_TYPE::BAG:
		{
			// 여기서 가방 UI를 생성해주지 말고, SceneMgr나 Scene에 접근해서 가방 UI 생성하는 함수를 실행해주자.
			// 그러면 가방 UI가 생성이 되고 메뉴는 삭제되며, Scene의 tick과 render를 돌때 가방 UI가 동작할 것이다.
			// 이후 가방쪽과 Scene쪽에서 UI를 삭제해주면 된다.
			CSceneMgr::CreateMgr()->GetCurScene()->NewBackPackUI();

			//EventDeleteObject(this);
			//CSceneMgr::CreateMgr()->GetCurScene()->SetMenuOn(false);
			break;
		}
		case (UINT)MENU_TYPE::CLOSE:
		{
			EventDeleteObject(this);
			CSceneMgr::CreateMgr()->GetCurScene()->SetMenuOn(false);
			break;
		}
		}

	}
	// 자식 UI의 tick을 실행시켜준다.
	//CUI::tick();
}

void CMenuUI::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (int)vPos.x
		, (int)vPos.y
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);

	CUI::render(_dc);
}