#include "pch.h"
#include "CBattleBox.h"

#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CBattleMgr.h"
#include "CEventMgr.h"

#include "CImage.h"
#include "CSound.h"
#include "CBoxArrow.h"
#include "CPokemon.h"
#include "CSkill.h"

CBattleBox::CBattleBox()
	: m_pImage(nullptr)
	, m_Font(nullptr)
	, m_PPFont(nullptr)
	, m_pSound(nullptr)
	, m_pTargetPokemon(nullptr)
	, m_vecChildUI{}
	, m_CurMenuType(BATTLEBOX_TYPE::SKILL01)
	, m_ISfocus(false)
	, m_arrSkillName{}
	, m_arrSkillMaxPP{}
	, m_arrSkillCurPP{}
	, m_arrSkillType{}

{
	SetPos(Vec2(0.f, 560.f));

	AddChildUI(new CBoxArrow);
	Vec2 ChildPos = GetPos();
	ChildPos.x += 45;
	ChildPos.y += 60;
	GetChildUI()[0]->SetPos(ChildPos);

	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BattleBox");
	m_Font = CResourceMgr::CreateMgr()->FindImg(L"BattleBoxFont");
	m_PPFont = CResourceMgr::CreateMgr()->FindImg(L"PPFont");
	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"SelectSound");
}

CBattleBox::CBattleBox(SKILL_INFO _SkillInfo)
	: m_pImage(nullptr)
	, m_Font(nullptr)
	, m_PPFont(nullptr)
	, m_pSound(nullptr)
	, m_pTargetPokemon(nullptr)
	, m_vecChildUI{}
	, m_CurMenuType(BATTLEBOX_TYPE::SKILL01)
	, m_ISfocus(false)
	, m_arrSkillName{}
	, m_arrSkillMaxPP{}
	, m_arrSkillCurPP{}
	, m_arrSkillType{}
{
	SetPos(Vec2(0.f, 560.f));

	AddChildUI(new CBoxArrow);
	Vec2 ChildPos = GetPos();
	ChildPos.x += 45;
	ChildPos.y += 60;
	GetChildUI()[0]->SetPos(ChildPos);

	// 스킬 인포 정리
	SetSkillInfo(_SkillInfo);

	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BattleBox");
	m_Font = CResourceMgr::CreateMgr()->FindImg(L"BattleBoxFont");
	m_PPFont = CResourceMgr::CreateMgr()->FindImg(L"PPFont");
	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"SelectSound");
}

CBattleBox::CBattleBox(CPokemon* _Object)
	: m_pImage(nullptr)
	, m_Font(nullptr)
	, m_PPFont(nullptr)
	, m_pSound(nullptr)
	, m_pOwnerUI(nullptr)
	, m_pTargetPokemon(_Object)
	, m_vecChildUI{}
	, m_CurMenuType(BATTLEBOX_TYPE::SKILL01)
	, m_ISfocus(false)
	, m_arrSkillName{}
	, m_arrSkillMaxPP{}
	, m_arrSkillCurPP{}
	, m_arrSkillType{}
{
	SetPos(Vec2(0.f, 560.f));

	AddChildUI(new CBoxArrow);
	Vec2 ChildPos = GetPos();
	ChildPos.x += 45;
	ChildPos.y += 60;
	GetChildUI()[0]->SetPos(ChildPos);

	// 스킬 인포 정리
	SetSkillInfo(_Object->GetSkillInfo());

	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BattleBox");
	m_Font = CResourceMgr::CreateMgr()->FindImg(L"BattleBoxFont");
	m_PPFont = CResourceMgr::CreateMgr()->FindImg(L"PPFont");
	m_pSound = CResourceMgr::CreateMgr()->FindSound(L"SelectSound");
}

CBattleBox::~CBattleBox()
{
}

