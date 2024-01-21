#include "pch.h"
#include "CPewter.h"

#include "CEngine.h"
#include "CCameraMgr.h"
#include "CResourceMgr.h"
#include "CEventMgr.h"
#include "CSceneMgr.h"

#include "CCollider.h"
#include "CImage.h"

#include "CPlayer.h"


CPewter::CPewter()
	: m_pBackImage(nullptr)
{
	m_pBackImage = CResourceMgr::CreateMgr()->FindImg(L"PewterCity");

	AddCollider(L"Image\\map\\City\\Pewter.Collider");
}

CPewter::~CPewter()
{
	CEnvironment::~CEnvironment();
}

void CPewter::tick()
{
	CEnvironment::tick();

	// ī�޶� ���� ����
	Vec2 CamRange = {};
	CamRange.x = m_pBackImage->GetWidth();
	CamRange.y = m_pBackImage->GetHeight();
	CamRange -= CEngine::CreateMgr()->GetResolution();
	CCameraMgr::CreateMgr()->SetCameraRange(CamRange);
}

void CPewter::render(HDC _dc)
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

void CPewter::SetImage(wstring _pImage)
{
	m_pBackImage = CResourceMgr::CreateMgr()->FindImg(_pImage);
}

// ���� �ٲ��� �� Ÿ�� �ݶ��̴��� �˰� �ش� �ݶ��̴��� �Ǵ��� �ؾ��Ѵ�.
void CPewter::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner())
		&& (GetCollider(0)->GetColliderType() == COLLIDER_TYPE::EVENT)
		&& (GetCollider(0)->GetCollisionCount() == 1))
	{
		SceneChange(SCENE_TYPE::VIRIDIAN_CITY);
	}
}

void CPewter::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CPewter::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}