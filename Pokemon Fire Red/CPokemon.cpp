#include "pch.h"
#include "CPokemon.h"

#include "CSkill.h"

CPokemon::CPokemon()
	: m_tMonsterInfo{}
	, m_bIS_LevelUp(false)
	, m_bIs_Incapacity(false)
	, m_arrPokemonType{} // 0으로 초기화 되므로 NONE이 들어간다.
	, m_arrSkill{}
	, m_pTargetSkill(0)
	, m_eOwnerType(OWNER_TYPE::WILD) // 기본으로는 야생이 들어간다.
	, m_eSceneType(POKEMONSCENE_TYPE::NONE)
{
}

CPokemon::~CPokemon()
{
	Safe_Del_Map(m_arrSkill);
}

void CPokemon::tick()
{
	// HP가 0인지 체크해서 0일 경우 전투 불능 판정을 해주어야 한다.
	if (m_tMonsterInfo.m_CurHP <= 0)
	{
		m_bIs_Incapacity = true;
	}

	if(!(m_pTargetSkill == nullptr))
		m_pTargetSkill->tick();

	CObject::tick();
}

void CPokemon::render(HDC _dc)
{
	CObject::render(_dc);
}

// 경험치 관련 함수

void CPokemon::AddBattleExp(UINT _OtherLv, UINT _MonCount)
{
	// 전투 종료 후 경험치 추가 상대 종류가 어떤 것인지도 추가해주어야 한다.
	m_tMonsterInfo.m_CurExp += ((30 * _OtherLv) / (7* _MonCount));

	// 경험치 획득 후 레벨업을 했을 경우
	if (m_tMonsterInfo.m_MaxExp <= m_tMonsterInfo.m_CurExp)
	{
		UINT EXPtem = m_tMonsterInfo.m_CurExp - m_tMonsterInfo.m_MaxExp;
		if (0 < EXPtem)
		{
			m_tMonsterInfo.m_CurExp = EXPtem;
		}
		else
		{
			m_tMonsterInfo.m_CurExp = 0;
		}

		LevelUP();
		// 만약 레벨업을 했을 경우 배틀 Scene에게 알려서 레벨업을 했다는 것을 알려야 한다.
		// 그래야 배틀씬에서 알맞은 텍스트 UI를 띄워준다.
	}
}

// 이상한 사탕 사용시에도 이 함수를 호출해주면 된다.
void CPokemon::LevelUP()
{
	if (m_tMonsterInfo.m_CurLV < m_tMonsterInfo.m_MaxLV)
	{
		m_tMonsterInfo.m_CurLV++;
	}

	StatsUpDate();
}

void CPokemon::StatsUpDate()
{
	m_tMonsterInfo.m_MaxHP += (((m_tMonsterInfo.m_MaxHP * 2) * (m_tMonsterInfo.m_CurLV / 100)) + 10 + m_tMonsterInfo.m_CurLV);
	m_tMonsterInfo.m_Atteck += (UINT)(((m_tMonsterInfo.m_Atteck * 2) * (m_tMonsterInfo.m_CurLV / 100)) + 5);
	m_tMonsterInfo.m_Defence += (UINT)(((m_tMonsterInfo.m_Defence * 2) * (m_tMonsterInfo.m_CurLV / 100)) + 5);
	m_tMonsterInfo.m_SAtteck += (UINT)(((m_tMonsterInfo.m_SAtteck * 2) * (m_tMonsterInfo.m_CurLV / 100)) + 5);
	m_tMonsterInfo.m_SDefence += (UINT)(((m_tMonsterInfo.m_SDefence * 2) * (m_tMonsterInfo.m_CurLV / 100)) + 5);
	m_tMonsterInfo.m_Speed += (UINT)(((m_tMonsterInfo.m_Speed * 2) * (m_tMonsterInfo.m_CurLV / 100)) + 5);
	UpDateMaxEXP();
}

// 경험치 요구량 계산
void CPokemon::UpDateMaxEXP()
{
	m_tMonsterInfo.m_MaxExp = ((1.2 * pow(m_tMonsterInfo.m_CurLV, 3)) - (15 * pow(m_tMonsterInfo.m_CurLV, 2))
		+ (100 * m_tMonsterInfo.m_CurLV) - 140);
}


