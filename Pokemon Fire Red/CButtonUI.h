#pragma once
#include "CUI.h"

typedef void(*PFUNC)(void);
typedef void(*PFUNC1)(DWORD_PTR);
typedef void(*PFUNC2)(DWORD_PTR, DWORD_PTR);

typedef void(CEntity::* DELEGATE_FUNC)(void);
typedef void(CEntity::* DELEGATE_FUNC1)(DWORD_PTR);
typedef void(CEntity::* DELEGATE_FUNC2)(DWORD_PTR, DWORD_PTR);

struct BtnDelegate
{
    CEntity* pInst;
    DELEGATE_FUNC   pFunc;

    bool IsValid()
    {
        if (pInst && pFunc)
            return true;
        return false;
    }

    BtnDelegate()
        : pInst(nullptr)
        , pFunc(nullptr)
    {}
};

class CImage;

class CButtonUI :
    public CUI
{
private:
    // 함수 포인터
    PFUNC       m_pFuncPointer;
    BtnDelegate m_Delegate;

    CImage*     m_pImage;

public:

    // 델리게이트 구조를 사용할지 콜백 구조를 사용할지는 선택해서 함수 정리할 것.
    void SetCallBack(PFUNC _pCallBack)
    {
        m_pFuncPointer = _pCallBack;
    }

    void SetDeletage(CEntity* _pInst, DELEGATE_FUNC _pFunc)
    {
        m_Delegate.pInst = _pInst;
        m_Delegate.pFunc = _pFunc;
    }

    void SetImage(CImage* _pImage) { m_pImage = _pImage; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void LBtnClicked() override;

public:
    CLONE(CButtonUI)

public:
    CButtonUI();
    ~CButtonUI();
};

