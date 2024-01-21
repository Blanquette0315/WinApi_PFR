#include "pch.h"
#include "CViridian.h"

#include "CEngine.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CSceneMgr.h"

#include "CCollider.h"
#include "CImage.h"

#include "CPlayer.h"


CViridian::CViridian()
	: m_pBackImage(nullptr)
{
	m_pBackImage = CResourceMgr::CreateMgr()->FindImg(L"ViridianCity");

	AddCollider(L"Image\\map\\City\\Viridian.Collider");
}

CViridian::~CViridian()
{
	CEnvironment::~CEnvironment();
}

void CViridian::tick()
{
	CEnvironment::tick();

	// 카메라 범위 연산
	Vec2 CamRange = {};
	CamRange.x = m_pBackImage->GetWidth();
	CamRange.y = m_pBackImage->GetHeight();
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CViridian::render(HDC _dc)
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

void CViridian::SetImage(wstring _pImage)
{
	m_pBackImage = CResourceMgr::CreateMgr()->FindImg(_pImage);
}

// 구조 바꿔어야 함 타겟 콜라이더를 알고 해당 콜라이더로 판단을 해야한다.
void CViridian::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())
		&& (GetCollider(0)->GetColliderType() == COLLIDER_TYPE::EVENT)
		&& (GetCollider(0)->GetCollisionCount() == 1))
	{
		SceneChange(SCENE_TYPE::PEWTER_CITY);
	}

	else if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())
		&& (GetCollider(1)->GetColliderType() == COLLIDER_TYPE::EVENT)
		&& (GetCollider(1)->GetCollisionCount() == 1))
	{
		SceneChange(SCENE_TYPE::ROAD_01);
	}
}

void CViridian::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CViridian::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}