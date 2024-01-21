#include "pch.h"
#include "CSkill.h"

#include "CPokemon.h"

CSkill::CSkill()
	: m_Power(0)
	, m_MaxPP(0)
	, m_CurPP(0)
	, m_Accuracy(1)
	, m_AType(0)
	, m_Priority(0)
	, m_pOwnerPokemon(nullptr)
{
}

CSkill::~CSkill()
{
}

void CSkill::SetSkillInfo(UINT _Power, UINT _MaxPP, float _Accuracy, POKEMON_TYPE _SkilType, UINT _AType, UINT _Priority)
{
	m_Power = _Power;
	m_MaxPP = _MaxPP;
	m_CurPP = _MaxPP;
	m_Accuracy = _Accuracy;
	m_SkillType = _SkilType;
	m_AType = _AType;
	m_Priority = _Priority;
}

void CSkill::SkillAct()
{
	if (m_pOwnerPokemon->GetOwnerType() == OWNER_TYPE::PLAYER)
	{
		SetPos(Vec2(880.f, 270.f));
	}
	else
	{
		SetPos(Vec2(360.f, 485.f));
	}
	

	if(!(m_CurPP == 0))
		--m_CurPP;
}

const wstring CSkill::GetWsSkillType()
{
	switch(m_SkillType)
	{
	case POKEMON_TYPE::NORMAL :
		{
			return L"NORMAL";
			break;
		}

	case POKEMON_TYPE::FIRE:
	{
		return L"FIRE";
		break;
	}

	case POKEMON_TYPE::WATER:
	{
		return L"WATER";
		break;
	}

	case POKEMON_TYPE::ELECTR:
	{
		return L"ELECTR";
		break;
	}

	case POKEMON_TYPE::GRASS:
	{
		return L"GRASS";
		break;
	}

	case POKEMON_TYPE::ICE:
	{
		return L"ICE";
		break;
	}

	case POKEMON_TYPE::FIGHT:
	{
		return L"FIGHT";
		break;
	}

	case POKEMON_TYPE::POISON:
	{
		return L"POISON";
		break;
	}

	case POKEMON_TYPE::GROUND:
	{
		return L"GROUND";
		break;
	}

	case POKEMON_TYPE::FLVING:
	{
		return L"FLVING";
		break;
	}

	case POKEMON_TYPE::PSYCHC:
	{
		return L"PSYCHC";
		break;
	}

	case POKEMON_TYPE::BUG:
	{
		return L"BUG";
		break;
	}

	case POKEMON_TYPE::ROCK:
	{
		return L"ROCK";
		break;
	}

	case POKEMON_TYPE::GHOST:
	{
		return L"GHOST";
		break;
	}

	case POKEMON_TYPE::DREGON:
	{
		return L"DREGON";
		break;
	}

	case POKEMON_TYPE::DARK:
	{
		return L"DARK";
		break;
	}

	case POKEMON_TYPE::STEEL:
	{
		return L"STEEL";
		break;
	}

	default:
	{
		return L"-";
		break;
	}
	}

}

void CSkill::tick()
{
	CObject::tick();
}

void CSkill::render(HDC _dc)
{
	CObject::render(_dc);
}
