#pragma once

// ==================
// ==     공용     ==
// ==================

#define SINGLE(type) public:\
						static type* CreateMgr()\
						{\
							static type newMgr;\
							return &newMgr;\
						}\
					private:\
						type();\
						~type();

#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;
#define CLONE(type) virtual type* Clone() override { return new type(*this); }

enum class PEN_COLOR
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class BRUSH_COLOR
{
	HOLLOW, // 투명 브러쉬
	BLACK,  // 검은 브러쉬
	GRAY,	// 회색 브러쉬
	MAGENTA, // 마젠타 브러쉬
	END,
};

// ==================
// ==    TimeMgr   ==
// ==================

#define DT CTimeMgr::CreateMgr()->GetDeltaTime()

// ==================
// ==    KeyMgr    ==
// ==================

enum class KEY_TYPE
{
	W,
	A,
	S,
	D,

	O,
	T,

	UP,
	LEFT,
	DOWN,
	RIGHT,

	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,

	LBTN,

	SPACE,
	ESC,
	ENTER,

	END,
};

enum class KEY_STATE
{
	TAP,
	PRESS,
	RELEASE,
	NONE,
};

#define IS_TAP(key_type) CKeyMgr::CreateMgr()->GetKeyState(KEY_TYPE::key_type) == KEY_STATE::TAP
#define IS_PRESS(key_type) CKeyMgr::CreateMgr()->GetKeyState(KEY_TYPE::key_type) == KEY_STATE::PRESS
#define IS_RELEASE(key_type) CKeyMgr::CreateMgr()->GetKeyState(KEY_TYPE::key_type) == KEY_STATE::RELEASE
#define IS_NONE(key_type) CKeyMgr::CreateMgr()->GetKeyState(KEY_TYPE::key_type) == KEY_STATE::NONE

// ==================
// ==   SceneMgr   ==
// ==================

enum class SCENE_TYPE
{
	LOGO_SCENE,
	INTRO_SCENE,
	PALLET_CITY,
	ROAD_01,
	VIRIDIAN_CITY,
	PEWTER_CITY,
	TOOL_SCENE,

	REDHOUSESCENE1F,
	REDHOUSESCENE2F,
	GREENHOUSE,
	OAKLAB,
	HOUSE1,
	HOUSE2,
	CENTER1F,
	CENTER2F,
	MART,
	HOUSEBLACKROOF,
	HOUSEBLACKROOF1,
	MUSEUM1F,
	MUSEUM2F,
	PEWTERGYM,

	PLAYER_POKEMON_INFO_SCENE,
	BACKPACK_SCENE,

	BATTLESCENE,

	END,
};


// ==================
// ==    Object    ==
// ==================

#define MAX_LAYER 16

enum class LAYER_TYPE
{
	DEFAULT,
	BACKGROUND,
	ENVIRONMENT,		// 환경체
	PLAYER,				// 3인칭 플레이어
	PLAYERPOKEMON,
	NPC,				// NPC 들
	PLAYER_PROJECTILE,	// 플레이어 몬스터 투사체
	MONSTER,			// 몬스터
	MONSTER_PROJECTILE,	// 상대 몬스터 투사체
	BALL,				// 몬스터 볼 : 포켓몬 포획할 때 해당 레이어 사용


	UI = MAX_LAYER - 1,	// UI
	END = MAX_LAYER,
};

enum class OBJECT_TYPE
{
	HOUSEREDROOF,
	OAKS_LAB,
	HOUSE1,
	HOUSE2,
	GYM,
	CENTER,
	MART,

	PALLET,
	ROAD1,
	VIRIDIAN,
	PEWTER,

	REDHOUSE_1F,
	REDHOUSE_2F,
	GREENHOUSE,
	HOUSE1_IN,
	HOUSE2_IN,
	OAKS_LAB_IN,
	CENTER_1F,
	CENTER_2F,
	MART_IN,

