#pragma once

class CImage;

class CEngine
{
	SINGLE(CEngine);
private:
	HWND			m_hMainWindow;	// ���� ������ �ڵ鰪
	HDC				m_hDC;			// ���� DC �ڵ鰪

	POINT			m_ptResolution;	// �ػ�
	CImage*			m_pBackBuffer;	// ����� ���߹��� �뵵

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

