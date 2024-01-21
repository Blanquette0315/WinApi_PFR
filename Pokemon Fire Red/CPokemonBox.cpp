#include "pch.h"
#include "CPokemonBox.h"

#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CBattleMgr.h"
#include "CKeyMgr.h"

#include "CImage.h"
#include "CPokemon.h"
#include "CAnimator.h"

#include "CMenuBox.h"

CPokemonBox::CPokemonBox(CPokemon* _Pokemon)
	: m_pImage(nullptr)
	, m_pTargetImage(nullptr)
	, m_pFont(nullptr)
	, m_pHPbar(nullptr)
	, m_pPokemon(_Pokemon)
	, m_bIS_Target(false)
	, m_bPressEnter(false)
	, m_bAnim(true)
	, m_iIndex(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"PokemonBox");
	m_pTargetImage = CResourceMgr::CreateMgr()->FindImg(L"PokemonBoxTarget");
	m_pFont = CResourceMgr::CreateMgr()->FindImg(L"PokemonBoxFont");
}

CPokemonBox::~CPokemonBox()
{
	if (!(m_pPokemon->IsDead()))
	{
		CEventMgr::CreateMgr()->EventDeleteRe_Render(m_pPokemon);
		m_pPokemon->GetAnimator()->ReSetCurAnim();
	}
}

void CPokemonBox::tick()
{
	// ButtonUI 에서 할 일 작성

	m_pPokemon->tick();

	CUI::tick();

	if (m_bPressEnter)
	{
		AddChildUI(new CMenuBox);
		GetParentUI()->SetISfocus(false);
		GetChildUI()[0]->SetISfocus(true);
		m_bPressEnter = false;
	}
}