void CBattleBox::tick()
{
	m_arrSkillCurPP[0] = m_pTargetPokemon->GetSkillInfo().Skill01CurPP;

	if (m_ISfocus)
	{
		m_vecChildUI = GetChildUI();
		// S키를 누르면 목차가 위로 이동한다.
		if (IS_TAP(S))
		{
			if (m_CurMenuType == BATTLEBOX_TYPE::SKILL01)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos += Vec2(0.f, 80.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = BATTLEBOX_TYPE::SKILL03;
			}
			else if (m_CurMenuType == BATTLEBOX_TYPE::SKILL02)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos += Vec2(0.f, 80.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = BATTLEBOX_TYPE::SKILL04;
			}
		}
		// W키를 누르면 목차가 아래로 이동한다.
		else if (IS_TAP(W))
		{
			if (m_CurMenuType == BATTLEBOX_TYPE::SKILL03)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos -= Vec2(0.f, 80.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = BATTLEBOX_TYPE::SKILL01;
			}
			else if (m_CurMenuType == BATTLEBOX_TYPE::SKILL04)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos -= Vec2(0.f, 80.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = BATTLEBOX_TYPE::SKILL02;
			}
		}
		else if (IS_TAP(D))
		{
			if (m_CurMenuType == BATTLEBOX_TYPE::SKILL01)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos += Vec2(370.f, 0.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = BATTLEBOX_TYPE::SKILL02;
			}
			else if (m_CurMenuType == BATTLEBOX_TYPE::SKILL03)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos += Vec2(370.f, 0.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = BATTLEBOX_TYPE::SKILL04;
			}
		}
		else if (IS_TAP(A))
		{
			if (m_CurMenuType == BATTLEBOX_TYPE::SKILL02)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos -= Vec2(370.f, 0.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = BATTLEBOX_TYPE::SKILL01;
			}
			else if (m_CurMenuType == BATTLEBOX_TYPE::SKILL04)
			{
				m_pSound->Play(false);
				Vec2 vPos = m_vecChildUI[0]->GetPos();
				vPos -= Vec2(370.f, 0.f);
				m_vecChildUI[0]->SetPos(vPos);
				m_CurMenuType = BATTLEBOX_TYPE::SKILL03;
			}
		}
		// 앤터 키를 누르면 지금 화살표가 가리키고 있는 기능을 수행시켜준다.
		else if (IS_TAP(ENTER))
		{
			switch (m_CurMenuType)
			{
			case BATTLEBOX_TYPE::SKILL01:
			{
				if (!(std::stoi(m_arrSkillCurPP[0]) == 0))
				{
					if (!(m_pTargetPokemon->GetSkill(0) == 0))
					{
						// m_pTargetPokemon->GetSkill(0)->SkillAct();
						CBattleMgr::CreateMgr()->Act(0);
						EventDeleteObject(m_pOwnerUI);
					}
				}
				break;
			}
			case BATTLEBOX_TYPE::SKILL02:
			{
				if (!(m_arrSkillCurPP[1] == L"-")
					&& !(std::stoi(m_arrSkillCurPP[1]) == 0))
				{
					if (!(m_pTargetPokemon->GetSkill(1) == 0))
						CBattleMgr::CreateMgr()->Act(1);
					EventDeleteObject(m_pOwnerUI);
				}
				break;
			}
			case BATTLEBOX_TYPE::SKILL03:
			{
				if (!(m_arrSkillCurPP[2] == L"-")
					&& !(std::stoi(m_arrSkillCurPP[2]) == 0))
				{
					if (!(m_pTargetPokemon->GetSkill(2) == 0))
						CBattleMgr::CreateMgr()->Act(2);
					EventDeleteObject(m_pOwnerUI);
				}
				break;
			}
			case BATTLEBOX_TYPE::SKILL04:
			{
				if (!(m_arrSkillCurPP[3] == L"-")
					&& !(std::stoi(m_arrSkillCurPP[3]) == 0))
				{
					if (!(m_pTargetPokemon->GetSkill(3) == 0))
						CBattleMgr::CreateMgr()->Act(3);
					EventDeleteObject(m_pOwnerUI);
				}
				break;
			}
			}
		}
	}


	CUI::tick();
}

