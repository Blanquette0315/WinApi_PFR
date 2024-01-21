#include "pch.h"
#include "CEnvironment.h"

#include "CResourceMgr.h"
#include "CPathMgr.h"

#include "CComponent.h"
#include "CCollider.h"
#include "CImage.h"

CEnvironment::CEnvironment()
	: m_arrCollider{}
	, m_pImage(nullptr)
	, CurCount(0)
	, m_tFianlInfo{}
{
}

CEnvironment::~CEnvironment()
{
	for (UINT i = 0; i < m_arrCollider.size(); ++i)
	{
		SAFE_DELETE(m_arrCollider[i]);
	}

	CObject::~CObject();
}

void CEnvironment::AddCollider(CComponent* _pComponent)
{
	if (CurCount < m_tFianlInfo.size())
	{
		m_arrCollider.push_back(_pComponent);
		
		++CurCount;
	}
	else
	{
		return;
	}
}

void CEnvironment::AddCollider(const wstring& _strRelativePath)
{
	ColliderLoad(_strRelativePath);
	for (UINT i = 0; i < m_tFianlInfo.size(); ++i)
	{
	
			AddCollider(new CCollider);
			GetCollider(i)->SetOffset(Vec2(m_tFianlInfo[i].ColliderOffset.x, m_tFianlInfo[i].ColliderOffset.y));
			GetCollider(i)->SetScale(Vec2(m_tFianlInfo[i].ColliderScale.x, m_tFianlInfo[i].ColliderScale.y));
			GetCollider(i)->SetColliderType(m_tFianlInfo[i].Collider_Type);
			GetCollider(i)->SetOwner(CObject::GetAdress());
	}
	
}

void CEnvironment::tick()
{
	// Object가 가지고 있는 모든 Component의 tick() 수행 후
	// 환경체가 가지고 있는 모든 Collider의 tick()을 수행 한다.

	CObject::tick();

	for (UINT i = 0; i < m_arrCollider.size(); ++i)
	{
		if (nullptr == m_arrCollider[i])
			continue;

		m_arrCollider[i]->tick();
	}
}

void CEnvironment::render(HDC _dc)
{
	// tick()과 동일하게 작동한다.

	CObject::render(_dc);

	for (UINT i = 0; i < m_arrCollider.size(); ++i)
	{
		if (nullptr == m_arrCollider[i])
			continue;

		m_arrCollider[i]->render(_dc);
	}
}

/*void CEnvironment::ImageRerender(HDC _dc)
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
}

void CEnvironment::SetImage(wstring _pImage)
{
	m_pImage = CResourceMgr::CreateMgr()->FindImg(_pImage);
}*/


void CEnvironment::ColliderLoad(const wstring& _strRelativePath)
{
	wstring FilePath = CPathMgr::CreateMgr()->GetContentPath();
	FilePath += _strRelativePath;
	
	// 파일 입출력
	FILE* pFile = nullptr;

	// 쓰기 모드로 열기
	_wfopen_s(&pFile, FilePath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	// Collider 정보 읽기
	UINT Count = 0;
	fread(&Count, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < Count; ++i)
	{
		Vec2 arrFinalScale = {};
		Vec2 arrFinalOffSet = {};
		COLLIDER_TYPE arrFianlComponentType = {};

		FianlInfo TemFinalInfo = {};

		fread(&arrFinalScale, sizeof(Vec2), 1, pFile);
		fread(&arrFinalOffSet, sizeof(Vec2), 1, pFile);
		fread(&arrFianlComponentType, sizeof(COLLIDER_TYPE), 1, pFile);

		TemFinalInfo.ColliderOffset.x = arrFinalOffSet.x;
		TemFinalInfo.ColliderOffset.y = arrFinalOffSet.y;
		TemFinalInfo.ColliderScale.x = arrFinalScale.x;
		TemFinalInfo.ColliderScale.y = arrFinalScale.y;
		TemFinalInfo.Collider_Type = arrFianlComponentType;
		m_tFianlInfo.push_back(TemFinalInfo);
	}

	/*Vec2 arrFinalScale[MaxCollider] = {};
	Vec2 arrFinalOffSet[MaxCollider] = {};
	COLLIDER_TYPE arrFianlComponentType[MaxCollider] = {};

	for (UINT i = 0; i < MaxCollider; ++i)
	{
		fread(&arrFinalScale[i], sizeof(Vec2), 1, pFile);
		fread(&arrFinalOffSet[i], sizeof(Vec2), 1, pFile);
		fread(&arrFianlComponentType[i], sizeof(COLLIDER_TYPE), 1, pFile);
	}

	for(UINT i = 0; i < MaxCollider; ++i)
	{
		m_tFianlInfo[i].ColliderOffset.x = arrFinalOffSet[i].x;
		m_tFianlInfo[i].ColliderOffset.y = arrFinalOffSet[i].y;
		m_tFianlInfo[i].ColliderScale.x = arrFinalScale[i].x;
		m_tFianlInfo[i].ColliderScale.y = arrFinalScale[i].y;
		m_tFianlInfo[i].Collider_Type = arrFianlComponentType[i];
	}*/

	fclose(pFile);
}