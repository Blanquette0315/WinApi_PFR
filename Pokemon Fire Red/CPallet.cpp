#include "pch.h"
#include "CPallet.h"

#include "CEngine.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CSceneMgr.h"

#include "CCollider.h"
#include "CImage.h"

#include "CPlayer.h"


CPallet::CPallet()
	: m_pBackImage(nullptr)
{
	m_pBackImage = CResourceMgr::CreateMgr()->FindImg(L"PalletCity");

	AddCollider(L"Image\\map\\City\\Pallet.Collider");
}

CPallet::~CPallet()
{
	CEnvironment::~CEnvironment();
}

void CPallet::tick()
{
	CEnvironment::tick();

	// 카메라 범위 연산
	Vec2 CamRange = {};
	CamRange.x = m_pBackImage->GetWidth();
	CamRange.y = m_pBackImage->GetHeight();
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CPallet::render(HDC _dc)
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

	CEnvironment::render(_dc);
}

void CPallet::SetImage(wstring _pImage)
{
	m_pBackImage = CResourceMgr::CreateMgr()->FindImg(_pImage);
}

void CPallet::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())
		&& (GetCollider(0)->GetColliderType() == COLLIDER_TYPE::EVENT)
		&& (GetCollider(0)->GetCollisionCount() == 1))
	{
		if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())->GetNowPokemonSize() != 0)
			SceneChange(SCENE_TYPE::ROAD_01);
	}
}

void CPallet::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CPallet::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}
