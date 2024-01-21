#include "pch.h"
#include "CPokemonSelectBox.h"

#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CBattleMgr.h"
#include "CSceneMgr.h"

#include "CCurPokemonBox.h"
#include "CPokemonBox.h"
#include "CCancelBox.h"

#include "CImage.h"
#include "CSound.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CPokemon.h"

CPokemonSelectBox::CPokemonSelectBox(CObject* _player)
	: m_pImage(nullptr)
	, m_pFont(nullptr)
	, m_pSound(nullptr)
	, m_eCurMenuType(POKETMONSELECT_TYPE::POKEMON1)
	, m_pPlayer(_player)
	, m_iCurTargetUI(0)
	, m_iPrevTargetUI(0)
	, m_iPokemonSize(0)
	, m_ISfocus(false)
	, m_eMsgType(SELECTPOKEMON_MSG_TYPE::DEF)
	, m_wMsg(L"")
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"PokemonSelectUI");
	m_pFont = CResourceMgr::CreateMgr()->FindImg(L"BattleBoxFont");
	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"SelectSound");

	Vec2 PoekmonBoxPos = Vec2(1190, 160);

	m_iPokemonSize = m_pPlayer->GetNowPokemonSize();

	// 플레이어 포켓몬 SceneType을 UI로 바꿔준다.
	m_pPlayer->GetNowPokemon(0)->SetPokSceneType(POKEMONSCENE_TYPE::UI);
	m_pPlayer->GetNowPokemon(0)->SetUIPrevPos();
	for (int i = 1; i < m_iPokemonSize; ++i)
	{
		m_pPlayer->GetNowPokemon(i)->SetPokSceneType(POKEMONSCENE_TYPE::UI);
		m_pPlayer->GetNowPokemon(i)->SetUIPrevPos();
	}

	if(!(m_iPokemonSize == 0))
	{
		AddChildUI(new CCurPokemonBox(CBattleMgr::CreateMgr()->GetVecPokemon(0)));
		GetChildUI()[0]->SetPos(Vec2(430, 375));
		GetChildUI()[0]->SetISfocus(true);
		m_iCurTargetUI = (UINT)m_eCurMenuType;
		m_iPrevTargetUI = m_iCurTargetUI;

		for (int i = 1; i < m_iPokemonSize; ++i)
		{
			if (!(i == 1))
			{
				PoekmonBoxPos.y += 120;
			}

			AddChildUI(new CPokemonBox(CBattleMgr::CreateMgr()->GetVecPokemon(i)));
			GetChildUI()[i]->SetPos(PoekmonBoxPos);
			GetChildUI()[i]->SetIndex(i);
		}

		AddChildUI(new CCancelBox);
		GetChildUI()[m_iPokemonSize]->SetPos(Vec2(1190, 770));
	}
}

CPokemonSelectBox::~CPokemonSelectBox()
{
	// 플레이어 포켓몬 SceneType을 Battle로 바꿔준다.
	if ((!m_pPlayer->IsDead()))
	{
		//CSceneMgr::CreateMgr()->GetPokemon(0)->SetPokSceneType(POKEMONSCENE_TYPE::BATTLE);
		//CSceneMgr::CreateMgr()->GetPokemon(0)->SetPos(m_pPlayer->GetNowPokemon(0)->GetUIPrevPos());
		m_pPlayer->GetNowPokemon(0)->SetPokSceneType(POKEMONSCENE_TYPE::BATTLE);
		m_pPlayer->GetNowPokemon(0)->SetPos(m_pPlayer->GetNowPokemon(0)->GetUIPrevPos());
		m_pPlayer->GetNowPokemon(0)->SetIOType(POKEMON_IO_TYPE::e_NONE);

		for (int i = 1; i < m_iPokemonSize; ++i)
		{
			m_pPlayer->GetNowPokemon(i)->SetPokSceneType(POKEMONSCENE_TYPE::BATTLE);
			m_pPlayer->GetNowPokemon(i)->SetPos(m_pPlayer->GetNowPokemon(i)->GetUIPrevPos());
		}
	}
}

