#include "pch.h"
#include "CBackPackUI.h"

#include "CKeyMgr.h"
#include "CResourceMgr.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CImage.h"
#include "CItem.h"

#include "CBackPackObj.h"
#include "CBackPackRightArrow.h"
#include "CBackPackLeftArrow.h"
#include "CMenuArrow.h"

#include "CPotion.h"
#include "CWeirdCandy.h"
#include "CRevive.h"

CBackPackUI::CBackPackUI()
	: m_pImage(nullptr)
	, m_pFont(nullptr)
	, m_arrOBJ{}
	, m_iBackCount(0)
	, m_arrExpendablesIT{}
	//, m_arrBallIT{}
	, m_iMaxIndex(0)
	, m_pTargetItem(nullptr)
	, m_arrMessage(L"")
	, m_bTargetUI(true)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BackPackUI");
	m_pFont = CResourceMgr::CreateMgr()->FindImg(L"BattleBoxFont");
	
	m_arrOBJ.push_back(new CBackPackObj);
	m_arrOBJ.push_back(new CBackPackLeftArrow);
	m_arrOBJ.push_back(new CBackPackRightArrow);
	m_arrOBJ[0]->SetPos(Vec2(200, 500));
	m_arrOBJ[1]->SetPos(Vec2(45, 350));
	m_arrOBJ[2]->SetPos(Vec2(348, 350));

	AddChildUI(new CMenuArrow);
	GetChildUI()[0]->SetPos(Vec2(450, 72));

	ITEM_INFO* temItem =  CSceneMgr::CreateMgr()->GetPlayerItem();

	if (temItem[(UINT)ITEM_TYPE::POTION].NUMBER != 0)
	{
		CItem* tempitem = new CPotion;
		tempitem->SetPos(Vec2(100, 680));
		m_arrExpendablesIT.push_back(tempitem);
		m_arrExpendablesITNum.push_back(temItem[(UINT)ITEM_TYPE::POTION].NUMBER);
	}

	if (temItem[(UINT)ITEM_TYPE::CANDY].NUMBER != 0)
	{
		CItem* tempitem = new CWeirdCandy;
		tempitem->SetPos(Vec2(100, 680));
		m_arrExpendablesIT.push_back(tempitem);
		m_arrExpendablesITNum.push_back(temItem[(UINT)ITEM_TYPE::CANDY].NUMBER);
	}

	if (temItem[(UINT)ITEM_TYPE::REVIVE].NUMBER != 0)
	{
		CItem* tempitem = new CRevive;
		tempitem->SetPos(Vec2(100, 680));
		m_arrExpendablesIT.push_back(tempitem);
		m_arrExpendablesITNum.push_back(temItem[(UINT)ITEM_TYPE::REVIVE].NUMBER);
	}

	m_iMaxIndex = m_arrExpendablesIT.size() - 1;
}

CBackPackUI::~CBackPackUI()
{
	for (UINT i = 0; i < m_arrOBJ.size(); ++i)
	{
		SAFE_DELETE(m_arrOBJ[i]);
	}


	for (UINT i = 0; i < m_arrExpendablesIT.size(); ++i)
	{
		SAFE_DELETE(m_arrExpendablesIT[i]);
	}
}

