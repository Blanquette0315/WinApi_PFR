#include "pch.h"
#include "CGrassBattle.h"

#include "CResourceMgr.h"

#include "CImage.h"

CGrassBattle::CGrassBattle()
	: m_pImage(nullptr)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"GrassBattle");
}

CGrassBattle::~CGrassBattle()
{
}

void CGrassBattle::tick()
{
}

void CGrassBattle::render(HDC _dc)
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
}