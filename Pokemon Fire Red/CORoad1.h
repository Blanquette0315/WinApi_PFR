#pragma once
#include "CEnvironment.h"
class CORoad1 :
    public CEnvironment
{
private:
    CImage* m_pBackImage; // BackGround Image аж╪р

public:
    virtual void SetImage(wstring _pImage) override;

public:

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) override;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CORoad1();
    virtual ~CORoad1();
};

