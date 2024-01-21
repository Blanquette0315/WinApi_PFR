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

	// ���߿� Tool ���۽� �ش� �ڵ�� �����ϵ��� ������־�� ����Ű�� ���ƴٴϸ鼭 �۾��� ����������.
	if (m_pTargetObj)
	{
		m_vLook = m_pTargetObj->GetPos();
	}

	// ó���� ī�޶� ȿ���� ������
	if (!m_CamEffectInfo.empty())
	{
		tCamEffectInfo& info = m_CamEffectInfo.front();

		info.fAccTime += DT;
		float fRatio = (info.fAccTime / info.fDuration);	// ���� �ð� ��� ����ð��� ������ 0 ~ 1 ���̷� ȯ��

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
	// ī�޶� Range üũ
	// ���� ������ ��� ��� m_vDiff�� ���� �����ش�.
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

