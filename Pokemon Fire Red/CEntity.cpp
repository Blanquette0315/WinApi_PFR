#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_GlobalID = 0;


CEntity::CEntity()
	: m_ID(g_GlobalID++)
{
}

CEntity::CEntity(const CEntity& _other)
	: m_strName(_other.m_strName)
	, m_ID(g_GlobalID++)
{
}

CEntity::~CEntity()
{
}