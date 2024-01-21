#include "pch.h"
#include "CCancelBox.h"

#include "CResourceMgr.h"

#include "CImage.h"

CCancelBox::CCancelBox()
	: m_pImage(nullptr)
	, m_pTargetImage(nullptr)
	, m_bIS_Target(false)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"CancelBox");
	m_pTargetImage = CResourceMgr::CreateMgr()->FindImg(L"CancelBoxTarget");
}

CCancelBox::~CCancelBox()
{
}

void CCancelBox::tick()
{
	// ButtonUI 에서 할 일 작성


	CUI::tick();
}

void CCancelBox::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	if (m_bIS_Target)
	{
		AlphaBlend(_dc, vPos.x - m_pTargetImage->GetWidth()
			, vPos.y - m_pTargetImage->GetHeight() + 10
			, m_pTargetImage->GetWidth(), m_pTargetImage->GetHeight()
			, m_pTargetImage->GetDC(), 0, 0, m_pTargetImage->GetWidth(), m_pTargetImage->GetHeight(), tFunc);

	}
	else
	{
		AlphaBlend(_dc, vPos.x - m_pImage->GetWidth()
			, vPos.y - m_pImage->GetHeight()
			, m_pImage->GetWidth(), m_pImage->GetHeight()
			, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
	}



	CUI::render(_dc);
}