void CPokemonSelectBox::tick()
{
	// ButtonUI 에서 할 일 작성
	if (m_ISfocus)
	{
		if (IS_TAP(D))
		{
			if ((m_iPokemonSize > m_iCurTargetUI)
				&& (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON1))
			{
				m_pSound->Play(false);
				m_iPrevTargetUI = m_iCurTargetUI;
				m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON2;
			}
		}
		else if (IS_TAP(A))
		{
			if ((m_iPokemonSize > m_iCurTargetUI)
				&& !(m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON1))
			{
				m_pSound->Play(false);
				m_iPrevTargetUI = m_iCurTargetUI;
				m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON1;
			}
		}
		else if (IS_TAP(W))
		{
			if ((m_iPokemonSize >= m_iCurTargetUI)
				&& !(m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON2))
			{
				if (m_eCurMenuType == POKETMONSELECT_TYPE::CANCLE)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON6;
				}
				else if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON6)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON5;
				}
				else if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON5)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON4;
				}
				else if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON4)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON3;
				}
				else if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON3)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON2;
				}
			}
		}

		else if (IS_TAP(S))
		{
			if ((m_iPokemonSize > m_iCurTargetUI)
				&& !(m_eCurMenuType == POKETMONSELECT_TYPE::CANCLE))
			{
				if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON2)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON3;
				}
				else if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON3)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON4;
				}
				else if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON4)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON5;
				}
				else if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON5)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::POKEMON6;
				}
				else if (m_eCurMenuType == POKETMONSELECT_TYPE::POKEMON6)
				{
					m_pSound->Play(false);
					m_iPrevTargetUI = m_iCurTargetUI;
					m_eCurMenuType = POKETMONSELECT_TYPE::CANCLE;
				}
			}
		}

		m_iCurTargetUI = (UINT)m_eCurMenuType;

		if ((m_iPrevTargetUI == 0)
			&& (m_iCurTargetUI == 0))
		{
		}
		else
		{
			GetChildUI()[m_iPrevTargetUI]->SetISfocus(false);
		}

		GetChildUI()[m_iCurTargetUI]->SetISfocus(true);

		if (m_iCurTargetUI == m_iPokemonSize)
		{
			m_eMsgType = SELECTPOKEMON_MSG_TYPE::CANCEL;
		}
		else
		{
			m_eMsgType = SELECTPOKEMON_MSG_TYPE::DEF;
		}

		if (IS_TAP(ENTER))
		{
			if (m_iCurTargetUI == m_iPokemonSize)
			{
				GetParentUI()->EraseChildUI();
				GetParentUI()->SetISfocus(true);
				EventDeleteObject(this);
			}
			else
			{
				GetChildUI()[m_iCurTargetUI]->IS_Enter();
				m_eMsgType = SELECTPOKEMON_MSG_TYPE::MENUON;
			}
		}
	}
	

	CUI::tick();
}

void CPokemonSelectBox::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, vPos.x
		, vPos.y
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);


	// text 출력

	Vec2 MsgPos = GetPos();
	MsgPos.x += 60;
	MsgPos.y += 700;

	if (m_eMsgType == SELECTPOKEMON_MSG_TYPE::DEF)
	{
		m_wMsg = L"Choose a POKEMON.";
	}
	else if (m_eMsgType == SELECTPOKEMON_MSG_TYPE::MENUON)
	{
		m_wMsg = L"Do What with this POKEMON?";
	}
	else if (m_eMsgType == SELECTPOKEMON_MSG_TYPE::CANCEL)
	{
		m_wMsg = L"Cancel?";
	}

	for (int i = 0; i < m_wMsg.size(); ++i)
	{
		Fint teminfo = LinkText(m_wMsg[i]);

		AlphaBlend(_dc, MsgPos.x
			, MsgPos.y
			, teminfo.i3, teminfo.i4
			, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		MsgPos.x += teminfo.i3;
	}

	CUI::render(_dc);
}

