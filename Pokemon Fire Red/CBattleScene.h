#pragma once
#include "CScene.h"
class CBattleScene :
    public CScene
{
private:
    //CImage* m_pImage;
    //EFFECT_TYPE m_TypeMatrix[(UINT)POKEMON_TYPE::END][(UINT)POKEMON_TYPE::END];
    CSound* m_pBGM;
    CSound* m_pWinBGM;
    CUI* m_pPlayerPokemonInfo;
    CUI* m_pMonsterInfo;
    CUI* m_pMessageBox;
    CPokemon* m_pPlayerPokemon;
    CPokemon* m_pTargetPokemon;
    CObject* m_pPlayer;
    float m_fDuration;
    bool m_bActionBoxOn;
    bool m_Select;
    bool m_bSceneAnim;
    bool m_bEXP;
    bool m_bWinSound;

private:
    // Info Box에 결과 반영 함수
    void SetResult();


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CBattleScene();
    ~CBattleScene();
};

