//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// texture.h 2017.06.12
// Author: Flauzino Vinicius AT12A242-33 60052
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 重複インクルード防止
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// マクロ定義
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
#define POLYGON_NUM (2)
#define TEX_DIR "resource/texture/"

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 列挙型宣言定義
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
enum TEXTURE_NUM
{
	TEXTURE_EMPTY = -1,
	TEXTURE_BG,
	TEXTURE_BULLET,
	TEXTURE_ENEMY,
	TEXTURE_PLAYER,
	TEXTURE_MAX
};

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// クラス
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
typedef class Texture
{
public:
	static Texture * Textures;

	static BOOL2   Mirror;
	static float   Angle;
	static VECTOR2 CutPosition;
	static VECTOR2 CutSize;
	static VECTOR2 Scroll;
	static bool    LockPosition;

	LPDIRECT3DTEXTURE9 pTex;
	VECTOR2            Size;
	COORD              Div;
	LPSTR              FileName;

	Texture(void);
	~Texture(void);

	void Draw(VECTOR3 Position, VECTOR2 Scale, D3DCOLOR Color, float Pattern);
	static void Init(void);
	static void UnInit(void);
	static void Load(TEXTURE_NUM Num, LPSTR FileName);
	static void Load(TEXTURE_NUM Num, LPSTR FileName, COORD Div);
} *pTexture;

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// End.
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
#endif //#ifndef _TEXTURE_H_