void CPokemonBox::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	if (m_bIS_Target)
	{
		AlphaBlend(_dc, vPos.x - m_pTargetImage->GetWidth()
			, vPos.y - m_pTargetImage->GetHeight() + 5
			, m_pTargetImage->GetWidth(), m_pTargetImage->GetHeight()
			, m_pTargetImage->GetDC(), 0, 0, m_pTargetImage->GetWidth(), m_pTargetImage->GetHeight(), tFunc);

	}
	else
	{
		AlphaBlend(_dc, vPos.x - m_pImage->GetWidth()
			, vPos.y - m_pImage->GetHeight()
			, m_pImage->GetWidth(), m_pImage->GetHeight()
			, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
	}

	// 포켓몬 이름 출력
	Vec2 TemNamePos = vPos;
	TemNamePos.x -= 625;
	TemNamePos.y -= 85;

	wstring _msg = m_pPokemon->GetName();

	for (int i = 0; i < _msg.size(); ++i)
	{
		Fint teminfo = LinkText(_msg[i]);

		AlphaBlend(_dc, TemNamePos.x
			, TemNamePos.y
			, teminfo.i3, teminfo.i4
			, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		TemNamePos.x += teminfo.i3;
	}

	// 포켓몬 레벨 출력
	Vec2 TemLvPos = vPos;
	TemLvPos.x -= 510;
	TemLvPos.y -= 40;

	wstring CurLv = std::to_wstring(m_pPokemon->GetCurLV());
	/*wstring _msg = L"";
	if (CurLv.size() == 1)
	{
		_msg
	}*/
	for (int i = 0; i < CurLv.size(); ++i)
	{
		Fint teminfo = LinkText(CurLv[i]);

		AlphaBlend(_dc, TemLvPos.x
			, TemLvPos.y
			, teminfo.i3, teminfo.i4
			, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		TemLvPos.x += teminfo.i3;
	}
	
	// HP 출력

	wstring m_wsHP = L"";
	wstring CurHP = std::to_wstring(m_pPokemon->GetCurHP());
	wstring MaxHP = std::to_wstring(m_pPokemon->GetMaxHP());

	Vec2 TemHPPos = vPos;
	TemHPPos.x -= 200;
	TemHPPos.y -= 40;

	if (CurHP.size() == 1)
	{
		m_wsHP += L"  ";
	}
	else if (CurHP.size() == 2)
	{
		m_wsHP += L" ";
	}
	m_wsHP += CurHP;
	m_wsHP += L"/";

	if (MaxHP.size() == 1)
	{
		m_wsHP += L"  ";
	}
	else if (MaxHP.size() == 2)
	{
		m_wsHP += L" ";
	}
	m_wsHP += MaxHP;

	for (int i = 0; i < m_wsHP.size(); ++i)
	{
		Fint teminfo = LinkText(m_wsHP[i]);
		if (m_wsHP[i] == '/')
		{
			TemHPPos.x += 25;
		}
		else if (m_wsHP[i] == ' ')
		{
			TemHPPos.x += 25;
		}
		else
		{
			AlphaBlend(_dc, TemHPPos.x
				, TemHPPos.y
				, teminfo.i3, teminfo.i4
				, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

			TemHPPos.x += teminfo.i3;
		}
	}

	// HP바
	Vec2 TemHPbarPos = vPos;
	TemHPbarPos.x -= 275;
	TemHPbarPos.y -= 80;
	float HPratio = (float)m_pPokemon->GetCurHP() / (float)m_pPokemon->GetMaxHP();
	if ((1 >= HPratio)
		&& (0.5 < HPratio))
	{
		m_pHPbar = CResourceMgr::CreateMgr()->FindImg(L"PokemonSelectUIHPbarG");
	}
	else if ((0.5 >= HPratio)
		&& (0.25 < HPratio))
	{
		m_pHPbar = CResourceMgr::CreateMgr()->FindImg(L"PokemonSelectUIHPbarY");
	}
	else
	{
		m_pHPbar = CResourceMgr::CreateMgr()->FindImg(L"PokemonSelectUIHPbarR");
	}
	AlphaBlend(_dc, TemHPbarPos.x
		, TemHPbarPos.y
		, (m_pHPbar->GetWidth() * HPratio), m_pHPbar->GetHeight()
		, m_pHPbar->GetDC(), 0, 0, (m_pHPbar->GetWidth() * HPratio), m_pHPbar->GetHeight(), tFunc);

	// 플레이어 포켓몬 UI 에니메이션 진행을 위해 다시 포즈를 잡는다.
	Vec2 TemPokePos = vPos;
	TemPokePos.x -= 683;
	m_pPokemon->SetUIPos(TemPokePos);
	if (m_bAnim)
	{
		CEventMgr::CreateMgr()->Re_Render(m_pPokemon);
		m_bAnim = false;
	}
	

	CUI::render(_dc);
}

bool CPokemonBox::IS_Enter()
{
	m_bPressEnter = true;
	return m_bPressEnter;
}

Fint CPokemonBox::LinkText(char _text)
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
		return Fint(315, 0, 25, 40);
		break;
	}
	case 'K':
	{
		return Fint(350, 0, 25, 40);
		break;
	}
	case 'L':
	{
		return Fint(385, 0, 25, 40);
		break;
	}
	case 'M':
	{
		return Fint(420, 0, 25, 40);
		break;
	}
	case 'N':
	{
		return Fint(0, 50, 25, 40);
		break;
	}
	case 'O':
	{
		return Fint(35, 50, 25, 40);
		break;
	}
	case 'P':
	{
		return Fint(70, 50, 25, 40);
		break;
	}
	case 'Q':
	{
		return Fint(105, 50, 25, 40);
		break;
	}
	case 'R':
	{
		return Fint(140, 50, 25, 40);
		break;
	}
	case 'S':
	{
		return Fint(175, 50, 25, 40);
		break;
	}
	case 'T':
	{
		return Fint(210, 50, 20, 40);
		break;
	}
	case 'U':
	{
		return Fint(245, 50, 25, 40);
		break;
	}
	case 'V':
	{
		return Fint(280, 50, 25, 40);
		break;
	}
	case 'W':
	{
		return Fint(315, 50, 25, 40);
		break;
	}
	case 'X':
	{
		return Fint(350, 50, 25, 40);
		break;
	}
	case 'Y':
	{
		return Fint(385, 50, 20, 40);
		break;
	}
	case 'Z':
	{
		return Fint(420, 50, 25, 40);
		break;
	}

	// 숫자
	case '0':
	{
		return Fint(615, 50, 25, 40);
		break;
	}
	case '1':
	{
		return Fint(475, 0, 20, 40);
		break;
	}
	case '2':
	{
		return Fint(510, 0, 25, 40);
		break;
	}
	case '3':
	{
		return Fint(545, 0, 25, 40);
		break;
	}
	case '4':
	{
		return Fint(580, 0, 25, 40);
		break;
	}
	case '5':
	{
		return Fint(615, 0, 25, 40);
		break;
	}
	case '6':
	{
		return Fint(475, 50, 25, 40);
		break;
	}
	case '7':
	{
		return Fint(510, 50, 25, 40);
		break;
	}
	case '8':
	{
		return Fint(545, 50, 25, 40);
		break;
	}
	case '9':
	{
		return Fint(580, 50, 25, 40);
		break;
	}
	default:
		break;
	}
}

void CPokemonBox::GetShiftPokemon()
{
	CBattleMgr::CreateMgr()->ShiftPokemon(m_iIndex);
}
