#include "pch.h"
#include "CPokemon.h"

#include "CSkill.h"

CPokemon::CPokemon()
	: m_tMonsterInfo{}
	, m_bIS_LevelUp(false)
	, m_bIs_Incapacity(false)
	, m_arrPokemonType{} // 0���� �ʱ�ȭ �ǹǷ� NONE�� ����.
	, m_arrSkill{}
	, m_pTargetSkill(0)
	, m_eOwnerType(OWNER_TYPE::WILD) // �⺻���δ� �߻��� ����.
	, m_eSceneType(POKEMONSCENE_TYPE::NONE)
{
}

CPokemon::~CPokemon()
{
	Safe_Del_Map(m_arrSkill);
}

void CPokemon::tick()
{
	// HP�� 0���� üũ�ؼ� 0�� ��� ���� �Ҵ� ������ ���־�� �Ѵ�.
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

// ����ġ ���� �Լ�

void CPokemon::AddBattleExp(UINT _OtherLv, UINT _MonCount)
{
	// ���� ���� �� ����ġ �߰� ��� ������ � �������� �߰����־�� �Ѵ�.
	m_tMonsterInfo.m_CurExp += ((30 * _OtherLv) / (7* _MonCount));

	// ����ġ ȹ�� �� �������� ���� ���
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
		// ���� �������� ���� ��� ��Ʋ Scene���� �˷��� �������� �ߴٴ� ���� �˷��� �Ѵ�.
		// �׷��� ��Ʋ������ �˸��� �ؽ�Ʈ UI�� ����ش�.
	}
}

// �̻��� ���� ���ÿ��� �� �Լ��� ȣ�����ָ� �ȴ�.
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

// ����ġ �䱸�� ���
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

// ��ų ���� �Լ�
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

	// ��ų �̸�
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

// ���� ���� �Լ�
// ������ �� �� ��� Ÿ��, ���, Ư���� ���ڷ� �޾� ����� �� �Ѱ��ش�.

UINT CPokemon::Attack(UINT _SkillPower, POKEMON_TYPE _SkillType, UINT _AType, UINT _Defence, UINT _SDefence
					,float _ComType1, float _ComType2 )
{
	// ������ �������� ����� ��� �� ��뿡�� �Ѱ��༭ ���� �ش� �������� Hit�� ����� ���� HP�� ��´�.

	// ���� ���
	float Lv = ((m_tMonsterInfo.m_CurLV) * 2 / 5 + 2);

	// ���� ���
	float Power = _SkillPower;

	// ���� �� Ư�� ���
	float Atteck = 0;
	if (_AType == 0)
		Atteck = m_tMonsterInfo.m_Atteck;
	else if (_AType == 1)
		Atteck = m_tMonsterInfo.m_SAtteck;

	// ��� �� Ư�� ���
	float Defence = 0;
	if (_AType == 0)
		Defence = _Defence;
	else if (_AType == 1)
		Defence = _SDefence;

	// Mod1 ���
	float Mod1 = 1;

	// �޼� ���
	float Critical = 1;

	// Mod2 ���
	float Mod2 = 1;

	// �ڼӺ��� ���
	float SameType = IS_SameType(m_arrPokemonType, _SkillType);

	// Ư�� �� ���
	float ComType1 = _ComType1;
	float ComType2 = _ComType2;

	//������ ���
	float Random = DmgRand();

	// ������ = (((((((���� * 2 / 5) + 2) * ���� * ���� / 50) / ���) * Mod1) + 2) * [[�޼�]] * Mod2) * �ڼӺ��� * ��1
	//			* ��2 * ������ / 100)
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
	UINT Randomi = rand() % 16 + 85; // 85 ~ 100 ������ ���� �������ش�.
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