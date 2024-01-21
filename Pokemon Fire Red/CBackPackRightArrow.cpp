#include "pch.h"
#include "CBackPackRightArrow.h"

#include "CResourceMgr.h"

#include "CImage.h"

CBackPackRightArrow::CBackPackRightArrow()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BackPackUIArrowRight");
}

CBackPackRightArrow::~CBackPackRightArrow()
{
}

void CBackPackRightArrow::tick()
{
}

void CBackPackRightArrow::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (int)vPos.x - m_pImage->GetWidth() / 2
		, (int)vPos.y - m_pImage->GetHeight() / 2
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);

	CObject::render(_dc);
}

