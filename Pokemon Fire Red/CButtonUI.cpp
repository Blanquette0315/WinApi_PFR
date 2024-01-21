#include "pch.h"
#include "CButtonUI.h"

#include "CSceneMgr.h"
#include "CToolScene.h"
#include "CResourceMgr.h"

#include "CImage.h"

CButtonUI::CButtonUI()
	: m_pFuncPointer(nullptr)
	, m_pImage(nullptr)
{

}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::tick()
{
	// ButtonUI 에서 할 일 작성


	CUI::tick();
}

void CButtonUI::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	tSelectPen pen(_dc, PEN_COLOR::GREEN);
	tSelectBrush Brush(_dc, BRUSH_COLOR::HOLLOW);

	Vec2 vFinalPos = GetFinalPos();

	Rectangle(_dc
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, (int)(vFinalPos.x + vScale.x)
		, (int)(vFinalPos.y + vScale.y));

	if (m_pImage)
	{
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = AC_SRC_ALPHA;
		tFunc.SourceConstantAlpha = 255;

		AlphaBlend(_dc, vFinalPos.x
			, vFinalPos.y
			, m_pImage->GetWidth(), m_pImage->GetHeight()
			, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
	}


	CUI::render(_dc);
}

void CButtonUI::LBtnClicked()
{
	if (nullptr != m_pFuncPointer)
		m_pFuncPointer();

	if (m_Delegate.IsValid())
	{
		(m_Delegate.pInst->*m_Delegate.pFunc)();
	}
}