#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CResourceMgr.h"

#include "CScene.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CImage.h"

#include "CPokemon.h"
#include "CCharmander.h"
#include "CSquirtle.h"
#include "CBulbasaur.h"
#include "CCaterpie.h"
#include "CPidgey.h"
#include "CRattata.h"

CPlayer::CPlayer()
	: m_pPlayerAtlas(nullptr)
	, m_fSpeed(200.f)
	, wallcollision(false)
	, DeltaPos{}
	, PrevPos{}
	, m_arrNowPokemon{}
	, m_arrPCPokemon{}
	, m_bAnim(false)
{
	AddComponent(new CAnimator);
	AddComponent(new CCollider);

	GetCollider()->SetOffset(Vec2(0, 30));
	GetCollider()->SetScale(Vec2(40,20));

	m_pPlayerAtlas = CResourceMgr::CreateMgr()->LoadImg(L"Player", L"Image\\Player\\Player.bmp");
	GetAnimator()->CreateAnimation(L"Walk_Up", m_pPlayerAtlas, Vec2(0.f, 160.f), Vec2(60.f, 80.f), Vec2(0.f, 0.f), 64.f, 4, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Down", m_pPlayerAtlas, Vec2(0.f, 80.f), Vec2(60.f, 80.f), Vec2(0.f, 0.f), 64.f, 4, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Left", m_pPlayerAtlas, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(0.f, 0.f), 64.f, 4, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Right", m_pPlayerAtlas, Vec2(0.f, 240.f), Vec2(60.f, 80.f), Vec2(0.f, 0.f), 64.f, 4, 0.1f);

	GetAnimator()->Play(L"Walk_Down", false);

	int size = CSceneMgr::CreateMgr()->GetPokemonSize();
	for (int i = 0; i < size; ++i)
	{
		m_arrNowPokemon.push_back(CSceneMgr::CreateMgr()->GetPokemon(i));
		m_arrNowPokemon[i]->SetOwnerType(OWNER_TYPE::PLAYER);
	}

	/*m_arrNowPokemon.push_back(new CPidgey(5));
	m_arrNowPokemon[0]->SetOwnerType(OWNER_TYPE::PLAYER);
	m_arrNowPokemon.push_back(new CCaterpie(5));
	m_arrNowPokemon[1]->SetOwnerType(OWNER_TYPE::PLAYER);

	m_arrNowPokemon.push_back(new CRattata(5));
	m_arrNowPokemon[2]->SetOwnerType(OWNER_TYPE::PLAYER);*/
	/*m_arrNowPokemon.push_back(new CBulbasaur(5));
	m_arrNowPokemon[3]->SetOwnerType(OWNER_TYPE::PLAYER);
	m_arrNowPokemon.push_back(new CCaterpie(5));
	m_arrNowPokemon[4]->SetOwnerType(OWNER_TYPE::PLAYER);
	m_arrNowPokemon.push_back(new CPidgey(5));
	m_arrNowPokemon[5]->SetOwnerType(OWNER_TYPE::PLAYER);*/
}

CPlayer::~CPlayer()
{
	/*for (int i = 0; i < m_arrNowPokemon.size(); ++i)
	{
		SAFE_DELETE(m_arrNowPokemon[i]);
	}*/

	/*for (int i = 0; i < m_arrPCPokemon.size(); ++i)
	{
		SAFE_DELETE(m_arrPCPokemon[i]);
	}*/
}


void CPlayer::tick()
{
	// Player 위치 정보 가져오기
	Vec2 vPos = GetPos();

	if (!(CSceneMgr::CreateMgr()->GetCurScene()->GetMenuISOn()))
	{
		if (wallcollision)
		{
			DeltaPos = (vPos - PrevPos);
			vPos = vPos - (DeltaPos.Changeint() + DeltaPos.Normalize());
		}

		else
		{
			// 키 입력에 따른 Player 이동
			if (IS_PRESS(W))
			{
				vPos.y -= m_fSpeed * DT;
				m_bAnim = false;
				GetAnimator()->CuntinuePlay(L"Walk_Up", true);
			}

			else if (IS_PRESS(S))
			{
				vPos.y += m_fSpeed * DT;
				m_bAnim = false;
				GetAnimator()->CuntinuePlay(L"Walk_Down", true);

			}

			else if (IS_PRESS(A))
			{
				vPos.x -= m_fSpeed * DT;
				m_bAnim = false;
				GetAnimator()->CuntinuePlay(L"Walk_Left", true);
			}

			else if (IS_PRESS(D))
			{
				vPos.x += m_fSpeed * DT;
				m_bAnim = false;
				GetAnimator()->CuntinuePlay(L"Walk_Right", true);
			}
			PrevPos = GetPos();
		}
	}

	

	SetPos(vPos);

	// 에니메이션
	// 키 입력시 애니메이션이 play되고,
	// 만약 해당 에니메이션이 끝나고, 키가 안눌린 상태면 각 항목의 0번 index만 출력해 멈춰 있도록 만들 것이다.
	if (!(CSceneMgr::CreateMgr()->GetCurScene()->GetMenuISOn()))
	{
		if (IS_TAP(W))
		{
			//m_bAnim = false;
			//GetAnimator()->Play(L"Walk_Up", true);
		}
		else if (IS_RELEASE(W))
		{
			//m_bAnim = true;
			GetAnimator()->Play(L"Walk_Up", false);
			//GetAnimator()->ReSetCurAnim();
			//m_vWASD.x = 0;
			//m_vWASD.y = 160.f;
		}

		else if (IS_TAP(A))
		{
			//m_bAnim = false;
			//GetAnimator()->Play(L"Walk_Left", true);
		}
		else if (IS_RELEASE(A))
		{
			GetAnimator()->Play(L"Walk_Left", false);
			//m_bAnim = true;
			//GetAnimator()->ReSetCurAnim();
			//m_vWASD.x = 0;
			//m_vWASD.y = 0;
		}

		else if (IS_TAP(D))
		{
			//m_bAnim = false;
			//GetAnimator()->Play(L"Walk_Right", true);
		}
		else if (IS_RELEASE(D))
		{
			GetAnimator()->Play(L"Walk_Right", false);
			//m_bAnim = true;
			//GetAnimator()->ReSetCurAnim();
			//m_vWASD.x = 0;
			//m_vWASD.y = 241.f;
		}

		else if (IS_TAP(S))
		{
			//m_bAnim = false;
			//GetAnimator()->Play(L"Walk_Down", true);
		}
		else if (IS_RELEASE(S))
		{
			GetAnimator()->Play(L"Walk_Down", false);
			//m_bAnim = true;
			//GetAnimator()->ReSetCurAnim();
			//m_vWASD.x = 0;
			//m_vWASD.y = 80.f;
		}
	}
	

	CObject::tick();
}

//void CPlayer::render(HDC _dc)
//{
//	CObject::render(_dc);
//
//	Vec2 vPos = CCameraMgr::CreateMgr()->GetRenderPos(GetPos());
//
//	if (m_bAnim)
//	{
//		BLENDFUNCTION tFunc = {};
//		tFunc.BlendOp = AC_SRC_OVER;
//		tFunc.BlendFlags = 0;
//		tFunc.AlphaFormat = AC_SRC_ALPHA;
//		tFunc.SourceConstantAlpha = 255;
//
//		AlphaBlend(_dc, (int)vPos.x - (60.f / 2)
//			, (int)vPos.y - (76.f / 2)
//			, 60.f, 76.f
//			, m_pPlayerAtlas->GetDC(), m_vWASD.x, m_vWASD.y, 60.f, 76.f, tFunc);
//	}
//}



CPokemon* CPlayer::GetNowPokemon(UINT _index)
{
	return m_arrNowPokemon[_index];
}

void CPlayer::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if (_pOtherCollider->GetColliderType() == COLLIDER_TYPE::DEFAULT)
	{
		wallcollision = true;
	}
}

void CPlayer::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	if (_pOtherCollider->GetColliderType() == COLLIDER_TYPE::DEFAULT)
	{
		wallcollision = false;
	}
}
