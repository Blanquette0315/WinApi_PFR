#include "pch.h"
#include "CMenuArrow.h"

#include "CResourceMgr.h"

#include "CImage.h"

CMenuArrow::CMenuArrow()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"MenuArrow");
}

CMenuArrow::~CMenuArrow()
{
}

void CMenuArrow::tick()
{
	// ButtonUI 에서 할 일 작성


	CUI::tick();
}

void CMenuArrow::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	if (m_pImage)
	{
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = AC_SRC_ALPHA;
		tFunc.SourceConstantAlpha = 255;

		AlphaBlend(_dc, vPos.x
			, vPos.y
			, m_pImage->GetWidth(), m_pImage->GetHeight()
			, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
	}


	CUI::render(_dc);
}