#include "pch.h"
#include "CBackGround.h"

#include "CEngine.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CImage.h"


CBackGround::CBackGround()
	: m_pBackImage(nullptr)
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::tick()
{
	// 카메라 범위 연산
	Vec2 CamRange = {};
	CamRange.x = m_pBackImage->GetWidth();
	CamRange.y = m_pBackImage->GetHeight();
	if ((CEngine::CreateMgr()->GetResolution().x < CamRange.x)
		&& (CEngine::CreateMgr()->GetResolution().y < CamRange.y))
	{
		CamRange -= CEngine::CreateMgr()->GetResolution();
		CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
	}

}

void CBackGround::render(HDC _dc)
{
	Vec2 vPos = CCameraMgr::CreateMgr()->GetRenderPos(GetPos());

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (UINT)vPos.x, (UINT)vPos.y
		, m_pBackImage->GetWidth(), m_pBackImage->GetHeight()
		, m_pBackImage->GetDC(), 0, 0, m_pBackImage->GetWidth(), m_pBackImage->GetHeight(), tFunc);

	CObject::render(_dc);
}

void CBackGround::SetImage(wstring _pImage)
{
	m_pBackImage = CResourceMgr::CreateMgr()->FindImg(_pImage);
}