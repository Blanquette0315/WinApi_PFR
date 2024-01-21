#pragma once
#include "CEntity.h"
#include "CCameraMgr.h"

class CComponent;
class CAnimator;
class CCollider;
class CUI;

class CImage;

class CPokemon;

// Object������ ������Ʈ�� ��ġ������ �����Ѵ�.

class CObject :
    public CEntity
{
private:
    CComponent* m_arrComponent[(UINT)COMPONENT_TYPE::END];  // Object�� ������ �ִ� ������Ʈ
    Vec2        m_vPos;                                     // ��ġ�� ��ǥ
    Vec2        m_vScale;
    bool        m_bDead;

    bool        m_IS_TOOL;

public:
    Vec2 GetPos() { return m_vPos; }
    Vec2 GetScale() { return m_vScale; }
    void SetPos(Vec2 _Pos) { m_vPos = _Pos; }
    void SetScale(Vec2 _Scale) { m_vScale = _Scale; }

    CObject* GetAdress() { return this; }

    virtual Vec2 SavePrevScenePos() { return Vec2(0, 0); };

    bool IsDead() const { return m_bDead; }

    virtual void SetImage(wstring _pImage) {}   // Background �̹����� �־��ֱ� ���� �����Լ�
    
    virtual void SetPokSceneType(POKEMONSCENE_TYPE _PoSceneType) {};
    virtual void SetOwnerType(OWNER_TYPE _OwnerType) {};

    virtual bool GetIncapacity() { return false; };

public:
    virtual CPokemon* GetNowPokemon(UINT _index) { return nullptr; }; // �÷��̾ ������ �ִ� ���ϸ��� �������� �Լ�
    virtual UINT GetNowPokemonSize() { return 0; }
    virtual void AddPokemon(CPokemon* _Pokemon) {};

public:
    // ����
    virtual void SetImage(UINT _index) {};

public:

    virtual void SetText(const wstring& _str) {};

    virtual UINT GetCurLV() { return 0; };
    virtual UINT GetCurHP() { return 0; };
    virtual UINT GetMaxHP() { return 0; };
    virtual UINT GetCurExp() { return 0; };
    virtual UINT GetMaxExp() { return 0; };

public:
    virtual UINT GetCurPP() { return 0; }
    virtual UINT GetPower() { return 0; }
    virtual UINT GetAccuracy() { return 0; }
    virtual UINT GetPriority() { return 0; }
    virtual UINT GetAType() { return 0; }

    virtual UINT GetMaxPP() { return 0; }
    virtual SKILL_INFO GetSkillInfo() { return SKILL_INFO(); };


    void AddComponent(CComponent* _pComponent);
    virtual UINT GetVectorSize() { return 0; };

    void SetISTool() { m_IS_TOOL = true; }
    bool GetISTool() { return m_IS_TOOL; }

    CCollider* GetCollider() const { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]; }
    virtual CCollider* GetCollider(UINT _index) const { return 0; }

    CAnimator* GetAnimator() const { return (CAnimator*)m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR]; }
public:
    virtual void tick();
    virtual void render(HDC _dc); // Object�� Render�� Collider�� �׷��ش�.

    // �浹 �߻��� ȣ���� �Լ�
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) {};
    virtual void CollisionOverlap(CCollider* _pOtherCollider) {};
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) {};

private:
    void SetDead() { m_bDead = true; }

public:
    CObject();
   virtual ~CObject();

    friend class CEventMgr;
};