void CBattleBox::render(HDC _dc)
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

	// 스킬 이름 출력
	
	// 1번 스킬
	Vec2 TemSkill01NamePos = vPos;
	TemSkill01NamePos.x += 80;
	TemSkill01NamePos.y += 65;

	for (int i = 0; i < m_arrSkillName[0].size(); ++i)
	{
		Fint teminfo = LinkText(m_arrSkillName[0][i]);

		AlphaBlend(_dc, TemSkill01NamePos.x
			, TemSkill01NamePos.y
			, teminfo.i3, teminfo.i4
			, m_Font->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		TemSkill01NamePos.x += teminfo.i3;
	}

	// 2번 스킬
	Vec2 TemSkill02NamePos = vPos;
	TemSkill02NamePos.x += 450;
	TemSkill02NamePos.y += 65;

	for (int i = 0; i < m_arrSkillName[1].size(); ++i)
	{
		Fint teminfo = LinkText(m_arrSkillName[1][i]);

		AlphaBlend(_dc, TemSkill02NamePos.x
			, TemSkill02NamePos.y
			, teminfo.i3, teminfo.i4
			, m_Font->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		TemSkill02NamePos.x += teminfo.i3;
	}

	// 3번 스킬
	Vec2 TemSkill03NamePos = vPos;
	TemSkill03NamePos.x += 80;
	TemSkill03NamePos.y += 145;

	for (int i = 0; i < m_arrSkillName[2].size(); ++i)
	{
		Fint teminfo = LinkText(m_arrSkillName[2][i]);

		AlphaBlend(_dc, TemSkill03NamePos.x
			, TemSkill03NamePos.y
			, teminfo.i3, teminfo.i4
			, m_Font->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		TemSkill03NamePos.x += teminfo.i3;
	}

	//4번 스킬
	Vec2 TemSkill04NamePos = vPos;
	TemSkill04NamePos.x += 450;
	TemSkill04NamePos.y += 145;

	for (int i = 0; i < m_arrSkillName[3].size(); ++i)
	{
		Fint teminfo = LinkText(m_arrSkillName[3][i]);

		AlphaBlend(_dc, TemSkill04NamePos.x
			, TemSkill04NamePos.y
			, teminfo.i3, teminfo.i4
			, m_Font->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);

		TemSkill04NamePos.x += teminfo.i3;
	}

	// 기술 PP 및 타입 출력

	Vec2 TemSkillPPPos = vPos;
	TemSkillPPPos.x += 1010;
	TemSkillPPPos.y += 62;

	Vec2 TemSkillTypePos = vPos;
	TemSkillTypePos.x += 955;
	TemSkillTypePos.y += 150;

	wstring temPP = L"";
	wstring temType = L"";

	switch (m_CurMenuType)
	{
	case BATTLEBOX_TYPE::SKILL01:
	{
		if (m_arrSkillCurPP[0] == L"-")
		{

			temPP = L" " + m_arrSkillCurPP[0] + L"/";

			if (m_arrSkillMaxPP[0] == L"-")
			{
				temPP = temPP + L" " + m_arrSkillMaxPP[0];
			}
		}
		else
		{
			if (m_arrSkillCurPP[0].size() == 1)
			{
				temPP = L"0" + m_arrSkillCurPP[0] + L"/";
				temPP = temPP + m_arrSkillMaxPP[0];
			}
			else
			{
				temPP = m_arrSkillCurPP[0] + L"/" + m_arrSkillMaxPP[0];
			}
		}

		if (m_arrSkillType[0] == L"-")
		{
			temType = L"-";
		}
		else
		{
			temType = m_arrSkillType[0];
		}
		break;
	}
	case BATTLEBOX_TYPE::SKILL02:
	{
		if (m_arrSkillCurPP[1] == L"-")
		{
			temPP = L" " + m_arrSkillCurPP[1] + L"/";

			if (m_arrSkillMaxPP[1] == L"-")
			{
				temPP = temPP + L" " + m_arrSkillMaxPP[1];
			}
		}
		else
		{
			if (m_arrSkillCurPP[1].size() == 1)
			{
				temPP = L"0" + m_arrSkillCurPP[1] + L"/";
				temPP = temPP + m_arrSkillMaxPP[1];
			}
			else
			{
				temPP = m_arrSkillCurPP[1] + L"/" + m_arrSkillMaxPP[1];
			}
		}

		if (m_arrSkillType[1] == L"-")
		{
			temType = L"-";
		}
		else
		{
			temType = m_arrSkillType[1];
		}
		break;
	}
	case BATTLEBOX_TYPE::SKILL03:
	{
		if (m_arrSkillCurPP[2] == L"-")
		{
			temPP = L" " + m_arrSkillCurPP[2] + L"/";

			if (m_arrSkillMaxPP[2] == L"-")
			{
				temPP = temPP + L" " + m_arrSkillMaxPP[2];
			}
		}
		else
		{
			if (m_arrSkillCurPP[2].size() == 1)
			{
				temPP = L"0" + m_arrSkillCurPP[2] + L"/";
				temPP = temPP + m_arrSkillMaxPP[2];
			}
			else
			{
				temPP = m_arrSkillCurPP[2] + L"/" + m_arrSkillMaxPP[2];
			}
		}

		if (m_arrSkillType[2] == L"-")
		{
			temType = L"-";
		}
		else
		{
			temType = m_arrSkillType[2];
		}
		break;
	}
	case BATTLEBOX_TYPE::SKILL04:
	{
		if (m_arrSkillCurPP[3] == L"-")
		{
			temPP = L" " + m_arrSkillCurPP[3] + L"/";

			if (m_arrSkillMaxPP[3] == L"-")
			{
				temPP = temPP + L" " + m_arrSkillMaxPP[3];
			}
		}
		else
		{
			if (m_arrSkillCurPP[3].size() == 1)
			{
				temPP = L"0" + m_arrSkillCurPP[3] + L"/";
				temPP = temPP + m_arrSkillMaxPP[3];
			}
			else
			{
				temPP = m_arrSkillCurPP[3] + L"/" + m_arrSkillMaxPP[3];
			}
		}

		if (m_arrSkillType[3] == L"-")
		{
			temType = L"-";
		}
		else
		{
			temType = m_arrSkillType[3];
		}
		break;
	}
	}

	for (int i = 0; i < temPP.size(); ++i)
	{
		if (temPP[i] == '/')
		{
			TemSkillPPPos.y -= 10;

			Fint teminfo = LinkText(temPP[i]);

			AlphaBlend(_dc, TemSkillPPPos.x
				, TemSkillPPPos.y
				, teminfo.i3, teminfo.i4
				, m_PPFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);
			TemSkillPPPos.y += 10;
			TemSkillPPPos.x += teminfo.i3;
		}
		else if (temPP[i] == '-')
		{
			Fint teminfo(390, 0, 30, 48);

			AlphaBlend(_dc, TemSkillPPPos.x
				, TemSkillPPPos.y
				, teminfo.i3, teminfo.i4
				, m_PPFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);
			TemSkillPPPos.x += teminfo.i3;
		}
		else if (temPP[i] == ' ')
		{
			TemSkillPPPos.x += 30;
		}
		else
		{
			Fint teminfo = LinkText(temPP[i]);

			AlphaBlend(_dc, TemSkillPPPos.x
				, TemSkillPPPos.y
				, teminfo.i3, teminfo.i4
				, m_PPFont->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);
			TemSkillPPPos.x += teminfo.i3;
		}
	}
	// 타입 출력
	for (int i = 0; i < temType.size(); ++i)
	{
		if (temType[i] == ' ')
		{
			TemSkillTypePos.x += 30;
		}
		else
		{
			Fint teminfo = LinkText(temType[i]);

			AlphaBlend(_dc, TemSkillTypePos.x
				, TemSkillTypePos.y
				, teminfo.i3, teminfo.i4
				, m_Font->GetDC(), teminfo.i1, teminfo.i2, teminfo.i3, teminfo.i4, tFunc);
			TemSkillTypePos.x += teminfo.i3;
		}
	}

	CUI::render(_dc);
}

void CBattleBox::SetSkillInfo(SKILL_INFO _SkillInfo)
{
	m_arrSkillName[0] = _SkillInfo.Skill01Name;
	m_arrSkillName[1] = _SkillInfo.Skill02Name;
	m_arrSkillName[2] = _SkillInfo.Skill03Name;
	m_arrSkillName[3] = _SkillInfo.Skill04Name;

	m_arrSkillMaxPP[0] = _SkillInfo.Skill01MaxPP;
	m_arrSkillMaxPP[1] = _SkillInfo.Skill02MaxPP;
	m_arrSkillMaxPP[2] = _SkillInfo.Skill03MaxPP;
	m_arrSkillMaxPP[3] = _SkillInfo.Skill04MaxPP;

	m_arrSkillCurPP[0] = _SkillInfo.Skill01CurPP;
	m_arrSkillCurPP[1] = _SkillInfo.Skill02CurPP;
	m_arrSkillCurPP[2] = _SkillInfo.Skill03CurPP;
	m_arrSkillCurPP[3] = _SkillInfo.Skill04CurPP;

	m_arrSkillType[0] = _SkillInfo.Skill01Type;
	m_arrSkillType[1] = _SkillInfo.Skill02Type;
	m_arrSkillType[2] = _SkillInfo.Skill03Type;
	m_arrSkillType[3] = _SkillInfo.Skill04Type;
}

Fint CBattleBox::LinkText(char _text)
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

