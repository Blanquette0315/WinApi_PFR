#pragma once
#include "CObject.h"

// 플레이어는 3인칭 시점과 배틀씬에서로 나뉜다.
// 먼저 3인칭 시점에서의 플레이어 움직임을 구현할 것이다.
// 플레이어 스피드 관리, 플레이어 충돌 관리

class CPokemon;

class CPlayer :
    public CObject
{
private:
    CImage* m_pPlayerAtlas;
    float m_fSpeed;
    Vec2 DeltaPos;
    Vec2 PrevPos;
    bool wallcollision;
    
    bool m_bAnim;
    Vec2 m_vWASD;

    vector<CPokemon*> m_arrNowPokemon;
    vector<CPokemon*> m_arrPCPokemon;

public:
    virtual void AddPokemon(CPokemon* _Pokemon) override { m_arrNowPokemon.push_back(_Pokemon); }

public:
    virtual CPokemon* GetNowPokemon(UINT _index) override;
    virtual UINT GetNowPokemonSize() override { return m_arrNowPokemon.size(); }

    virtual Vec2 SavePrevScenePos() override { return GetPos(); }
public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) override;

public:
    virtual void tick() override;
   // virtual void render(HDC _dc) override;
public:
    CPlayer();
    ~CPlayer();
};