void CPokemon::SetBaseStats(UINT _MaxHP, UINT _Atteck, UINT _Defence, UINT _Speed, UINT _SAtteck, UINT _SDefence)
{
	m_tMonsterInfo.m_MaxHP = _MaxHP;
	m_tMonsterInfo.m_CurHP = _MaxHP;
	m_tMonsterInfo.m_Atteck = _Atteck;
	m_tMonsterInfo.m_Defence = _Defence;
	m_tMonsterInfo.m_Speed = _Speed;
	m_tMonsterInfo.m_SAtteck = _SAtteck;
	m_tMonsterInfo.m_SDefence = _SDefence;
	StatsUpDate();

	m_tMonsterInfo.m_CurHP = m_tMonsterInfo.m_MaxHP;
}

void CPokemon::SetPokemonType(POKEMON_TYPE _Type1, POKEMON_TYPE _Type2)
{
	m_arrPokemonType[0] = _Type1;
	m_arrPokemonType[1] = _Type2;
}

// 스킬 관련 함수
void CPokemon::AddSkill(UINT _strKey, CSkill* _Skill)
{
	if (!(m_arrSkill.size() == 4))
	{
		m_arrSkill.insert(make_pair(_strKey, _Skill));
	}
}

SKILL_INFO CPokemon::GetSkillInfo()
{
	SKILL_INFO temSkillinfo = {};

	// 스킬 이름
	if ((m_arrSkill.size() > 0)
		&& !(m_arrSkill[0] == nullptr))
	{
		temSkillinfo.Skill01Name = m_arrSkill[0]->GetName();
		temSkillinfo.Skill01MaxPP = std::to_wstring(m_arrSkill[0]->GetMaxPP());
		temSkillinfo.Skill01CurPP = std::to_wstring(m_arrSkill[0]->GetCurPP());
		temSkillinfo.Skill01Type = m_arrSkill[0]->GetWsSkillType();
	}
	else
	{
		temSkillinfo.Skill01Name = L"-";
		temSkillinfo.Skill01MaxPP = L"-";
		temSkillinfo.Skill01CurPP = L"-";
		temSkillinfo.Skill01Type = L"-";
	}

	if ((m_arrSkill.size() > 1)
		&& !(m_arrSkill[1] == nullptr))
	{
		temSkillinfo.Skill02Name = m_arrSkill[1]->GetName();
		temSkillinfo.Skill02MaxPP = std::to_wstring(m_arrSkill[1]->GetMaxPP());
		temSkillinfo.Skill02CurPP = std::to_wstring(m_arrSkill[1]->GetCurPP());
		temSkillinfo.Skill02Type = m_arrSkill[1]->GetWsSkillType();
	}
	else
	{
		temSkillinfo.Skill02Name = L"-";
		temSkillinfo.Skill02MaxPP = L"-";
		temSkillinfo.Skill02CurPP = L"-";
		temSkillinfo.Skill02Type = L"-";
	}

	if ((m_arrSkill.size() > 2)
		&& !(m_arrSkill[2] == nullptr))
	{
		temSkillinfo.Skill03Name = m_arrSkill[2]->GetName();
		temSkillinfo.Skill03MaxPP = std::to_wstring(m_arrSkill[2]->GetMaxPP());
		temSkillinfo.Skill03CurPP = std::to_wstring(m_arrSkill[2]->GetCurPP());
		temSkillinfo.Skill03Type = m_arrSkill[2]->GetWsSkillType();
	}
	else
	{
		temSkillinfo.Skill03Name = L"-";
		temSkillinfo.Skill03MaxPP = L"-";
		temSkillinfo.Skill03CurPP = L"-";
		temSkillinfo.Skill03Type = L"-";
	}

	if ((m_arrSkill.size() > 3)
		&& !(m_arrSkill[3] == nullptr))
	{
		temSkillinfo.Skill04Name = m_arrSkill[3]->GetName();
		temSkillinfo.Skill04MaxPP = std::to_wstring(m_arrSkill[3]->GetMaxPP());
		temSkillinfo.Skill04CurPP = std::to_wstring(m_arrSkill[3]->GetCurPP());
		temSkillinfo.Skill04Type = m_arrSkill[3]->GetWsSkillType();
	}
	else
	{
		temSkillinfo.Skill04Name = L"-";
		temSkillinfo.Skill04MaxPP = L"-";
		temSkillinfo.Skill04CurPP = L"-";
		temSkillinfo.Skill04Type = L"-";
	}

	return temSkillinfo;
}

