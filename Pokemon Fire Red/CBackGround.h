#pragma once
#include "CObject.h"

// 각각의 스테이지의 BackGround를 생성할 때 사용한다.
// 각각의 Scene에서 해당 클래스로 객체를 만들어 BGI를 만든다.

class CBackGround :
    public CObject
{
private:
    CImage*     m_pBackImage; // BackGround Image 주소

public:
    virtual void SetImage(wstring _pImage) override;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CBackGround();
   virtual ~CBackGround();
};

