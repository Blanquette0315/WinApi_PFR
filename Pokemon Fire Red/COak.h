#pragma once
#include "CEnvironment.h"

enum class LBRT
{
    LEFT,
    BOT,
    RIGHT,
    TOP,
};

class COak :
    public CEnvironment
{
private:
    CImage* m_pImage;
    bool IS_Collision;
    UINT m_iRe_render;
    LBRT m_eLBRT;
    bool m_bEvent;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) override;

public:
    COak();
    virtual ~COak();
};

