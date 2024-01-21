#include "pch.h"
#include "CBoxArrow.h"

#include "CResourceMgr.h"

#include "CImage.h"

CBoxArrow::CBoxArrow()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BoxArrow");
}

CBoxArrow::~CBoxArrow()
{
}

void CBoxArrow::tick()
{
	// ButtonUI 에서 할 일 작성


	CUI::tick();
}

void CBoxArrow::render(HDC _dc)
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