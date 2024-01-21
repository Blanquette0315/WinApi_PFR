#pragma once
#include "CEnvironment.h"
class CMuseumStand2 :
    public CEnvironment
{
private:
    CImage* m_pImage;
    bool IS_Collision;
    UINT m_iRe_render;

public:

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) override;


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CMuseumStand2();
    virtual ~CMuseumStand2();
};

