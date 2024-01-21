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
	// SŰ�� ������ ������ ���� �̵��Ѵ�.
	if (IS_TAP(S) && (m_CurMenuType < (UINT)MENU_TYPE::CLOSE))
	{
		Vec2 vPos = m_vecChildUI[0]->GetPos();
		vPos += Vec2(0.f, 64.f);
		m_vecChildUI[0]->SetPos(vPos);
		m_CurMenuType++;
	}
	// WŰ�� ������ ������ �Ʒ��� �̵��Ѵ�.
	else if (IS_TAP(W) && (m_CurMenuType > (UINT)MENU_TYPE::POKEMON))
	{
		Vec2 vPos = m_vecChildUI[0]->GetPos();
		vPos -= Vec2(0.f, 64.f);
		m_vecChildUI[0]->SetPos(vPos);
		m_CurMenuType--;
	}
	// ���� Ű�� ������ ���� ȭ��ǥ�� ����Ű�� �ִ� UIScene���� �ٲ��ش�.
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
			// ���⼭ ���� UI�� ���������� ����, SceneMgr�� Scene�� �����ؼ� ���� UI �����ϴ� �Լ��� ����������.
			// �׷��� ���� UI�� ������ �ǰ� �޴��� �����Ǹ�, Scene�� tick�� render�� ���� ���� UI�� ������ ���̴�.
			// ���� �����ʰ� Scene�ʿ��� UI�� �������ָ� �ȴ�.
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
	// �ڽ� UI�� tick�� ��������ش�.
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