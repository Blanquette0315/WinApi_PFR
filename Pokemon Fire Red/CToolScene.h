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

    // Obeject Mode ����
    vector<tObjectInfo>     m_arrObjectInfo;
    vector<LAYER_TYPE>       m_arrObjectLayerType;  // ��ġ �Ҷ� �ش� ������Ʈ�� � ���̾ �ִ��� �˱� ���� ����
    vector<OBJECT_TYPE>      m_arrObjectType;       // ������Ʈ Ÿ���� �������� new�� �Ҵ��� ���̱� ���� (Scene����)
    vector<CObject*>         m_arrObjectPut;        // ���� �۾����� Scene��濡 ��ġ�� ������Ʈ ��ϵ��Դϴ�.
    Vec2                     m_NowPos;              // ���� ������
    LAYER_TYPE               m_eLayerType;          // �����Ϳ� ���۽����� ������Ʈ ���̾� ����
    UINT                     m_iObjectCount;        // ������ ������Ʈ�� �� ����
    CButtonUI*               m_pSelectObjectButton; // ������Ʈ ��� ������Ʈ ���� ��ư�� �ּ�
    UINT                     m_iCurScene;           // ���� �۾����� Scene�� �ľ��ϱ� ���� ����
    CObject*                 m_pBackGround;         // �۾��� Scene�� ����� �־��ֱ� ���� ������ �ִ� �ּ�

    // ColliderMode ����
    vector<tCollider_Info>   m_arrColliderInfo;
    RECT             m_rCollider;
    COLLIDER_TYPE    m_eColliderType;
    UINT             m_COUNT;
    bool             m_IS_Render;
    Vec2             m_vPos;

    tCollider_Info   m_arrLoadColl[MaxCollider];

    // BackGround Collider ����
    

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
    // ����
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

