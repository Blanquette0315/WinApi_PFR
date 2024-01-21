#include "pch.h"
#include "CCameraMgr.h"

#include "CSceneMgr.h"
#include "CEngine.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObject.h"
#include "CScene.h"
#include "CImage.h"

#include "CToolScene.h"

CCameraMgr::CCameraMgr()
	: m_pTargetObj(nullptr)
	, m_pVeil(nullptr)
	, m_fAlpha(0.f)
	, m_vDiff(Vec2(0.f,0.f))
{
	POINT ptResol = CEngine::CreateMgr()->GetResolution();
	m_pVeil = CResourceMgr::CreateMgr()->CreateImg(L"Veil", ptResol.x, ptResol.y);
}

CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::init()
{
	m_vResolution = CEngine::CreateMgr()->GetResolution();
	m_vLook = (m_vResolution / 2.f);
}

void CCameraMgr::tick()
{
	if (IS_PRESS(UP))
	{
		m_vLook.y -= DT * 500.f;
	}
	if (IS_PRESS(DOWN))
	{
		m_vLook.y += DT * 500.f;
	}
	if (IS_PRESS(LEFT))
	{
		m_vLook.x -= DT * 500.f;
	}
	if (IS_PRESS(RIGHT))
	{
		m_vLook.x += DT * 500.f;
	}

	// 나중에 Tool 제작시 해당 코드는 무시하도록 만들어주어야 방향키로 돌아다니면서 작업이 가능해진다.
	if (m_pTargetObj)
	{
		m_vLook = m_pTargetObj->GetPos();
	}

	// 처리할 카메라 효과가 있으면
	if (!m_CamEffectInfo.empty())
	{
		tCamEffectInfo& info = m_CamEffectInfo.front();

		info.fAccTime += DT;
		float fRatio = (info.fAccTime / info.fDuration);	// 제한 시간 대비 진행시간의 비율을 0 ~ 1 사이로 환산

		if (1.f <= fRatio)
		{
			fRatio = 1.f;
			m_CamEffectInfo.pop_front();
		}

		else
		{
			if (CAM_EFFECT::FADE_IN == info.eEffect)
				m_fAlpha = 1.f - fRatio;
			else if (CAM_EFFECT::FADE_OUT == info.eEffect)
				m_fAlpha = fRatio;
			else
				m_fAlpha = 0.f;
		}
	}

	m_vDiff = m_vLook - (m_vResolution / 2.f);
	if (!(dynamic_cast<CToolScene*>(CSceneMgr::CreateMgr()->GetCurScene())))
	{
		CheckDiff();
	}
}

void CCameraMgr::CheckDiff()
{
	// 카메라 Range 체크
	// 만약 범위를 벗어날 경우 m_vDiff를 고정 시켜준다.
	if (m_vDiff.x < 0.f)
	{
		m_vDiff.x = 0.f;
	}

	if (m_vDiff.x > m_CameraRange.x)
	{
		m_vDiff.x = m_CameraRange.x;
	}

	if (m_vDiff.y < 0.f)
	{
		m_vDiff.y = 0.f;
	}

	if (m_vDiff.y > m_CameraRange.y)
	{
		m_vDiff.y = m_CameraRange.y;
	}
}

void CCameraMgr::render(HDC _dc)
{
	if (0.f == m_fAlpha)
		return;

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = 0;
	tFunc.SourceConstantAlpha = (BYTE)(255.f * m_fAlpha);

	AlphaBlend(_dc, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, m_pVeil->GetDC()
		, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, tFunc);
}

