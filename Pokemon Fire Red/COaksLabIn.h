#pragma once
#include "CEnvironment.h"
class COaksLabIn :
    public CEnvironment
{
private:
    CImage* m_pImage;
    bool IS_Collision;
    bool IS_Event;

public:

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) override;


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    COaksLabIn();
    ~COaksLabIn();
};

