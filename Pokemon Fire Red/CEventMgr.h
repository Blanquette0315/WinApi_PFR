#pragma once

class CUI;

class CEventMgr
{
	SINGLE(CEventMgr);
private:
	vector<tEventInfo>	m_vecEvent;
	//vector<CObject*>	m_vecRenderObejct;
	map< UINT, CObject*> m_mapRenderObject;
	vector<CObject*>	m_vecDeadObj;
	UINT	m_ReRenderEventCount;
	UINT	m_DeleteRenderEventCount;

public:
	UINT GetCount() { return m_ReRenderEventCount; }
	void SetCount(UINT _Count) { m_ReRenderEventCount = _Count; }
public:
	void tick();
	void render(HDC _dc);
	void AddEvent(const tEventInfo& _event) { m_vecEvent.push_back(_event); }

	void Re_Render(CObject* _pObj);
	void EventDeleteRe_Render(CObject* _pObj);
	void EventSetUIFocus(CUI* _pObj);

	void DeleteReRenderM();
};

