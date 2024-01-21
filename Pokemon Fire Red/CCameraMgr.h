#pragma once

class CObject;
class CImage;

class CCameraMgr
{
	SINGLE(CCameraMgr);

private:
	Vec2					m_vResolution;	// ȭ�� �ػ�
	Vec2					m_vLook;		// ���� ī�޶� �����ִ� ��ǥ
	Vec2					m_vDiff;		// ȭ�� �ػ� �߽� ��ǥ�� ���� ī�޶� Look ���� ����
	Vec2					m_CameraRange;	// ī�޶� ������ ����ֱ� ���� ��� ����

	CObject* m_pTargetObj;

	// veil
	CImage* m_pVeil;		// ������ �뵵 BitmapImage ����
	float					m_fAlpha;		// ���� ����

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

