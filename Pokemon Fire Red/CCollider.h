#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2            m_vOffsetPos;   // Object �� ���� ������� �Ÿ� (Player�� Collider�� ���� ���� ��´�.)
    Vec2            m_vScale;       // Collider�� ũ��
    Vec2            m_vFinalPos;    // �浹ü�� ���� ��ġ

    COLLIDER_TYPE   m_eColliderType;

    int             m_iCollisionCount; // �浹 Ƚ��

public:
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    void SetOffset(Vec2 _vOffset) { m_vOffsetPos = _vOffset; }

    Vec2 GetFinalPos() const { return m_vFinalPos; }
    Vec2 GetScale() const { return m_vScale; }

public:
    void SetColliderType(COLLIDER_TYPE _ColliderType) { m_eColliderType = _ColliderType; }
    COLLIDER_TYPE GetColliderType() { return m_eColliderType; }
    int GetCollisionCount() { return m_iCollisionCount; }
public:
    // �浹 ���� �߻� �Լ�
    void CollisionBeginOverlap(CCollider* _pOtherCollider);
    void CollisionOverlap(CCollider* _pOtherCollider);
    void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
    CLONE(CCollider);

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CCollider();
    ~CCollider();
};

