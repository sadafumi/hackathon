//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// texture.cpp 2017.06.12
// Author: Flauzino Vinicius AT12A242-33 60052
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// インクルードファイル
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
#include "core.h" //コアヘッダー

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 静的変数
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
pTexture Texture::Textures = new Texture[TEXTURE_MAX];
BOOL2    Texture::Mirror = {};
float    Texture::Angle = 0;
VECTOR2	 Texture::CutPosition = Vector2(0, 0);
VECTOR2	 Texture::CutSize = Vector2(0, 0);
VECTOR2  Texture::Scroll = Vector2(0, 0);
bool     Texture::LockPosition = false;
bool     Texture::LockColor = false;

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 静的関数
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
Texture::Texture(void)
{
	this->pTex = NULL;
}

Texture::~Texture(void)
{
	SAFE_RELEASE(this->pTex);
}

void Texture::Init(void)
{
	//テクスチャ読込
	Texture::Load(TEXTURE_BG, TEX_DIR"bg.png");
	Texture::Load(TEXTURE_BULLET, TEX_DIR"bullet.png");
	Texture::Load(TEXTURE_ENEMY, TEX_DIR"enemy.png");
	Texture::Load(TEXTURE_PLAYER, TEX_DIR"player2.png");
}

void Texture::UnInit(void)
{
	SAFE_DELETE(Texture::Textures);
}

void Texture::Load(TEXTURE_NUM Num, LPSTR FileName)
{
	D3DXIMAGE_INFO dii;
	D3DXGetImageInfoFromFile(FileName, &dii);
	D3DXCreateTextureFromFile(DirectX::pDevice, FileName, &Texture::Textures[Num].pTex);
	Texture::Textures[Num].Size.x = (SHORT)dii.Width;
	Texture::Textures[Num].Size.y = (SHORT)dii.Height;
	Texture::Textures[Num].Div.X = 1;
	Texture::Textures[Num].Div.Y = 1;
}

