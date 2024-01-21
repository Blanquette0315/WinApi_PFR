#pragma once
#include "CObject.h"

// ������ ���������� BackGround�� ������ �� ����Ѵ�.
// ������ Scene���� �ش� Ŭ������ ��ü�� ����� BGI�� �����.

class CBackGround :
    public CObject
{
private:
    CImage*     m_pBackImage; // BackGround Image �ּ�

public:
    virtual void SetImage(wstring _pImage) override;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CBackGround();
   virtual ~CBackGround();
};

