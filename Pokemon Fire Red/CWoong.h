#pragma once
#include "CEnvironment.h"
class CWoong :
    public CEnvironment
{
private:
    CImage* m_pImage;
    bool IS_Collision;
    UINT m_iRe_render;
    bool m_bEvent;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) override;

public:
    CWoong();
    virtual ~CWoong();
};