void Texture::Load(TEXTURE_NUM Num, LPSTR FileName, COORD Div)
{
	D3DXIMAGE_INFO dii;
	D3DXGetImageInfoFromFile(FileName, &dii);
	D3DXCreateTextureFromFile(DirectX::pDevice, FileName, &Texture::Textures[Num].pTex);
	Texture::Textures[Num].Size.x = (float)dii.Width;
	Texture::Textures[Num].Size.y = (float)dii.Height;
	Texture::Textures[Num].Div.X = Div.X;
	Texture::Textures[Num].Div.Y = Div.Y;
}

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// メンバー関数
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
void Texture::Draw(VECTOR3 Pos, VECTOR2 Scale, D3DCOLOR Color, float Pattern)
{
	Pos.z = 1.0f;
	if (!Texture::LockPosition)
	{
		Pos.x -= Camera::Position.x;
		Pos.y -= Camera::Position.y;
		Pos.z -= Camera::Position.z;
	}

	Scale.x *= Camera::Zoom.x;
	Scale.y *= Camera::Zoom.y;
	Texture::Angle += Camera::Angle;

	if (!Texture::LockColor)
	{
		D3DXCOLOR newColor;
		D3DXCOLOR OldColor = Color;
		D3DXCOLOR CameraColor = Camera::Color;
		D3DXColorModulate(&newColor, &OldColor, &CameraColor);
		Color = newColor;
	}

	VECTOR2 Size = {};
	COORD Div = {};
	UINT _Pattern = (UINT)Pattern;
	float a = 0;
	float b = 0;
	float c = 0;
	float d = 0;

	if (this->pTex != NULL)
	{
		DirectX::pDevice->SetTexture(0, this->pTex);
	}

	Div = this->Div;
	_Pattern = (UINT)Pattern % (Div.X * Div.Y);
	Size = this->Size;
	Size.x = (float)(Size.x * Scale.x);
	Size.y = (float)(Size.y * Scale.y);

	if (Texture::Mirror.x)
		b = 1.0f / Div.X * (_Pattern % Div.X), a = 1.0f / Div.X * (_Pattern % Div.X) + 1.0f / Div.X;
	else
		a = 1.0f / Div.X * (_Pattern % Div.X), b = 1.0f / Div.X * (_Pattern % Div.X) + 1.0f / Div.X;
	if (Texture::Mirror.y)
		d = 1.0f / Div.Y * (_Pattern / Div.X), c = 1.0f / Div.Y * (_Pattern / Div.X) + 1.0f / Div.Y;
	else
		c = 1.0f / Div.Y * (_Pattern / Div.X), d = 1.0f / Div.Y * (_Pattern / Div.X) + 1.0f / Div.Y;

	if (Texture::CutSize.x != 0 && Texture::CutSize.y != 0)
	{
		float w = b - a;
		float h = d - c;

		a += w * CutPosition.x;
		Pos.x += Size.x * w * CutPosition.x;
		b = a + w * CutSize.x;
		Size.x = (float)(CutSize.x * Size.x);
		c += h * CutPosition.y;
		Pos.y += Size.y * h * CutPosition.y;
		d = c + h * CutSize.y;
		Size.y = (float)(CutSize.y * Size.y);
	}
	a += Texture::Scroll.x;
	b += Texture::Scroll.x;
	c += Texture::Scroll.y;
	d += Texture::Scroll.y;
	
	Size.x = SHORT(Size.x / Div.X / 2.0f); Size.y = SHORT(Size.y / Div.Y / 2.0f);

	VERTEX * vtx = new VERTEX[6];
	vtx->u = a;   vtx->v = c; vtx->z = Pos.z; vtx->rhw = 1.0f; vtx->rgba = Color;
	vtx->x = Pos.x + cosf(atan2f((float)-Size.y, (float)-Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y); 
	vtx->y = Pos.y + sinf(atan2f((float)-Size.y, (float)-Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y);
	vtx++;
	vtx->u = b; vtx->v = c; vtx->z = Pos.z; vtx->rhw = 1.0f; vtx->rgba = Color;
	vtx->x = Pos.x + cosf(atan2f((float)-Size.y, (float)Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y); 
	vtx->y = Pos.y + sinf(atan2f((float)-Size.y, (float)Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y);
	vtx++;
	vtx->u = a; vtx->v = d; vtx->z = Pos.z; vtx->rhw = 1.0f; vtx->rgba = Color;
	vtx->x = Pos.x + cosf(atan2f((float)Size.y, (float)-Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y); 
	vtx->y = Pos.y + sinf(atan2f((float)Size.y, (float)-Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y);
	vtx++;
	vtx->u = b; vtx->v = d; vtx->z = Pos.z; vtx->rhw = 1.0f; vtx->rgba = Color;
	vtx->x = Pos.x + cosf(atan2f((float)Size.y, (float)Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y); 
	vtx->y = Pos.y + sinf(atan2f((float)Size.y, (float)Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y);
	vtx++;
	vtx->u = a; vtx->v = d; vtx->z = Pos.z; vtx->rhw = 1.0f; vtx->rgba = Color;
	vtx->x = Pos.x + cosf(atan2f((float)Size.y, (float)-Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y); 
	vtx->y = Pos.y + sinf(atan2f((float)Size.y, (float)-Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y);
	vtx++;
	vtx->u = b; vtx->v = c; vtx->z = Pos.z; vtx->rhw = 1.0f; vtx->rgba = Color;
	vtx->x = Pos.x + cosf(atan2f((float)-Size.y, (float)Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y); 
	vtx->y = Pos.y + sinf(atan2f((float)-Size.y, (float)Size.x) + RAD(Texture::Angle)) * SQRT(Size.x, Size.y);
	vtx -= 5;

	DirectX::pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vtx, sizeof(VERTEX));
	SAFE_DELETE(vtx);
}