#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2            m_vOffsetPos;   // Object 로 부터 상대적인 거리 (Player의 Collider는 발을 기준 삼는다.)
    Vec2            m_vScale;       // Collider의 크기
    Vec2            m_vFinalPos;    // 충돌체의 최종 위치

    COLLIDER_TYPE   m_eColliderType;

    int             m_iCollisionCount; // 충돌 횟수

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
    // 충돌 관련 발생 함수
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

