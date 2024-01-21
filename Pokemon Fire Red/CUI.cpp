#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUI::CUI()
	: m_pParentUI(nullptr)
	, m_bMouseOn(false)
	, m_bLbtnPressed(false)
{
}

CUI::CUI(const CUI& _ui)
	: CObject(_ui)
	, m_pParentUI(nullptr)
	, m_bMouseOn(false)
	, m_bLbtnPressed(false)
{
	for (size_t i = 0; i < _ui.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_ui.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		SAFE_DELETE(m_vecChildUI[i]);
	}
}

void CUI::tick()
{
	// FinalPos
	m_vFinalPos = GetPos();

	if (m_pParentUI)
	{
		m_vFinalPos += m_pParentUI->GetFinalPos();
	}

	// 마우스 온 체크
	CheckMouseOn();


	// ChildUI Tick
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick();
	}
}

void CUI::render(HDC _dc)
{
	// ChildUI Render
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}



void CUI::CheckMouseOn()
{
	Vec2 vMousePos = CKeyMgr::CreateMgr()->GetMousePos();
	Vec2 vScale = GetScale();

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}


CUI* CUI::GetAncestorUI()
{
	CUI* pAncestor = this;

	while (nullptr != pAncestor->m_pParentUI)
	{
		pAncestor = pAncestor->m_pParentUI;
	}

	return pAncestor;
}

void CUI::AddChildUI(CUI* _pChildUI)
{
	assert(!_pChildUI->m_pParentUI);

	m_vecChildUI.push_back(_pChildUI);
	_pChildUI->m_pParentUI = this;
}
