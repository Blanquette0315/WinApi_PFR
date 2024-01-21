#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

#include "CEnvironment.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::tick()
{
	CScene* pCurScene = CSceneMgr::CreateMgr()->GetCurScene();

	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (m_matrix[iRow] & (1 << iCol))
			{
				CollisionBtwLayer(pCurScene, (LAYER_TYPE)iRow, (LAYER_TYPE)iCol);
			}
		}
	}
}


void CCollisionMgr::CollisionBtwLayer(CScene* _pCurScene, LAYER_TYPE _eLeft, LAYER_TYPE _eRight)
{
	const vector<CObject*>& vecLeft = _pCurScene->GetObjects(_eLeft);
	const vector<CObject*>& vecRight = _pCurScene->GetObjects(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider()
			&& !((_eLeft == LAYER_TYPE::ENVIRONMENT)
				|| (_eLeft == LAYER_TYPE::BACKGROUND)
				|| (_eLeft == LAYER_TYPE::NPC)))
			continue;

		size_t j = 0;
		if (_eLeft == _eRight)
		{
			j = i + 1;
		}


		for (; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider()
				&& !((_eRight == LAYER_TYPE::ENVIRONMENT)
					|| (_eRight == LAYER_TYPE::BACKGROUND)
					|| (_eRight == LAYER_TYPE::NPC)))
			{
				continue;
			}
			//vecLeft[i]->GetVectorSize()
			//vecRight[j]->GetVectorSize()
			if (dynamic_cast<CEnvironment*>(vecLeft[i]))
			{
				for (UINT k = 0; k < vecLeft[i]->GetVectorSize(); ++k)
				{
					if (nullptr == vecLeft[i]->GetCollider(k))
						continue;
					CollisionBtwCollider(vecLeft[i]->GetCollider(k), vecRight[j]->GetCollider());
				}
			}
			else if (dynamic_cast<CEnvironment*>(vecRight[j]))
			{
				for (UINT k = 0; k < vecRight[j]->GetVectorSize(); ++k)
				{
					if (nullptr == vecRight[j]->GetCollider(k))
						continue;
					CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider(k));
				}
			}
			else
			{
				CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider());
			}
		}
	}
}

void CCollisionMgr::CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight)
{
	COLLIDER_ID id;
	id.LEFT_ID = _pLeft->GetID();
	id.RIGHT_ID = _pRight->GetID();

	map<LONGLONG, bool>::iterator iter = m_mapColInfo.find(id.ID);

	if (iter == m_mapColInfo.end())
	{
		m_mapColInfo.insert(make_pair(id.ID, false));
		iter = m_mapColInfo.find(id.ID);
	}

	// 두 충돌체중 하나 이상의 Dead 상태인지
	bool IsDead = _pLeft->GetOwner()->IsDead() || _pRight->GetOwner()->IsDead();


	// 현재 충돌중인지 검사 한다.			
	if (IsCollision(_pLeft, _pRight))
	{
		if (false == iter->second)
		{
			if (!IsDead)
			{
				_pLeft->CollisionBeginOverlap(_pRight);
				_pRight->CollisionBeginOverlap(_pLeft);
				iter->second = true;
			}
		}
		else
		{
			if (IsDead)
			{
				_pLeft->CollisionEndOverlap(_pRight);
				_pRight->CollisionEndOverlap(_pLeft);
				iter->second = false;
			}
			else
			{
				_pLeft->CollisionOverlap(_pRight);
				_pRight->CollisionOverlap(_pLeft);
			}
		}
	}
	else
	{
		if (iter->second)
		{
			_pLeft->CollisionEndOverlap(_pRight);
			_pRight->CollisionEndOverlap(_pLeft);
			iter->second = false;
		}
	}
}


bool CCollisionMgr::IsCollision(CCollider* _pLeft, CCollider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	Vec2 vLeftScale = _pLeft->GetScale();

	Vec2 vRightPos = _pRight->GetFinalPos();
	Vec2 vRightScale = _pRight->GetScale();


	// 사각형 충돌체 충돌 검사
	if (fabs(vLeftPos.x - vRightPos.x) < (vLeftScale.x / 2.f + vRightScale.x / 2.f)
		&& fabs(vLeftPos.y - vRightPos.y) < (vLeftScale.y / 2.f + vRightScale.y / 2.f))
	{
		return true;
	}
	return false;
}






void CCollisionMgr::CollisionLayerCheck(LAYER_TYPE _eLeft, LAYER_TYPE _eRight)
{
	// 더 작은 숫자를 행(배열의 인덱스) 으로, 더 큰 숫자를 열(비트 위치) 로
	UINT iRow = 0, iCol = 0;
	if ((UINT)_eLeft <= (UINT)_eRight)
	{
		iRow = (UINT)_eLeft;
		iCol = (UINT)_eRight;
	}
	else
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionLayerRelease(LAYER_TYPE _eLeft, LAYER_TYPE _eRight)
{
	// 더 작은 숫자를 행(배열의 인덱스) 으로, 더 큰 숫자를 열(비트 위치) 로
	UINT iRow = 0, iCol = 0;
	if ((UINT)_eLeft <= (UINT)_eRight)
	{
		iRow = (UINT)_eLeft;
		iCol = (UINT)_eRight;
	}
	else
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	m_matrix[iRow] &= ~(1 << iCol);
}