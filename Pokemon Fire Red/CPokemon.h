#pragma once
#include "CObject.h"

class CSkill;

class CPokemon :
    public CObject
{
private:
    Monster_Info    m_tMonsterInfo;
    OWNER_TYPE      m_eOwnerType;
    CSkill*         m_pTargetSkill;
    POKEMON_TYPE    m_arrPokemonType[2];
    POKEMONSCENE_TYPE m_eSceneType;
    map<UINT, CSkill*> m_arrSkill; // 스킬은 최대 4개까지 가지고 있을 수 있다.
    Vec2            m_vPrevPos;
    bool            m_bIS_LevelUp;
    bool            m_bIs_Incapacity;

private:
    // 레벨업에 따른 스텟 변화 적용
    void StatsUpDate();
    void UpDateMaxEXP();

public:
    virtual bool GetIncapacity() override { return m_bIs_Incapacity; }

public:
    virtual void SetIOType(POKEMON_IO_TYPE _Type) {};
    virtual void SetIOAnimOnce() {};
    virtual bool GetIOAnimOnce() { return false; }

public:
    void SetUIPrevPos() { m_vPrevPos = GetPos(); }
    Vec2 GetUIPrevPos() { return m_vPrevPos; }
    void SetUIPos(Vec2 _Pos) { SetPos(_Pos); }

public:
    virtual UINT GetCurLV() override { return m_tMonsterInfo.m_CurLV; }
    virtual UINT GetCurHP() override { return m_tMonsterInfo.m_CurHP; }
    virtual UINT GetMaxHP() override { return m_tMonsterInfo.m_MaxHP; }
    virtual UINT GetCurExp() override { return m_tMonsterInfo.m_CurExp; }
    virtual UINT GetMaxExp() override { return m_tMonsterInfo.m_MaxExp; }

    UINT GetDefence() { return m_tMonsterInfo.m_Defence; }
    UINT GetSDefence() { return m_tMonsterInfo.m_SDefence; }
    UINT GetSpeed() { return m_tMonsterInfo.m_Speed; }

    POKEMON_TYPE GetPokeType1() { return m_arrPokemonType[0]; }
    POKEMON_TYPE GetPokeType2() { return m_arrPokemonType[1]; }
    
    void SetBaseStats(UINT _MaxHP, UINT _Atteck, UINT _Defence, UINT _Speed, UINT _SAtteck, UINT _SDefence);
    void SetCurLv(UINT _CurLV) { m_tMonsterInfo.m_CurLV = _CurLV; }

    void SetPokemonType(POKEMON_TYPE _Type1, POKEMON_TYPE _Type2);

    virtual void SetAddPos() {};
public:
    void AddSkill(UINT _strKey, CSkill* _Skill);
    virtual SKILL_INFO GetSkillInfo() override;
    CSkill* GetSkill(UINT _i);
    CSkill* GetRandSkill();
    void SetTargetSkill(CSkill* _Skill) { m_pTargetSkill = _Skill; }
    CSkill* GetTargetSkill() { return m_pTargetSkill; }
public:
   virtual void SetOwnerType(OWNER_TYPE _OwnerType) { m_eOwnerType = _OwnerType; }
    OWNER_TYPE GetOwnerType() { return m_eOwnerType; }
    virtual void SetPokSceneType(POKEMONSCENE_TYPE _PoSceneType) { m_eSceneType = _PoSceneType; }
    POKEMONSCENE_TYPE GetPokSceneType() { return m_eSceneType; }
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    void AddBattleExp(UINT _OtherLv, UINT _MonCount);
    void LevelUP();

public:
    UINT Attack(UINT _SkillPower, POKEMON_TYPE _SkillType, UINT _AType, UINT _Defence, UINT _SDefence
        , float _ComType1, float _ComType2);
    void Hit(UINT _DMG);
    float IS_SameType(POKEMON_TYPE _arrType[], POKEMON_TYPE _SkillType);
    UINT DmgRand();

public:
    CPokemon();
    ~CPokemon();
};