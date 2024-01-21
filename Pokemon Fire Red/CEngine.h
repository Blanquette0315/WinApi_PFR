#pragma once

class CImage;

class CEngine
{
	SINGLE(CEngine);
private:
	HWND			m_hMainWindow;	// 메인 윈도우 핸들값
	HDC				m_hDC;			// 메인 DC 핸들값

	POINT			m_ptResolution;	// 해상도
	CImage*			m_pBackBuffer;	// 백버퍼 이중버퍼 용도

	HPEN			m_arrPen[(UINT)PEN_COLOR::END];
	HBRUSH			m_arrBrush[(UINT)BRUSH_COLOR::END];

	bool			m_bTickOnce;

public:
	void init(HWND _hwnd, UINT _Width, UINT _Hight); 
	void tick();

public:
	HWND GetMainHwnd() { return m_hMainWindow; };
	HDC GetMainDC() { return m_hDC; }
	HPEN GetPen(PEN_COLOR _color) { return m_arrPen[(UINT)_color]; }
	HBRUSH GetBrush(BRUSH_COLOR _brush) { return m_arrBrush[(UINT)_brush]; }

	POINT GetResolution() { return m_ptResolution; }

	void SetTickOnce(bool _bool) { m_bTickOnce = _bool; }
	bool GetTickOnce() { return m_bTickOnce; }

private:
	void CreateDefaultGDIObject();
};

