#pragma once

class CObject;
class CImage;

class CCameraMgr
{
	SINGLE(CCameraMgr);

private:
	Vec2					m_vResolution;	// 화면 해상도
	Vec2					m_vLook;		// 현재 카메라가 보고있는 좌표
	Vec2					m_vDiff;		// 화면 해상도 중심 좌표와 현재 카메라 Look 간에 차이
	Vec2					m_CameraRange;	// 카메라 범위를 잡아주기 위한 멤버 변수

	CObject* m_pTargetObj;

	// veil
	CImage* m_pVeil;		// 가림막 용도 BitmapImage 생성
	float					m_fAlpha;		// 투명 강도

	list<tCamEffectInfo>	m_CamEffectInfo;




public:
	void init();
	void tick();
	void render(HDC _dc);



public:
	Vec2 GetLookAt() { return m_vLook; }
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff.Changeint(); }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	Vec2 GetDiff() { return m_vDiff; }

	void SetCameraRange(Vec2 _vRange) { m_CameraRange = _vRange; }

	void CheckDiff();

	void SetTargetObject(CObject* _pObj) { m_pTargetObj = _pObj; }
	void SetCameraEffect(CAM_EFFECT _type, float _fDuration)
	{
		tCamEffectInfo info = {};
		info.eEffect = _type;
		info.fDuration = _fDuration;
		m_CamEffectInfo.push_back(info);
	}
};

