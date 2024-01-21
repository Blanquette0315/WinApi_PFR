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

    bool                        m_bRepeat;      // �ݺ����
    bool                        m_bMult;        // �����Ų�� ��Ƽ �ִϸ��̼�����

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

    // ���ϸ��̼��� �̾ �������ִ� �Լ�
    void CuntinuePlay(const wstring& _strName, bool _bRepeat);

    // �ִϸ��̼��� ù ����� �������ָ鼭 �ִϸ��̼��� �������ִ� �Լ�
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

