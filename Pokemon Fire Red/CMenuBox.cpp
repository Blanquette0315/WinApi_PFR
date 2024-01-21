#include "pch.h"
#include "CMenuBox.h"

#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CBattleMgr.h"

#include "CImage.h"
#include "CSound.h"

#include "CMenuArrow.h"

CMenuBox::CMenuBox()
	: m_pImage(nullptr)
	, m_iMenuType(0) // 0이 Shift, 1이 cancel
	, m_bIS_Target(false)
	, m_pFont(nullptr)
	, m_pSound(nullptr)
	, m_wShift(L"SHIFT")
	, m_wCancel(L"CANCEL")
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"MenuBox");
	m_pFont = CResourceMgr::CreateMgr()->FindImg(L"BattleBoxFont");
	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"SelectSound");

	SetPos(Vec2(885, 560));

	AddChildUI(new CMenuArrow);
	Vec2 ArrowPos = GetPos();
	ArrowPos += Vec2(30, 55);
	GetChildUI()[0]->SetPos(ArrowPos);
	CEventMgr::CreateMgr()->Re_Render(this);
}

CMenuBox::~CMenuBox()
{
	CEventMgr::CreateMgr()->EventDeleteRe_Render(this);
}

void CMenuBox::tick()
{
	if (m_bIS_Target)
	{
		if (IS_TAP(W) && (m_iMenuType == 1))
		{
			m_pSound->Play(false);
			Vec2 vPos = GetChildUI()[0]->GetPos();
			vPos -= Vec2(0.f, 80.f);
			GetChildUI()[0]->SetPos(vPos);
			
			m_iMenuType = 0;
		}
		else if (IS_TAP(S) && (m_iMenuType == 0))
		{
			m_pSound->Play(false);
			Vec2 vPos = GetChildUI()[0]->GetPos();
			vPos += Vec2(0.f, 80.f);
			GetChildUI()[0]->SetPos(vPos);

			m_iMenuType = 1;
		}
		else if (IS_TAP(ENTER))
		{
			if (m_iMenuType == 0)
			{
				CBattleMgr::CreateMgr()->SetBattle_Type(BATTLE_TYPE::POKEMONSHIFT);
				GetParentUI()->GetShiftPokemon();

				EventDeleteObject((GetParentUI()->GetParentUI()->GetParentUI()));
			}
			else if (m_iMenuType == 1)
			{
				GetParentUI()->EraseChildUI();
				GetParentUI()->SetISfocus(true);
				GetParentUI()->GetParentUI()->SetISfocus(true);
				EventDeleteObject(this);
			}
		}
	}
	

	CUI::tick();
}

void CMenuBox::render(HDC _dc)
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


	Vec2 CancelPos = GetPos();
	CancelPos.x += 60;
	CancelPos.y += 55;

	for (int i = 0; i < m_wShift.size(); ++i)
	{
		Fint teminfo = LinkText(m_wShift[i]);

		AlphaBlend(_dc, CancelPos.x
			, CancelPos.y
			, teminfo.i3, teminfo.i4
			, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		CancelPos.x += teminfo.i3;
	}

	Vec2 ShiftPos = GetPos();
	ShiftPos.x += 60;
	ShiftPos.y += 135;

	for (int i = 0; i < m_wCancel.size(); ++i)
	{
		Fint teminfo = LinkText(m_wCancel[i]);

		AlphaBlend(_dc, ShiftPos.x
			, ShiftPos.y
			, teminfo.i3, teminfo.i4
			, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		ShiftPos.x += teminfo.i3;
	}

	CUI::render(_dc);
}


Fint CMenuBox::LinkText(char _text)
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

	default:
		break;
	}
}