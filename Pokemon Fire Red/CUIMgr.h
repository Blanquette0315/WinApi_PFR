#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;
	CUI* m_pTargetUI;

public:
	void tick();

public:
	CUI* GetFocusedUI() { return m_pFocusedUI; }
	CUI* GetTargetUI() { return m_pTargetUI; }
	void clear()
	{
		m_pFocusedUI = nullptr;
		m_pTargetUI = nullptr;
	}

private:
	CUI* FindTargetUI(CUI* _pParentUI);
};

