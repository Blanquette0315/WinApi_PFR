#pragma once
#include "CComponent.h"

class CAnimation;
class CImage;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;
    CAnimation* m_pCurAnim;
    vector<CAnimation*> m_arrMultAnim;

    bool                        m_bRepeat;      // 반복재생
    bool                        m_bMult;        // 실행시킨게 멀티 애니메이션인지

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    void CreateAnimation(const wstring& _strName, CImage* _pImage
        , Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true);

    void CreateAnimationY(const wstring& _strName, CImage* _pImage
        , Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true);

    CAnimation* FindAnimation(const wstring& _strKey);
    void Play(const wstring& _strName, bool _bRepeat);

    // 에니메이션을 이어서 실행해주는 함수
    void CuntinuePlay(const wstring& _strName, bool _bRepeat);

    // 애니메이션의 첫 장면을 셋팅해주면서 애니메이션을 실행해주는 함수
    void Play(const wstring& _strName, UINT _iSetFrm, bool _bRepeat);

    void ReSetCurAnim() { m_pCurAnim = nullptr; }


public:
    void AddMultAnim(const wstring& _strName);
    void PlayMultAnim(bool _bRepeat);
    void CuntinuePlayMultAnim(bool _bRepeat);
    void MultOff() { m_bMult = false; }

public:
    CLONE(CAnimator);

public:
    CAnimator();
    CAnimator(const CAnimator& _animator);
    ~CAnimator();
};

