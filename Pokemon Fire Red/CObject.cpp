#include "pch.h"
#include "CObject.h"
#include "CComponent.h"

CObject::CObject()
	: m_arrComponent{}
	, m_vPos{}
	, m_bDead(false)
	, m_IS_TOOL(false)
{
}

CObject::~CObject()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		SAFE_DELETE(m_arrComponent[i]);
	}

	CEntity::~CEntity();
}

void CObject::AddComponent(CComponent* _pComponent)
{
	m_arrComponent[(UINT)_pComponent->GetType()] = _pComponent;
	_pComponent->m_pOwner = this;
}

void CObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComponent[i])
			continue;

		m_arrComponent[i]->tick();
	}
}

void CObject::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComponent[i])
			continue;

		m_arrComponent[i]->render(_dc);
	}
}

