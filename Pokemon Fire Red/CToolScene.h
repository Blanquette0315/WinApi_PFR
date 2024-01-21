#pragma once
#include "CScene.h"

enum class TOOL_MODE
{
    OBJECTPOS,
    COLLIDER,
    ANIMATION,
    NONE,
};

enum class BACKGROUND_TYPE
{
    PALLET,
    ROAD1,
    VIRIDIAN,
    PEWTER,

    REDHOUSESCENE1F,
    REDHOUSESCENE2F,
    GREENHOUSESCENE,
    OAKLABSCENE,

    HOUSE1SCENE,
    HOUSE2SCENE,
    CENTERSCENE1F,
    CENTERSCENE2F,
    MARTSCENE,
    HOUSEBLACKROOFSCENE,
    MUSEUMSCENE1F,
    MUSEUMSCENE2F,
    PEWTERGYMSCENE,

    END,
};

class CPanelUI;

class CToolScene :
    public CScene
{
private:
    TOOL_MODE        m_eMode;
    CObject*         m_vAllObject[(UINT)OBJECT_TYPE::END];
    CUI*             m_pFocusUI;
    UINT             m_iCurObject;

    // Obeject Mode 관련
    vector<tObjectInfo>     m_arrObjectInfo;
    vector<LAYER_TYPE>       m_arrObjectLayerType;  // 배치 할때 해당 오브젝트가 어떤 레이어에 있는지 알기 위해 만듬
    vector<OBJECT_TYPE>      m_arrObjectType;       // 오브젝트 타입을 전달해줘 new로 할당할 것이기 때문 (Scene에서)
    vector<CObject*>         m_arrObjectPut;        // 현재 작업중인 Scene배경에 배치된 오브젝트 목록들입니다.
    Vec2                     m_NowPos;              // 지금 포지션
    LAYER_TYPE               m_eLayerType;          // 데이터에 전송시켜줄 오브젝트 레이어 정보
    UINT                     m_iObjectCount;        // 전달할 오브젝트의 총 갯수
    CButtonUI*               m_pSelectObjectButton; // 오브젝트 모드 오브젝트 셀렉 버튼의 주소
    UINT                     m_iCurScene;           // 지금 작업중인 Scene을 파악하기 위한 변수
    CObject*                 m_pBackGround;         // 작업할 Scene의 배경을 넣어주기 위해 가지고 있는 주소

    // ColliderMode 관련
    vector<tCollider_Info>   m_arrColliderInfo;
    RECT             m_rCollider;
    COLLIDER_TYPE    m_eColliderType;
    UINT             m_COUNT;
    bool             m_IS_Render;
    Vec2             m_vPos;

    tCollider_Info   m_arrLoadColl[MaxCollider];

    // BackGround Collider 관련
    

private:
    void CreateObject();
    CObject* NewObject(UINT _i);
    void ObjectMode();
    void ColliderMode();

    void CreateUI();
    void CreateColldierUI();
    void CreateObjectUI();

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void enter() override;
    virtual void exit() override;

public:
    // 공용
    void CloseUI();

    // Object Mode
    void ObjectSave();
    void ObjectLoad();
    void SelectObject();
    void SetPlayerType();
    void SetEnvironmentType();
    void SetNPCType();
    void PrevObject();
    void SetObjectPos();
    void NextObject();
    void ClickPos();

    // Collider Mode
    void SetColliderDef() { m_eColliderType = COLLIDER_TYPE::DEFAULT; }
    void SetColliderRerender() { m_eColliderType = COLLIDER_TYPE::RE_RENDER; }
    void SetColliderEvent() { m_eColliderType = COLLIDER_TYPE::EVENT; }
    void ColliderSave();
    void ColliderLoad();
    void SetCollider();


public:
    CToolScene();
    ~CToolScene();
};

