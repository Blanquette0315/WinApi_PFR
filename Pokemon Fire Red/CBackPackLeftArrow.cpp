#include "pch.h"
#include "CBackPackLeftArrow.h"

#include "CResourceMgr.h"

#include "CImage.h"

CBackPackLeftArrow::CBackPackLeftArrow()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BackPackUIArrow");
}

CBackPackLeftArrow::~CBackPackLeftArrow()
{
}

void CBackPackLeftArrow::tick()
{
}

void CBackPackLeftArrow::render(HDC _dc)
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