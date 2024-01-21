#pragma once
#include "CEntity.h"

class CObject;

class CScene :
    public CEntity
{
private:
	vector<CObject*>	m_arrLayer[MAX_LAYER];
	vector<tObjectInfo>			m_arrObjectInfo;
	bool m_bMenu_ON;

public:
	void AddObject(CObject* _pObject, LAYER_TYPE _eLayer) { m_arrLayer[(UINT)_eLayer].push_back(_pObject); }
	const vector<CObject*>& GetObjects(LAYER_TYPE _eType){ return m_arrLayer[(UINT)_eType];	}

	void SetMenuOn(bool _bool) { m_bMenu_ON = _bool; }
	bool GetMenuISOn() { return m_bMenu_ON; }
public:
	// UI
	virtual void AddPokemonEvent(int _i) {};
	void DeleteUIObject();
	void SetFocusedUI(CObject* _pUI);

public:
	virtual void tick();
	virtual void render(HDC _dc);

	// Scene 진입 시 호출
	virtual void enter() = 0;

	// Scene 나올 때 호출
	virtual void exit() = 0;

	Vec2 SavePrevScenePos();

public:
	// 가방 UI를 생성해주기 위한 함수.
	void NewBackPackUI();

public:
	virtual void SetEvent(bool _bool) {};

protected:
	void DeleteAllObject();
	void DeleteObject(LAYER_TYPE _eType);

	void AddLoadObject(const wstring& _strRelativePath);

	CObject* GetPlayer() { return m_arrLayer[(UINT)LAYER_TYPE::PLAYER][0]; }

private:
	void ObjectLoad(const wstring& _strRelativePath);
	CObject* NewObject(UINT _Type);
public:
	CScene();
	virtual ~CScene();
};

