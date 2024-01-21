#include "pch.h"
#include "CPlayerActionBox.h"

#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CEventMgr.h"
#include "CBattleMgr.h"

#include "CImage.h"
#include "CSound.h"

#include "CBattleBox.h"
#include "CBoxArrow.h"
#include "CPokemonSelectBox.h"

CPlayerActionBox::CPlayerActionBox()
	: m_pImage(nullptr)
	, m_pSound(nullptr)
	, m_vecChildUI{}
	, m_CurMenuType(PLAYER_ACTION_TYPE::FIGHT)
	, m_ISfocus(true)
	, m_targetPokemon(nullptr)
	, m_Skillinfo{}
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"PlayerActionBox");
	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"SelectSound");
}

CPlayerActionBox::CPlayerActionBox(CPokemon* _Object, CObject* _player)
	: m_pImage(nullptr)
	, m_pSound(nullptr)
	, m_vecChildUI{}
	, m_CurMenuType(PLAYER_ACTION_TYPE::FIGHT)
	, m_ISfocus(true)
	, m_targetPokemon(_Object)
	, m_Skillinfo{}
	,m_pPlayer(_player)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"PlayerActionBox");
	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"SelectSound");

	AddChildUI(new CBoxArrow);
	GetChildUI()[0]->SetPos(Vec2(645.f, 620.f));
}

CPlayerActionBox::~CPlayerActionBox()
{
}

void CPlayerActionBox::tick()
{
	if (m_ISfocus)
	{
		m_vecChildUI = GetChildUI();
		// S키를 누르면 목차가 위로 이동한다.
		if (IS_TAP(S))
		{
			if (m_CurMenuType == PLAYER_ACTION_TYPE::FIGHT)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos += Vec2(0.f, 80.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = PLAYER_ACTION_TYPE::POKEMON;
			}
			else if (m_CurMenuType == PLAYER_ACTION_TYPE::BAG)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos += Vec2(0.f, 80.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = PLAYER_ACTION_TYPE::RUN;
			}
		}
		// W키를 누르면 목차가 아래로 이동한다.
		else if (IS_TAP(W))
		{
			if (m_CurMenuType == PLAYER_ACTION_TYPE::POKEMON)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos -= Vec2(0.f, 80.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = PLAYER_ACTION_TYPE::FIGHT;
			}
			else if (m_CurMenuType == PLAYER_ACTION_TYPE::RUN)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos -= Vec2(0.f, 80.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = PLAYER_ACTION_TYPE::BAG;
			}
		}
		else if (IS_TAP(D))
		{
			if (m_CurMenuType == PLAYER_ACTION_TYPE::FIGHT)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos += Vec2(280.f, 0.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = PLAYER_ACTION_TYPE::BAG;
			}
			else if (m_CurMenuType == PLAYER_ACTION_TYPE::POKEMON)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos += Vec2(280.f, 0.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = PLAYER_ACTION_TYPE::RUN;
			}
		}
		else if (IS_TAP(A))
		{
			if (m_CurMenuType == PLAYER_ACTION_TYPE::BAG)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos -= Vec2(280.f, 0.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = PLAYER_ACTION_TYPE::FIGHT;
			}
			else if (m_CurMenuType == PLAYER_ACTION_TYPE::RUN)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos -= Vec2(280.f, 0.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = PLAYER_ACTION_TYPE::POKEMON;
			}
		}
		// 앤터 키를 누르면 지금 화살표가 가리키고 있는 기능을 수행시켜준다.
		else if (IS_TAP(ENTER))
		{
			switch (m_CurMenuType)
			{
			case PLAYER_ACTION_TYPE::FIGHT:
			{
				m_ISfocus = false;
				AddChildUI(new CBattleBox(m_targetPokemon));
				GetChildUI()[1]->SetOwnerUI(this);
				CEventMgr::CreateMgr()->EventSetUIFocus(GetChildUI()[1]);
				break;
			}
			case PLAYER_ACTION_TYPE::BAG:
			{
				break;
			}
			case PLAYER_ACTION_TYPE::POKEMON:
			{
				m_ISfocus = false;
				AddChildUI(new CPokemonSelectBox(m_pPlayer));
				GetChildUI()[1]->SetPos(Vec2(0, 0));
				GetChildUI()[1]->SetISfocus(true);
				break;
			}
			case PLAYER_ACTION_TYPE::RUN:
			{
				CBattleMgr::CreateMgr()->SetRunRand();
				CBattleMgr::CreateMgr()->Run();
				EventDeleteObject(this);
				break;
			}
			}
		}
	}

	CUI::tick();
}

void CPlayerActionBox::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	if (m_pImage)
	{
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = AC_SRC_ALPHA;
		tFunc.SourceConstantAlpha = 255;

		AlphaBlend(_dc, vPos.x
			, vPos.y
			, m_pImage->GetWidth(), m_pImage->GetHeight()
			, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
	}


	CUI::render(_dc);
}