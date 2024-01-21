#pragma once
// ==================
// ==     공용     ==
// ==================

struct Fint
{
	int i1;
	int i2;
	int i3;
	int i4;

public:
	Fint(int _i1, int _i2, int _i3, int _i4)
		: i1(_i1)
		, i2(_i2)
		, i3(_i3)
		, i4(_i4)
	{}
};

struct Vector2
{
	float x;
	float y;

public:
	bool IsZero()
	{
		if (0.f == x && 0.f == y)
			return true;
		return false;
	}


	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float fLength = Length();

		assert(fLength);

		x /= fLength;
		y /= fLength;

		return *this;
	}

	float Distance(Vector2 _vOther)
	{
		float _x = x - _vOther.x;
		float _y = y - _vOther.y;

		return sqrtf(_x * _x + _y * _y);
	}

	float Dot(Vector2 _vOther)
	{
		return x * _vOther.x + y * _vOther.y;
	}

	Vector2 Changeint()
	{
		x = (int)x;
		y = (int)y;
		return *this;
	}

	Vector2 operator + (Vector2 _vOther)
	{
		return Vector2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vector2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vector2 operator -()
	{
		return Vector2(-x, -y);
	}

	Vector2 operator - (const Vector2 _vOther) const
	{
		return Vector2(x - _vOther.x, y - _vOther.y);
	}

	void operator -= (Vector2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	void operator -= (float _f)
	{
		x -= _f;
		y -= _f;
	}

	Vector2 operator * (float _f)
	{
		return Vector2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

	Vector2 operator * (Vector2 _v)
	{
		return Vector2(x * _v.x, y * _v.y);
	}

	Vector2 operator / (const float _f)
	{
		assert(_f != 0.f);

		return Vector2(x / _f, y / _f);
	}

	void operator /= (float _f)
	{
		assert(_f != 0.f);

		x /= _f;
		y /= _f;
	}

	Vector2 operator / (Vector2 _v)
	{
		assert(_v.x != 0.f && _v.y != 0.f);

		return Vector2(x / _v.x, y / _v.y);
	}

	void operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

public:
	Vector2()
		: x(0.f)
		, y(0.f)
	{}

	Vector2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vector2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	~Vector2() {}
};
typedef Vector2 Vec2;

// Pen과 Brush 설정을 위한 구조체
struct tSelectPen
{
private:
	HDC		m_hDC;
	HPEN	m_hPrevPen;

public:
	void SetPenColor(PEN_COLOR _color)
	{
		m_hPrevPen = (HPEN)SelectObject(m_hDC, CEngine::CreateMgr()->GetPen(_color));
	}

public:
	tSelectPen(HDC _dc)
		: m_hDC(_dc)
		, m_hPrevPen(0)
	{

	}

	tSelectPen(HDC _dc, PEN_COLOR _color)
		: m_hDC(_dc)
		, m_hPrevPen(0)
	{
		m_hPrevPen = (HPEN)SelectObject(m_hDC, CEngine::CreateMgr()->GetPen(_color));
	}

	~tSelectPen()
	{
		SelectObject(m_hDC, m_hPrevPen);
	}
};

struct tSelectBrush
{
private:
	HDC		m_hDC;
	HBRUSH	m_hPrevBrush;

public:
	tSelectBrush(HDC _dc, BRUSH_COLOR _color)
		: m_hDC(_dc)
		, m_hPrevBrush(0)
	{
		m_hPrevBrush = (HBRUSH)SelectObject(m_hDC, CEngine::CreateMgr()->GetBrush(_color));
	}

	~tSelectBrush()
	{
		SelectObject(m_hDC, m_hPrevBrush);
	}
};


// ==================
// ==    KeyMgr    ==
// ==================

struct Key_Info
{
	KEY_TYPE		_KType;
	KEY_STATE		_KState;
	bool			PrevPress;
};

// ==================
// ==   SceneMgr   ==
// ==================


// ==================
// ==   CEventMgr  ==
// ==================

struct tEventInfo
{
	EVENT_TYPE	eType;
	DWORD_PTR	first;
	DWORD_PTR	second;
};



// ==================
// ==    CObject   ==
// ==================

struct Monster_Info		// 포켓몬의 기초 스텟 정보
{
	UINT m_MaxLV;		// 최대 레벨
	UINT m_CurLV;		// 현재 레벨 정보

	UINT m_MaxHP;		// 최대 체력
	UINT m_CurHP;		// 현재 체력
		
	UINT m_MaxExp;		// 체워야할 경험치 : 레벨이 오를때 마다 해당 경험치 요구량이 증가한다.
	UINT m_CurExp;		// 현재 경험치 : 전투를 마치면 일정 경험치를 채워준다.

	UINT m_Atteck;		// 공격력 : 일반 공격의 데미지 계산에 사용
	UINT m_Defence;		// 방어력 : 일반 공격을 받을 시 데미지 계산에 사용
	UINT m_Speed;		// 스피드 : 스피드는 선공 기준을 잡아준다.
	UINT m_SAtteck;		// 특공   : 특수 공격의 데미지 계산에 사용 
	UINT m_SDefence;	// 특방   : 특수 공격을 받을 시 데미지 계산에 사용

	//UINT Base_Stats;	// 종족값

public:
	Monster_Info()
		: m_MaxLV(100)
		, m_CurLV(0)
		, m_MaxHP(0)
		, m_CurHP(0)
		, m_MaxExp(0)
		, m_CurExp(0)
		, m_Atteck(0)
		, m_Defence(0)
		, m_Speed(0)
		, m_SAtteck(0)
		, m_SDefence(0)
	{}
};


// ==================
// ==  CCameraMgr  ==
// ==================

struct tCamEffectInfo
{
	float		fAccTime;	// 누적 진행 시간
	float		fDuration;	// 이펙트 총 재생시간
	CAM_EFFECT	eEffect;	// 카메라 효과 타입
};

// ==================
// ==  CAnimation  ==
// ==================

struct tAnimFrm
{
	Vec2    vLeftTop;   // 이미지 내에서 좌상단 픽셀좌표
	Vec2    vSize;      // 좌상단으로부터 잘라낼 가로 세로 픽셀 길이    
	Vec2    vOffset;    // 출력 위치 오프셋
	float   fDuration;  // 해당 프레임 유지시간
};

// ==================
// ==   CCollider  ==
// ==================

union COLLIDER_ID
{
	struct
	{
		UINT LEFT_ID;
		UINT RIGHT_ID;
	};
	LONGLONG ID;
};

struct tCollider_Info
{
	RECT				rColliderPos;
	COLLIDER_TYPE		eColliderType;

public:
	tCollider_Info()
		: eColliderType(COLLIDER_TYPE::NONE)
	{
	}
};

struct FianlInfo
{
	Vec2 ColliderOffset; // 8
	Vec2 ColliderScale;	 // 8
	COLLIDER_TYPE Collider_Type;
};

// ==================
// ==    CScene    ==
// ==================

struct tObjectInfo
{
	Vec2		ObjectPos;
	LAYER_TYPE	ObjectLayer;
	OBJECT_TYPE ObjectType;
};

// ==================
// ==   SkillInfo  ==
// ==================

struct SKILL_INFO
{
	wstring	Skill01Name;
	wstring	Skill01MaxPP;
	wstring	Skill01CurPP;
	wstring	Skill01Type;

	wstring	Skill02Name;
	wstring	Skill02MaxPP;
	wstring	Skill02CurPP;
	wstring	Skill02Type;

	wstring	Skill03Name;
	wstring	Skill03MaxPP;
	wstring	Skill03CurPP;
	wstring	Skill03Type;

	wstring	Skill04Name;
	wstring	Skill04MaxPP;
	wstring	Skill04CurPP;
	wstring	Skill04Type;
};

// ==================
// ==   ITEMINFO   ==
// ==================

struct ITEM_INFO
{
	UINT NUMBER;
	wstring Name;
};