Fint CPokemonSelectBox::LinkText(char _text)
{
	switch (_text)
	{
	case 'A':
	{
		return Fint(0, 0, 25, 40);
		break;
	}
	case 'B':
	{
		return Fint(35, 0, 25, 40);
		break;
	}
	case 'C':
	{
		return Fint(70, 0, 25, 40);
		break;
	}
	case 'D':
	{
		return Fint(105, 0, 25, 40);
		break;
	}
	case 'E':
	{
		return Fint(140, 0, 25, 40);
		break;
	}
	case 'F':
	{
		return Fint(175, 0, 25, 40);
		break;
	}
	case 'G':
	{
		return Fint(210, 0, 25, 40);
		break;
	}
	case 'H':
	{
		return Fint(245, 0, 25, 40);
		break;
	}
	case 'I':
	{
		return Fint(280, 0, 20, 40);
		break;
	}
	case 'J':
	{
		return Fint(310, 0, 25, 40);
		break;
	}
	case 'K':
	{
		return Fint(345, 0, 25, 40);
		break;
	}
	case 'L':
	{
		return Fint(380, 0, 25, 40);
		break;
	}
	case 'M':
	{
		return Fint(415, 0, 25, 40);
		break;
	}
	case 'N':
	{
		return Fint(450, 0, 25, 40);
		break;
	}
	case 'O':
	{
		return Fint(485, 0, 25, 40);
		break;
	}
	case 'P':
	{
		return Fint(520, 0, 25, 40);
		break;
	}
	case 'Q':
	{
		return Fint(555, 0, 25, 40);
		break;
	}
	case 'R':
	{
		return Fint(590, 0, 25, 40);
		break;
	}
	case 'S':
	{
		return Fint(625, 0, 25, 40);
		break;
	}
	case 'T':
	{
		return Fint(660, 0, 20, 40);
		break;
	}
	case 'U':
	{
		return Fint(690, 0, 25, 40);
		break;
	}
	case 'V':
	{
		return Fint(725, 0, 25, 40);
		break;
	}
	case 'W':
	{
		return Fint(760, 0, 25, 40);
		break;
	}
	case 'X':
	{
		return Fint(795, 0, 25, 40);
		break;
	}
	case 'Y':
	{
		return Fint(830, 0, 20, 40);
		break;
	}
	case 'Z':
	{
		return Fint(860, 0, 25, 40);
		break;
	}

	// 소문자
	case 'a':
	{
		return Fint(0, 50, 25, 40);
		break;
	}
	case 'b':
	{
		return Fint(35, 50, 25, 40);
		break;
	}
	case 'c':
	{
		return Fint(70, 50, 25, 40);
		break;
	}
	case 'd':
	{
		return Fint(105, 50, 25, 40);
		break;
	}
	case 'e':
	{
		return Fint(140, 50, 25, 40);
		break;
	}
	case 'f':
	{
		return Fint(175, 50, 25, 40);
		break;
	}
	case 'g':
	{
		return Fint(210, 50, 25, 45);
		break;
	}
	case 'h':
	{
		return Fint(245, 50, 25, 40);
		break;
	}
	case 'i':
	{
		return Fint(285, 50, 10, 40);
		break;
	}
	case 'j':
	{
		return Fint(305, 50, 20, 40);
		break;
	}
	case 'k':
	{
		return Fint(340, 50, 25, 40);
		break;
	}
	case 'l':
	{
		return Fint(380, 50, 15, 40);
		break;
	}
	case 'm':
	{
		return Fint(410, 50, 25, 40);
		break;
	}
	case 'n':
	{
		return Fint(445, 50, 25, 40);
		break;
	}
	case 'o':
	{
		return Fint(480, 50, 25, 40);
		break;
	}
	case 'p':
	{
		return Fint(515, 50, 20, 45);
		break;
	}
	case 'q':
	{
		return Fint(545, 50, 25, 45);
		break;
	}
	case 'r':
	{
		return Fint(580, 50, 25, 40);
		break;
	}
	case 's':
	{
		return Fint(615, 50, 25, 40);
		break;
	}
	case 't':
	{
		return Fint(650, 50, 25, 40);
		break;
	}
	case 'u':
	{
		return Fint(685, 50, 25, 40);
		break;
	}
	case 'v':
	{
		return Fint(720, 50, 25, 40);
		break;
	}
	case 'w':
	{
		return Fint(755, 50, 25, 40);
		break;
	}
	case 'x':
	{
		return Fint(790, 50, 25, 40);
		break;
	}
	case 'y':
	{
		return Fint(825, 50, 25, 45);
		break;
	}
	case 'z':
	{
		return Fint(860, 50, 25, 40);
		break;
	}

	// 숫자
	case '0':
	{
		return Fint(0, 0, 30, 48);
		break;
	}
	case '1':
	{
		return Fint(33, 0, 30, 48);
		break;
	}
	case '2':
	{
		return Fint(66, 0, 30, 48);
		break;
	}
	case '3':
	{
		return Fint(102, 0, 30, 48);
		break;
	}
	case '4':
	{
		return Fint(138, 0, 30, 48);
		break;
	}
	case '5':
	{
		return Fint(174, 0, 30, 48);
		break;
	}
	case '6':
	{
		return Fint(210, 0, 30, 48);
		break;
	}
	case '7':
	{
		return Fint(246, 0, 30, 48);
		break;
	}
	case '8':
	{
		return Fint(282, 0, 30, 48);
		break;
	}
	case '9':
	{
		return Fint(318, 0, 30, 48);
		break;
	}

	// 특수 문자
	case ' ':
	{
		return Fint(550, 100, 25, 45);
		break;
	}
	case '/':
	{
		return Fint(354, 0, 30, 55);
		break;
	}

	case '-':
	{
		return Fint(165, 160, 25, 40);
		break;
	}

	case '?':
	{
		return Fint(25, 160, 25, 40);
		break;
	}

	case '.':
	{
		return Fint(200, 160, 10, 40);
		break;
	}

	default:
		break;
	}
}