	FLOWER,
	ATREE,
	AATREE,
	GRASS,
	WAVE0,
	WAVE1,
	WAVE2,
	WAVE3,
	WAVE4,
	WAVE5,
	WAVE6,
	WAVE7,
	MAILBOX,
	WHITE_FENCE,
	WHITE_SIGN,
	WOOD_SIGN,
	WHITEFENCE1,
	WHITEFENCELEFTBOT,
	WHITEFENCELEFTTOP,
	WHITEFENCERIGHTBOT,
	WHITEFENCERIGHTTOP,
	WOODFENCE,
	WOODFENCE1,
	WOODFENCELEFTBOT,
	WOODFENCELEFTTOP,
	WOODFENCERIGHTBOT,
	WOODFENCERIGHTTOP,
	SMALLTREE,
	PALLETWATER,
	ROCKTILE,
	ROCKTILECONER,
	MUSEUM,
	HOUSEBLACKROOF,
	PEWTER_GYM,
	GYMSIGN,
	BED,
	FLOWERPOT,
	OAKBOOK,
	OAKBOOKSHELF,
	OAKBOOKSHELFHALF,
	OAKMACHINE,
	TABLE,
	OAKTABLE,
	OAKMONSTERBALL,
	OAKBOOKSHELFHALF1,
	CENTERSOFA,
	CENTERTABLE,
	MARTSTAND,
	MARTSTAND1,
	MARTTABLE,
	MUSEUMSTAND,
	MUSEUMSTAND1,
	MUSEUMSTAND2,
	MUSEUMBOX,
	PLAYER,
	GREENREDHOUSE,
	ESCALATOR1F,
	ESCALATOR2F,
	WOODFENCE2,

	OAK,

	END,
};

// ==================
// ==  COMPONENT   ==
// ==================

enum class COMPONENT_TYPE
{
	AI,			// 배틀시 AI 사용할 예정이다.
	ANIMATOR,	// 애니메이션
	RIGIDBODY,	// 몬스터 볼 공 날라 갈 때 궤적 계산시 사용 예정
	COLLIDER,	// 충돌체
	END,
};

// ==================
// ==  CCameraMgr  ==
// ==================

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

// ==================
// ==   CEventMgr  ==
// ==================

enum class EVENT_TYPE
{
	CREATE_OBJECT, // first : Object Adress, second : Layer Type
	DELETE_OBJECT, // first : Object Adress, 
	SCENE_CHANGE,  // first : Scene Type
	RE_RENDER,	   // first : Object Adress
	DELETE_RE_RENDER,
	SETUIFOCUS,

	END,
};


// ==================
// ==   CCollider  ==
// ==================

#define MaxCollider 8

enum class COLLIDER_TYPE
{
	NONE,		// 콜라이더가 없다는 뜻이다.
	DEFAULT,
	EVENT,
	RE_RENDER,
};

// ==================
// ==    MnueUI    ==
// ==================

enum class MENU_TYPE
{
	POKEMON,
	BAG,
	CLOSE,
};

enum class PLAYER_ACTION_TYPE
{
	FIGHT,
	BAG,
	POKEMON,
	RUN,
};

enum class BATTLEBOX_TYPE
{
	SKILL01,
	SKILL02,
	SKILL03,
	SKILL04,
};

// ==================
// ==    Player    ==
// ==================

struct PlayerInfo
{
	UINT Money;

};

// ==================
// ==   PokeMon    ==
// ==================

enum class OWNER_TYPE
{
	PLAYER,
	TRAINER,
	WILD,
};

enum class POKEMON_IO_TYPE
{
	e_IN,
	e_NONE,
	e_OUT,
};

// ==================
// ==  PokeMonType ==
// ==================

enum class POKEMON_TYPE
{
	NORMAL,
	FIRE,
	WATER,
	ELECTR,
	GRASS,
	ICE,
	FIGHT,
	POISON,
	GROUND,
	FLVING,
	PSYCHC,
	BUG,
	ROCK,
	GHOST,
	DREGON,
	DARK,
	STEEL,

	END,

	NONE,
};

enum class EFFECT_TYPE
{
	GREAT,
	NORMAL,
	WEEK,
	NON,
};

enum class POKEMONSCENE_TYPE
{
	NONE,
	BATTLE,
	UI,
};

// ==================
// ==  BattleScene ==
// ==================

enum class BATTLE_TYPE
{
	NONE,
	PLAYERACTION,
	PLAYERUSESKILL,
	PALYERCALDMG,
	OTHERTURN,
	OTHERCALDMG,
	RUN,
	POKEMONSHIFT,
	POKEMONSHIFT2,
	PLAYERDEADCHECK,
	OTHERDEADCHECK,
	GETEXP,
	BATTLEEND,
};

// =====================
// == PokemonSelectUI ==
// =====================

enum class POKETMONSELECT_TYPE
{
	POKEMON1,
	POKEMON2,
	POKEMON3,
	POKEMON4,
	POKEMON5,
	POKEMON6,

	CANCLE,
};

// ==============
// ==   ITem   ==
// ==============

enum class ITEM_TYPE
{
	POTION,
	CANDY,
	REVIVE,
};