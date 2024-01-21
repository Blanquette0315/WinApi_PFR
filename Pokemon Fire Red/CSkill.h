#pragma once
#include "CObject.h"
class CSkill :
    public CObject
{
private:
    UINT m_Power;
    UINT m_MaxPP;
    UINT m_CurPP;
    float m_Accuracy;       // 명중률 float으로 100분률로 사용할 예정
    POKEMON_TYPE m_SkillType;
    CPokemon* m_pOwnerPokemon;

    UINT m_AType;           // 어택 타입이 0이면 물리, 1이면 특수이다.
    UINT m_Priority;        // 우선도 0일 경우 일반적, 1일 경우 제일 먼저

public:
    void SetSkillInfo(UINT _Power, UINT _MaxPP, float _Accuracy, POKEMON_TYPE _SkilType, UINT _AType, UINT _Priority);

    virtual UINT GetCurPP() override { return m_CurPP; }
    UINT SetCurPP(UINT _CurPP) { m_CurPP = _CurPP; }

    virtual UINT GetPower()     override { return m_Power; }
    virtual UINT GetAccuracy() override { return m_Accuracy; }
    virtual UINT GetPriority() override { return m_Priority; }
    virtual UINT GetAType()     override { return m_AType; }
    virtual POKEMON_TYPE GetSkillType() { return m_SkillType; }

    virtual UINT GetMaxPP()     override { return m_MaxPP; }
    // UINT GetType() { return m_Power; }

    virtual void SkillAct();
    virtual void SetSkillPos(Vec2 _StartPos, Vec2 _EndPos) {};
    virtual bool IS_Animation_End() { return false; };

    void SetOwnerPokemon(CPokemon* _Owner) { m_pOwnerPokemon = _Owner; }
    CPokemon* GetOwnerPokemon() { return m_pOwnerPokemon; }

    const wstring GetWsSkillType();
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CSkill();
    ~CSkill();
};

