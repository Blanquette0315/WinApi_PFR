#pragma once
#include "CObject.h"

// !!!!!!환경체들의 Pos 기준은 하단 중심으로 할 것이다.!!!!!!!

// 환경 오브젝트들의 부모 클래스로 추상 클래스이다.
// 환경 오브젝트의 리소스들은 각각의 자식에서 설계할 것이다.

// 환경 오브젝트들의 Collider는 여기서 그려줄 것이다.
// 또한 환경 오브젝트들의 Collider는 최대 6개까지 가질 수 있게 만들 것이다.

// 주의할 점!!! 환경체들은 AddComponent로 Collider를 넣으면 안된다.
// 예외 처리 해주어야함.

class CEnvironment :
    public CObject
{
private:
    CImage*                     m_pImage;                    // render 해야할 Image

    vector<CComponent*>                 m_arrCollider;  // Collider를 관리해준다.
    UINT                        CurCount;                    // 현재 가지고 있는 Collider의 갯수
    vector<FianlInfo>                   m_tFianlInfo;   // 파일에서 얻어온 콜라이더 정보
public:
    void AddCollider(CComponent* _pComponent);
    void AddCollider(const wstring& _strRelativePath);
    void ColliderLoad(const wstring& _strRelativePath);

    virtual CCollider* GetCollider(UINT _indx) const { return (CCollider*)m_arrCollider[_indx]; }
    virtual UINT GetVectorSize() { return m_arrCollider.size(); }

    // void ImageRerender(HDC _dc);
    // virtual void SetImage(wstring _pImage) override;

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override {}
    virtual void CollisionOverlap(CCollider* _pOtherCollider) override {}
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) override {}

public:
    virtual void tick() override;           // Object의 tick()을 수행한 후, tick()을 수행해줄 것이다.
    virtual void render(HDC _dc) override;  // Object의 render()를 수행한 후, render()를 수행해줄 것이다.

public:
    CEnvironment();
    virtual ~CEnvironment();
};