void CBackPackUI::tick()
{
	if (m_bTargetUI)
	{
		for (UINT i = 0; i < m_arrOBJ.size(); ++i)
		{
			m_arrOBJ[i]->tick();
		}

		switch (m_iBackCount)
		{
		case 0:
		{
			m_iMaxIndex = m_arrExpendablesIT.size() - 1;
			break;
		}
		case 1:
		{
			m_iMaxIndex = 0;
			break;
		}
		case 2:
		{
			m_iMaxIndex = 0;
			break;
		}

		default:
			break;
		}

		if (IS_TAP(ESC))
		{
			EventDeleteObject(this);
			CSceneMgr::CreateMgr()->GetCurScene()->SetMenuOn(false);
		}

		if (IS_TAP(D))
		{
			if (m_iBackCount < 2)
			{
				m_iBackCount++;
				m_arrOBJ[0]->SetImage(m_iBackCount);
				m_iIndex = 0;
			}
		}
		else if (IS_TAP(A))
		{
			if (m_iBackCount > 0)
			{
				m_iBackCount--;
				m_arrOBJ[0]->SetImage(m_iBackCount);
				m_iIndex = 0;
			}
		}
		if (m_iMaxIndex != 0)
		{
			if (IS_TAP(W))
			{
				if (m_iIndex > 0)
				{
					Vec2 temPos = GetChildUI()[0]->GetPos();
					temPos.y -= 80;
					GetChildUI()[0]->SetPos(temPos);
					m_iIndex--;
				}
			}
			else if (IS_TAP(S))
			{
				if (m_iIndex < m_iMaxIndex)
				{
					Vec2 temPos = GetChildUI()[0]->GetPos();
					temPos.y += 80;
					GetChildUI()[0]->SetPos(temPos);
					m_iIndex++;
				}
			}
		}
	}

	CUI::tick();
}

void CBackPackUI::render(HDC _dc)
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

	// 아이템 이미지 출력
	for (UINT i = 0; i < m_arrOBJ.size(); ++i)
	{
		m_arrOBJ[i]->render(_dc);
	}

	switch (m_iBackCount)
	{
	case 0:
	{
		m_arrExpendablesIT[m_iIndex]->render(_dc);
		m_pTargetItem = m_arrExpendablesIT[m_iIndex];
		break;
	}
	case 1:
	{
		m_pTargetItem = nullptr;
		break;
	}
	case 2:
	{
		m_pTargetItem = nullptr;
		break;
	}

	}

	// 아이템 이름및 갯수 출력
	Vec2 NamePos = Vec2(485, 70);
	Vec2 NumPos = Vec2(1090, 70);
	for (UINT i = 0; i < m_arrExpendablesIT.size(); ++i)
	{
		wstring msg = m_arrExpendablesIT[i]->GetName();

		for (int i = 0; i < msg.size(); ++i)
		{
			if (msg[i] == ' ')
			{
				NamePos.x += 30;
			}
			else
			{
				Fint teminfo = LinkText(msg[i]);

				AlphaBlend(_dc, NamePos.x
					, NamePos.y
					, teminfo.i3, teminfo.i4
					, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);
				NamePos.x += teminfo.i3;
			}
		}

		// 갯수 출력
		wstring nmsg = std::to_wstring(m_arrExpendablesITNum[i]).c_str();

		for (UINT j = nmsg.size(); j > 0; --j)
		{
			int num = j - 1;
			if (nmsg[num] == ' ')
			{
				NumPos.x -= 30;
			}
			else
			{
				Fint teminfo = LinkText(nmsg[num]);

				AlphaBlend(_dc, NumPos.x
					, NumPos.y
					, teminfo.i3, teminfo.i4
					, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);
				NumPos.x -= teminfo.i3;
			}
		}

		// 줄 바꾸기
		NamePos.x = 485;
		NamePos.y += 80;
		NumPos.x = 1090;
		NumPos.y += 80;
	}

	// 아이템 설명 출력
	Vec2 TextPos = Vec2(200,660);

	if (m_pTargetItem != nullptr)
	{
		m_arrMessage = m_pTargetItem->GetExplanation()->c_str();
	}
	else
	{
		m_arrMessage = L"";
	}

	for (int i = 0; i < m_arrMessage.size(); ++i)
	{
		if (m_arrMessage[i] == ' ')
		{
			TextPos.x += 30;
		}
		else
		{
			Fint teminfo = LinkText(m_arrMessage[i]);

			AlphaBlend(_dc, TextPos.x
				, TextPos.y
				, teminfo.i3, teminfo.i4
				, m_pFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);
			TextPos.x += teminfo.i3;
		}
	}

	CUI::render(_dc);
}

Fint CBackPackUI::LinkText(char _text)
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