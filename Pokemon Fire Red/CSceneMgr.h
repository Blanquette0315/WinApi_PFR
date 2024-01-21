#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	CScene* m_pCurScene;
	CScene* m_pPrevScene;

	vector<CPokemon*> m_arrNowPokemon;
	Vec2 PlayerPrevPos;

	ITEM_INFO m_arrItem[(UINT)ITEM_TYPE::REVIVE]; // 가지고 있는 아이템 정보 배열


public:
	ITEM_INFO* GetPlayerItem() { return m_arrItem; }

public:
	CPokemon* GetPokemon(int index);
	int GetPokemonSize() { return m_arrNowPokemon.size(); }
	void AddPokemon(CPokemon* _Obj);

public:
	CScene* GetCurScene() { return m_pCurScene; }

	Vec2 GetPlayerPrevPos() { return PlayerPrevPos; }

	void SetPrevScene(CScene* _Prev) { m_pPrevScene = _Prev; }
	CScene* GetPrevScene() { return m_pPrevScene; }

private:
	void ChangeScene(SCENE_TYPE _eNext);

public:
	void init();

	void tick();
	void render(HDC _dc);

	friend class CEventMgr;
};

