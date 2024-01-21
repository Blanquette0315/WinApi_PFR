#include "pch.h"
#include "CBattleMessageBox.h"

#include "CResourceMgr.h"
#include "CKeyMgr.h"

#include "CImage.h"
#include "CSound.h"

CBattleMessageBox::CBattleMessageBox()
	: m_pImage(nullptr)
	, m_pEnterSound(nullptr)
	, m_Font(nullptr)
	, m_arrMessage{}
	, m_HaveText(false)
	, m_Tick(0)
	, m_fDuration(0)
	, m_bEndMessage(false)
	, m_bPressEnter(false)
	, m_bEndSwich(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BattleMessageBox"); 
	m_Font = CResourceMgr::CreateMgr()->FindImg(L"BattleMessageFontTable");
	m_pEnterSound = CResourceMgr::CreateMgr()->FindSound(L"SelectSound");
}

CBattleMessageBox::~CBattleMessageBox()
{
}

void CBattleMessageBox::tick()
{
	if (IS_TAP(ENTER))
	{
		m_bPressEnter = true;
		m_pEnterSound->Play(false);
	}


	CUI::tick();
}

void CBattleMessageBox::render(HDC _dc)
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

	if (m_HaveText)
	{
		Vec2 TextPos = vPos;
		TextPos.x += 50;
		TextPos.y += 65;

		float a = 0.5 / m_arrMessage.size();
		m_fDuration += DT;

		if ((m_fDuration > a) && (m_Tick < m_arrMessage.size()))
		{
			m_Tick++;
			m_fDuration = 0;
			m_bEndSwich = true;
		}

		else if ((m_bEndSwich == true) && (m_Tick >= m_arrMessage.size()))
		{
			m_bEndSwich = false;
			m_bEndMessage = true;
		}

		for (int i = 0; i < m_Tick; i++)
		{
			if (m_arrMessage[i] == '@')
			{
				TextPos = vPos;
				TextPos.x += 50;
				TextPos.y += 65;
				TextPos.y += 80;
			}
			else
			{
				Vec2 TemPos = LinkText(m_arrMessage[i]);
				if (m_arrMessage[i] == '?')
					TextPos.y -= 10;
				else if (m_arrMessage[i] == '!')
					TextPos.y -= 10;
				else if (m_arrMessage[i] == ',')
					TextPos.y += 10;

				AlphaBlend(_dc, TextPos.x
					, TextPos.y
					, 30, 55
					, m_Font->GetDC(), TemPos.x, TemPos.y, 30, 55, tFunc);

				if (m_arrMessage[i] == '?')
					TextPos.y += 10;
				else if (m_arrMessage[i] == '!')
					TextPos.y += 10;
				else if (m_arrMessage[i] == ',')
					TextPos.y -= 10;

				TextPos.x += 30;
			}
		}
	}

	CUI::render(_dc);
}

void CBattleMessageBox::SetText(const wstring& _str)
{
	m_HaveText = true;
	m_arrMessage = _str;
}


Vec2 CBattleMessageBox::LinkText(char _text)
{
	switch (_text)
	{
	case 'A':
	{
		return Vec2(70, 25);
		break;
	}
	case 'B':
	{
		return Vec2(130, 25);
		break;
	}
	case 'C':
	{
		return Vec2(190, 25);
		break;
	}
	case 'D':
	{
		return Vec2(350, 25);
		break;
	}
	case 'E':
	{
		return Vec2(410, 25);
		break;
	}
	case 'F':
	{
		return Vec2(470, 25);
		break;
	}
	case 'G':
	{
		return Vec2(70, 105);
		break;
	}
	case 'H':
	{
		return Vec2(130, 105);
		break;
	}
	case 'I':
	{
		return Vec2(190, 105);
		break;
	}
	case 'J':
	{
		return Vec2(350, 105);
		break;
	}
	case 'K':
	{
		return Vec2(410, 105);
		break;
	}
	case 'L':
	{
		return Vec2(470, 105);
		break;
	}
	case 'M':
	{
		return Vec2(70, 185);
		break;
	}
	case 'N':
	{
		return Vec2(130, 185);
		break;
	}
	case 'O':
	{
		return Vec2(190, 185);
		break;
	}
	case 'P':
	{
		return Vec2(350, 185);
		break;
	}
	case 'Q':
	{
		return Vec2(410, 185);
		break;
	}
	case 'R':
	{
		return Vec2(470, 185);
		break;
	}
	case 'S':
	{
		return Vec2(530, 185);
		break;
	}
	case 'T':
	{
		return Vec2(70, 265);
		break;
	}
	case 'U':
	{
		return Vec2(130, 265);
		break;
	}
	case 'V':
	{
		return Vec2(190, 265);
		break;
	}
	case 'W':
	{
		return Vec2(350, 265);
		break;
	}
	case 'X':
	{
		return Vec2(410, 265);
		break;
	}
	case 'Y':
	{
		return Vec2(470, 265);
		break;
	}
	case 'Z':
	{
		return Vec2(530, 265);
		break;
	}

	// ¼Ò¹®ÀÚ
	case 'a':
	{
		return Vec2(70, 375);
		break;
	}
	case 'b':
	{
		return Vec2(130, 375);
		break;
	}
	case 'c':
	{
		return Vec2(190, 375);
		break;
	}
	case 'd':
	{
		return Vec2(350, 375);
		break;
	}
	case 'e':
	{
		return Vec2(410, 375);
		break;
	}
	case 'f':
	{
		return Vec2(470, 375);
		break;
	}
	case 'g':
	{
		return Vec2(70, 455);
		break;
	}
	case 'h':
	{
		return Vec2(130, 455);
		break;
	}
	case 'i':
	{
		return Vec2(190, 455);
		break;
	}
	case 'j':
	{
		return Vec2(350, 455);
		break;
	}
	case 'k':
	{
		return Vec2(410, 455);
		break;
	}
	case 'l':
	{
		return Vec2(470, 455);
		break;
	}
	case 'm':
	{
		return Vec2(70, 535);
		break;
	}
	case 'n':
	{
		return Vec2(130, 535);
		break;
	}
	case 'o':
	{
		return Vec2(190, 535);
		break;
	}
	case 'p':
	{
		return Vec2(350, 535);
		break;
	}
	case 'q':
	{
		return Vec2(410, 535);
		break;
	}
	case 'r':
	{
		return Vec2(470, 535);
		break;
	}
	case 's':
	{
		return Vec2(530, 535);
		break;
	}
	case 't':
	{
		return Vec2(70, 615);
		break;
	}
	case 'u':
	{
		return Vec2(130, 615);
		break;
	}
	case 'v':
	{
		return Vec2(190, 615);
		break;
	}
	case 'w':
	{
		return Vec2(350, 615);
		break;
	}
	case 'x':
	{
		return Vec2(410, 615);
		break;
	}
	case 'y':
	{
		return Vec2(470, 615);
		break;
	}
	case 'z':
	{
		return Vec2(530, 615);
		break;
	}

	case ' ':
	{
		return Vec2(0, 0);
		break;
	}
	case '@':
	{
		return Vec2(0, 0);
		break;
	}
	case '?':
	{
		return Vec2(180, 875);
		break;
	}

	case '!':
	{
		return Vec2(70, 875);
		break;
	}

	case ',':
	{
		return Vec2(695, 115);
		break;
	}

	default:
		break;
	}
}