CSkill* CPokemon::GetSkill(UINT _i)
{
	if (m_arrSkill.size() == 1)
	{
		if (_i > 0)
		{
			return 0;
		}
		else
		{
			return m_arrSkill[_i];
		}
	}
	if (m_arrSkill.size() == 2)
	{
		if (_i > 1)
		{
			return 0;
		}
		else
		{
			return m_arrSkill[_i];
		}
	}
	if (m_arrSkill.size() == 3)
	{
		if (_i > 2)
		{
			return 0;
		}
		else
		{
			return m_arrSkill[_i];
		}
	}
	if (m_arrSkill.size() == 4)
	{
		if (_i > 3)
		{
			return 0;
		}
		else
		{
			return m_arrSkill[_i];
		}
	}
}

CSkill* CPokemon::GetRandSkill()
{
	if (m_arrSkill.size() == 1)
	{
		return m_arrSkill[0];
	}
	if (m_arrSkill.size() == 2)
	{
		srand(time(NULL));
		int i = rand() % 2;
		return m_arrSkill[i];
	}
	if (m_arrSkill.size() == 3)
	{
		srand(time(NULL));
		int i = rand() % 3;
		return m_arrSkill[i];
	}
	if (m_arrSkill.size() == 4)
	{
		srand(time(NULL));
		int i = rand() % 4;
		return m_arrSkill[i];
	}
	
}

// 전투 관련 함수
// 공격을 할 때 상대 타입, 방어, 특방을 인자로 받아 계산한 뒤 넘겨준다.

UINT CPokemon::Attack(UINT _SkillPower, POKEMON_TYPE _SkillType, UINT _AType, UINT _Defence, UINT _SDefence
					,float _ComType1, float _ComType2 )
{
	// 데미지 공식으로 대미지 계산 후 상대에게 넘겨줘서 상대는 해당 데미지를 Hit로 계산해 현재 HP를 깎는다.

	// 레벨 계산
	float Lv = ((m_tMonsterInfo.m_CurLV) * 2 / 5 + 2);

	// 위력 계산
	float Power = _SkillPower;

	// 공격 및 특공 계산
	float Atteck = 0;
	if (_AType == 0)
		Atteck = m_tMonsterInfo.m_Atteck;
	else if (_AType == 1)
		Atteck = m_tMonsterInfo.m_SAtteck;

	// 방어 및 특방 계산
	float Defence = 0;
	if (_AType == 0)
		Defence = _Defence;
	else if (_AType == 1)
		Defence = _SDefence;

	// Mod1 계산
	float Mod1 = 1;

	// 급소 계산
	float Critical = 1;

	// Mod2 계산
	float Mod2 = 1;

	// 자속보정 계산
	float SameType = IS_SameType(m_arrPokemonType, _SkillType);

	// 특성 상성 계산
	float ComType1 = _ComType1;
	float ComType2 = _ComType2;

	//랜덤수 계산
	float Random = DmgRand();

	// 데미지 = (((((((레벨 * 2 / 5) + 2) * 위력 * 공격 / 50) / 방어) * Mod1) + 2) * [[급소]] * Mod2) * 자속보정 * 상성1
	//			* 상성2 * 랜덤수 / 100)
	UINT DMG = (UINT)((((((Lv * Power * Atteck / 50) / Defence) * Mod1) + 2) * Critical * Mod2) * SameType * ComType1 * ComType2 * Random / 100);

	return DMG;
}

float CPokemon::IS_SameType(POKEMON_TYPE _arrType[], POKEMON_TYPE _SkillType)
{
	if ((_arrType[0] == _SkillType)
		|| (_arrType[1] == _SkillType))
	{
		return 1.5f;
	}
	else
	{
		return 1.0;
	}
}

UINT CPokemon::DmgRand()
{
	srand(time(NULL));
	UINT Randomi = rand() % 16 + 85; // 85 ~ 100 사이의 수를 생성해준다.
	return Randomi;
}


void CPokemon::Hit(UINT _DMG)
{
	if ((m_tMonsterInfo.m_CurHP == 0) || (m_tMonsterInfo.m_CurHP < _DMG))
	{
		m_tMonsterInfo.m_CurHP = 0;
	}
	else
	{
		m_tMonsterInfo.m_CurHP -= _DMG;
	}
}