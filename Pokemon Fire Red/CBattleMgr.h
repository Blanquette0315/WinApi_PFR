#pragma once

class CPokemon;

class CBattleMgr
{
	SINGLE(CBattleMgr)
private:
	EFFECT_TYPE m_TypeMatrix[(UINT)POKEMON_TYPE::END][(UINT)POKEMON_TYPE::END];
	vector<CPokemon*> m_arrPlayerPokemon;
	CPokemon* m_pPlayerPokemon;
	CPokemon* m_pTargetPokemon;
	BATTLE_TYPE m_eBattleType; // 배틀씬 흐름 제어를 위해 가지고 있다.
	CUI* m_pMessageBox;
	int m_iRunRand;

private:
	float CompareType(POKEMON_TYPE _Type, POKEMON_TYPE _Target);

public:
	void SetPlayerPoke(CPokemon* _Pokemon) { m_pPlayerPokemon = _Pokemon; }
	void SetTargetPoke(CPokemon* _Pokemon) { m_pTargetPokemon = _Pokemon; }
	CPokemon* GetPlayerPoke() { return m_pPlayerPokemon; }

	int GetPokemonSize() { return m_arrPlayerPokemon.size(); }

	void PlayerPokemoninit(CPokemon* _obj);
	void BattleMgrEixt();
	CPokemon* GetVecPokemon(UINT _index);
	void ShiftPokemon(UINT _index);

	void SetMessageBox(CUI* _Box) { m_pMessageBox = _Box; }

	BATTLE_TYPE GetBattle_Type() { return m_eBattleType; }
	void SetBattle_Type(BATTLE_TYPE _Type) { m_eBattleType = _Type; m_pMessageBox->TextReset(); }

	int GetRunRand() { return m_iRunRand; }

public:
	bool IS_Player_First();

public:
	void Act(UINT _skindex);
	void ActSkill();

	void OtherAct();
	void OtherActSkill();

	void Run();
	void SetRunRand();

public:
	void init();
};

