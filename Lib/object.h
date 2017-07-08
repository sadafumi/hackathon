//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// object.h 2017.06.12
// Author: Flauzino Vinicius AT12A242-33 60052
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 重複インクルード防止
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
#ifndef _OBJECT_H_
#define _OBJECT_H_

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// マクロ定義
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
#define OBJECT_MAX (10000)
#define DEPTH_MAX  (  100)

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 列挙型
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
enum HITBOX_TYPE
{
	HITBOX_NONE,
	HITBOX_RECT,
	HITBOX_CIRCLE,
	HITBOX_MAX
};

enum OBJECT_TYPE
{
	OBJ_TEXTURE,
	OBJ_PRIMITIVE,
	OBJ_MAX
};

enum LIMIT_TYPE
{
	LIMIT_NONE,
	LIMIT_RECT,
	LIMIT_CIRCLE,
	LIMIT_MAX
};

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 構造体宣言
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
typedef struct HITBOX
{
	HITBOX_TYPE Type;
	VECTOR2     Scale;
} *PHITBOX;

typedef struct LIMIT
{
	VECTOR3       Position;
	VECTOR2       Size;
	LIMIT_TYPE    Type;
} *PLIMIT;

typedef struct INERTIA
{
	float         Force;
	float         Angle;
	VECTOR3       v3;
} *PINERTIA;

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// クラス
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
typedef class Object
{
public:
	static Object * Objects[OBJECT_MAX];
	static bool AutoUpdate;
	static bool AutoDraw;
	static void InitAll(void);
	static void DrawAll(void);
	static void UnInit(void);
	static void UpdateAll(void);

	int x;

	Object(void);
	~Object(void);

	virtual void Draw(void);

	TEXTURE_NUM  GetTexture(void);
	float        GetPattern(void);
	VECTOR3      GetPosition(void);
	VECTOR2      GetScale(void);
	D3DCOLOR     GetColor(void);
	BOOL2        GetMirror(void);
	float        GetAngle(void);
	VECTOR2      GetScroll(void);
	int          GetTimer(void);

	virtual void Init(void);
	void         UpdateThis(void);
	virtual void Update(void);

	void SetTexture(TEXTURE_NUM Num);
	void SetPattern(float Pattern);
	void SetPosition(VECTOR3 Position);
	void SetScale(VECTOR2 Scale);
	void SetColor(D3DCOLOR Color);
	void SetMirror(BOOL2 Mirror);
	void SetAngle(float Angle);
	void SetScroll(VECTOR2 Scroll);
	void SetLockPosition(bool LockPosition);
	void SetAll(TEXTURE_NUM Num, float Pattern, VECTOR3 Position, VECTOR2 Scale, D3DCOLOR Color, BOOL2 Mirror);
	void UpdatePattern(float Pattern);
	void UpdatePosition(VECTOR3 Position);
	void UpdateScale(VECTOR2 Scale);
	void UpdateScroll(VECTOR2 Scroll);
	void UpdateAngle(float Angle);
	void Move(VECTOR3 Move);
	bool CheckCollision(Object * Obj);
	void SetLimit(void);
	void SetTimer(int Frames);

protected:
	OBJECT_TYPE    ObjectType;
	TEXTURE_NUM    Num;
	D3DCOLOR       Color;
				   
	VECTOR3        Position;
	VECTOR2        Scale;
	VECTOR2        Size;
	BOOL2          Mirror;
	float          Pattern;
	float          Angle;
				   
	HITBOX         HitBox;
	LIMIT          Limit;
	INERTIA        Inertia;
				   
	VECTOR2        CutPosition, CutSize;
	VECTOR2        Scroll;
	bool           LockPosition;
				   		  
	int            Timer;
	float          Gravity;
} *pObject;

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// End.
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
#endif //#ifndef _OBJECT_H_