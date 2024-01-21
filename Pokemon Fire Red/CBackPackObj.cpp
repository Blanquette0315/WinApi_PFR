#include "pch.h"
#include "CBackPackObj.h"

#include "CResourceMgr.h"

#include "CImage.h"


CBackPackObj::CBackPackObj()
	: m_pImage(nullptr)
	, m_iImageNum(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BackPack");
}

CBackPackObj::~CBackPackObj()
{

}

void CBackPackObj::tick()
{
	if (m_iImageNum == 0)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BackPack");
	}
	else if (m_iImageNum == 1)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BackPack2");
	}
	else if (m_iImageNum == 2)
	{
		m_pImage = CResourceMgr::CreateMgr()->FindImg(L"BackPack3");
	}

}

void CBackPackObj::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (int)vPos.x - m_pImage->GetWidth() / 2
		, (int)vPos.y - m_pImage->GetHeight()
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);

	CObject::render(_dc);
}


void CBackPackObj::SetImage(UINT _index)
{
	m_iImageNum = _index;
}
