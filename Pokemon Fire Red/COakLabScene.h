#pragma once
#include "CScene.h"
class COakLabScene :
    public CScene
{
private:
    CSound* m_pEixtSound;
    CSound* m_pInSound;
    CBattleMessageBox* m_pMsgBox;
    bool m_bEvent;

public:
    virtual void SetEvent(bool _bool) override { m_bEvent = _bool; }
    virtual void AddPokemonEvent(int _i) override;

public:

    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    COakLabScene();
    ~COakLabScene();
};

