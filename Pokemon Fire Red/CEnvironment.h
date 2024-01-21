#pragma once
#include "CObject.h"

// !!!!!!ȯ��ü���� Pos ������ �ϴ� �߽����� �� ���̴�.!!!!!!!

// ȯ�� ������Ʈ���� �θ� Ŭ������ �߻� Ŭ�����̴�.
// ȯ�� ������Ʈ�� ���ҽ����� ������ �ڽĿ��� ������ ���̴�.

// ȯ�� ������Ʈ���� Collider�� ���⼭ �׷��� ���̴�.
// ���� ȯ�� ������Ʈ���� Collider�� �ִ� 6������ ���� �� �ְ� ���� ���̴�.

// ������ ��!!! ȯ��ü���� AddComponent�� Collider�� ������ �ȵȴ�.
// ���� ó�� ���־����.

class CEnvironment :
    public CObject
{
private:
    CImage*                     m_pImage;                    // render �ؾ��� Image

    vector<CComponent*>                 m_arrCollider;  // Collider�� �������ش�.
    UINT                        CurCount;                    // ���� ������ �ִ� Collider�� ����
    vector<FianlInfo>                   m_tFianlInfo;   // ���Ͽ��� ���� �ݶ��̴� ����
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
    virtual void tick() override;           // Object�� tick()�� ������ ��, tick()�� �������� ���̴�.
    virtual void render(HDC _dc) override;  // Object�� render()�� ������ ��, render()�� �������� ���̴�.

public:
    CEnvironment();
    virtual ~CEnvironment();
};

