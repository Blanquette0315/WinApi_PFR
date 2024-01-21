#include "pch.h"
#include "CMonsterInfoBox.h"

#include "CResourceMgr.h"

#include "CImage.h"

CMonsterInfoBox::CMonsterInfoBox()
	: m_pImage(nullptr)
	, m_Font(nullptr)
	, m_wsName{}
	, m_MaxHP(0)
	, m_CurHP(0)
	, m_Level(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"MonsterInfoBox");
	m_Font = CResourceMgr::CreateMgr()->FindImg(L"InfoBoxFont");
	m_HPbar = CResourceMgr::CreateMgr()->FindImg(L"GreenHPbar");
}

CMonsterInfoBox::~CMonsterInfoBox()
{
}

void CMonsterInfoBox::tick()
{
	// 텍스트 띄우는 코드가 들어가야 한다.

	CUI::tick();
}

void CMonsterInfoBox::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	if (m_pImage)
	{
		AlphaBlend(_dc, vPos.x
			, vPos.y
			, m_pImage->GetWidth(), m_pImage->GetHeight()
			, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
	}

	// 이름 출력

	Vec2 TemNamePos = vPos;
	TemNamePos.x += 35;
	TemNamePos.y += 25;

	for (int i = 0; i < m_wsName.size(); ++i)
	{
		Fint teminfo = LinkText(m_wsName[i]);

		AlphaBlend(_dc, TemNamePos.x
			, TemNamePos.y
			, teminfo.i3, teminfo.i4
			, m_Font->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		TemNamePos.x += teminfo.i3;
	}

	// 레벨 출력

	wstring m_wsLevel = L"Lv";
	m_wsLevel += std::to_wstring(m_Level);

	Vec2 TemLevelPos = vPos;
	TemLevelPos.x += 315;
	TemLevelPos.y += 25;
	if (std::to_wstring(m_Level).size() == 1)
	{
		TemLevelPos.x += 50;
	}
	else if (std::to_wstring(m_Level).size() == 2)
	{
		TemLevelPos.x += 25;
	}

	for (int i = 0; i < m_wsLevel.size(); ++i)
	{
		Fint teminfo = LinkText(m_wsLevel[i]);

		AlphaBlend(_dc, TemLevelPos.x
			, TemLevelPos.y
			, teminfo.i3, teminfo.i4
			, m_Font->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		TemLevelPos.x += teminfo.i3;
	}

	// 체력 바

	Vec2 TemHPbarPos = vPos;
	TemHPbarPos.x += 190;
	TemHPbarPos.y += 80;
	float HPratio = (float)m_CurHP / (float)m_MaxHP;
	if ((1 >= HPratio)
		&& (0.5 < HPratio))
	{
		m_HPbar = CResourceMgr::CreateMgr()->FindImg(L"GreenHPbar");
	}
	else if ((0.5 >= HPratio)
		&& (0.25 < HPratio))
	{
		m_HPbar = CResourceMgr::CreateMgr()->FindImg(L"YellowHPbar");
	}
	else
	{
		m_HPbar = CResourceMgr::CreateMgr()->FindImg(L"RedHPbar");
	}
	AlphaBlend(_dc, TemHPbarPos.x
		, TemHPbarPos.y
		, (m_HPbar->GetWidth() * HPratio), m_HPbar->GetHeight()
		, m_HPbar->GetDC(), 0, 0, (m_HPbar->GetWidth() * HPratio), m_HPbar->GetHeight(), tFunc);

	CUI::render(_dc);
}

Fint CMonsterInfoBox::LinkText(char _text)
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
		return Fint(0, 100, 25, 40);
		break;
	}
	case '1':
	{
		return Fint(40, 100, 20, 40);
		break;
	}
	case '2':
	{
		return Fint(70, 100, 25, 40);
		break;
	}
	case '3':
	{
		return Fint(105, 100, 25, 40);
		break;
	}
	case '4':
	{
		return Fint(140, 100, 25, 40);
		break;
	}
	case '5':
	{
		return Fint(175, 100, 25, 40);
		break;
	}
	case '6':
	{
		return Fint(210, 100, 25, 40);
		break;
	}
	case '7':
	{
		return Fint(245, 100, 25, 40);
		break;
	}
	case '8':
	{
		return Fint(280, 100, 25, 40);
		break;
	}
	case '9':
	{
		return Fint(315, 100, 25, 40);
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
		return Fint(130, 155, 25, 45);
		break;
	}

	default:
		break;
	}
}