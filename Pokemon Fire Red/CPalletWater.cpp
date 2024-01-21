#include "pch.h"
#include "CPalletWater.h"

#include "CResourceMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"

CPalletWater::CPalletWater()
	: m_pImage(nullptr)
	, IS_Collision(false)
	, m_iRe_render(0)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(L"PalletWave");

	AddCollider(L"Image\\map\\Environment\\PalletWave.Collider");

	//CEventMgr::CreateMgr()->Re_Render(this);
}

CPalletWater::~CPalletWater()
{
	CEnvironment::~CEnvironment();
}

void CPalletWater::tick()
{
	CEnvironment::tick();
}

void CPalletWater::render(HDC _dc)
{
	Vec2 vPos = CCameraMgr::CreateMgr()->GetRenderPos(GetPos());

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (int)vPos.x - m_pImage->GetWidth() / 2
		, (int)vPos.y - m_pImage->GetHeight()
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);

	CEnvironment::render(_dc);
}

void CPalletWater::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	
}

void CPalletWater::CollisionOverlap(CCollider* _pOtherCollider)
{

}

void CPalletWater::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	
}