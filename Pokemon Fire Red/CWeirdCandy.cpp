#include "pch.h"
#include "CWeirdCandy.h"

#include "CResourceMgr.h"

#include "CImage.h"

CWeirdCandy::CWeirdCandy()
	: m_pImage(nullptr)
	, m_eItemType(ITEM_TYPE::CANDY)
	, m_wsExplanation(L"")
{
	// 이름 넣기
	SetName(L"Candy");

	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"Candy");
	m_wsExplanation = L"Increases the LV of 1 Pokemon by 1";
}

CWeirdCandy::~CWeirdCandy()
{
}

void CWeirdCandy::tick()
{
	CObject::tick();
}

void CWeirdCandy::render(HDC _dc)
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