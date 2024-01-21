#pragma once
#include "CObject.h"

// �÷��̾�� 3��Ī ������ ��Ʋ�������� ������.
// ���� 3��Ī ���������� �÷��̾� �������� ������ ���̴�.
// �÷��̾� ���ǵ� ����, �÷��̾� �浹 ����

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

