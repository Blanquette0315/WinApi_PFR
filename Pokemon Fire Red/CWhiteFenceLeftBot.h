#pragma once
#include "CEnvironment.h"
class CWhiteFenceLeftBot :
    public CEnvironment
{
private:
    CImage* m_pImage;
    bool IS_Collision;
    UINT m_iRe_render;

public:
    void SetRerender(UINT _I) { m_iRe_render = _I; }
    UINT GetRerender() { return m_iRe_render; }

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) override;


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CWhiteFenceLeftBot();
    virtual ~CWhiteFenceLeftBot();
};

