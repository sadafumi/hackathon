//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// object.cpp 2017.06.12
// Author: Flauzino Vinicius AT12A242-33 60052
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// インクルードファイル
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
#include "core.h" //コアヘッダー

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 静的変数
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
pObject    Object::Objects[OBJECT_MAX] = {};
bool       Object::AutoUpdate = true;
bool       Object::AutoDraw = true;
pPrimitive pr[OBJECT_MAX] = {};
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// 静的関数
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
void Object::InitAll(void)
{
	for (int n = 0; n < OBJECT_MAX; n++)
	{
		if (Object::Objects[n] != NULL)
			Object::Objects[n]->Init();
	}
}

void Object::UnInit(void)
{
	for (int n = 0; n < OBJECT_MAX; n++)
	{
		if (Object::Objects[n] != NULL)
		{
			delete Object::Objects[n];
			Object::Objects[n] = NULL;
		}
	}
}

void Object::UpdateAll(void)
{
	for (int n = 0; n < OBJECT_MAX; n++)
	{
		if (Object::Objects[n] != NULL)
		{
			Object::Objects[n]->UpdateThis();
		}
	}
	char c[256];
	sprintf(c, "%d, %d", Input::MousePos.X, Input::MousePos.Y);
	SetWindowText(DirectX::hWnd, c);
}

void Object::DrawAll(void)
{
	for (int z = 0; z < DEPTH_MAX; z++)
	{
		for (int n = 0; n < OBJECT_MAX; n++)
		{
			if (Object::Objects[n] != NULL)
			{
				if ((int)(Object::Objects[n]->GetPosition().z) == z)
					Object::Objects[n]->Draw();
			}
		}
	}
}

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// メンバー関数
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
Object::Object(void)
{
	for (int n = 0; n < OBJECT_MAX; n++)
	{
		if (Object::Objects[n] == NULL)
		{
			Object::Objects[n] = this;
			this->x = n;
			break;
		}
	}

	this->ObjectType = OBJ_TEXTURE;
	this->Num = TEXTURE_EMPTY;
	this->Pattern = 0;
	this->Position = Vector3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.5f);
	this->Scale = Vector2(1.0f, 1.0f);
	this->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Mirror = Bool2(false, false);
	this->CutPosition = Vector2(0, 0);
	this->CutSize = Vector2(0, 0);
	this->Scroll = Vector2(0, 0);
	this->Angle = 0;
	this->Inertia.Force = 0.96f;
	this->Inertia.v3 = Vector3(0, 0, 0);
	this->Inertia.Angle = 0;
	this->LockPosition = false;
	this->LockColor = false;
	this->Size = Vector2(1.0f, 1.0f);
	this->Timer = 0;
	this->Limit.Type = LIMIT_NONE;
	this->Limit.Position = Vector3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	this->Limit.Size = Vector2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
	this->HitBox.Type = HITBOX_NONE;
	this->HitBox.Scale = Vector2(0.6f, 0.6f);
	this->Gravity = 0.0f;
}

Object::~Object(void)
{
	if (pr[this->x] != NULL)
	{
		delete pr[this->x];
		pr[this->x] = NULL;
	}
}

void Object::Init(void)
{

}

void Object::Update(void)
{

}

void Object::UpdateThis(void)
{
	this->Update();

	//空なら終了
	if (this == nullptr) return;

	//カウンター更新
	if (this->Timer)
		this->Timer--;

	//サイズ更新
	switch (this->ObjectType)
	{
	case OBJ_TEXTURE:
		this->Size.x = (Texture::Textures[this->Num].Size.x / Texture::Textures[this->Num].Div.X * this->Scale.x);
		this->Size.y = (Texture::Textures[this->Num].Size.y / Texture::Textures[this->Num].Div.Y * this->Scale.y);
		break;
	case OBJ_PRIMITIVE:
		this->Size = this->Scale;
		break;
	}

	//重力
	this->UpdatePosition(Vector3(0.0f, this->Gravity, 0.0f));

	//慣性
	this->Position.x += this->Inertia.v3.x;
	this->Position.y += this->Inertia.v3.y;
	this->Position.z += this->Inertia.v3.z;
	this->Angle += this->Inertia.Angle * 0.03f;
	this->Inertia.v3.x *= this->Inertia.Force;
	this->Inertia.v3.y *= this->Inertia.Force;
	this->Inertia.v3.z *= this->Inertia.Force;
	this->Inertia.Angle *= this->Inertia.Force;

	//移動制限
	this->SetLimit();
}

void Object::Draw(void)
{
	if (this->Num > TEXTURE_EMPTY)
		if (Texture::Textures[this->Num].pTex != NULL)
		{
			//カット処理
			Texture::CutPosition = this->CutPosition;
			Texture::CutSize = this->CutSize;
			//スクロール処理
			Texture::Scroll = this->Scroll;
			//ミラー設定
			Texture::Mirror = this->Mirror;
			//角度設定
			Texture::Angle = this->Angle;
			//ロック設定
			Texture::LockPosition = this->LockPosition;
			Texture::LockColor = this->LockColor;

			//描画
			Texture::Textures[this->Num].Draw(
				this->Position, this->Scale,
				this->Color, this->Pattern
			);
		}
}

TEXTURE_NUM Object::GetTexture(void)
{
	return this->Num;
}

float Object::GetPattern(void)
{
	return this->Pattern;
}

VECTOR3 Object::GetPosition(void)
{
	return this->Position;
}

VECTOR2 Object::GetScale(void)
{
	return this->Scale;
}

D3DCOLOR Object::GetColor(void)
{
	return this->Color;
}

BOOL2 Object::GetMirror(void)
{
	return this->Mirror;
}

float Object::GetAngle(void)
{
	return this->Angle;
}

VECTOR2 Object::GetScroll(void)
{
	return this->Scroll;
}

void Object::SetTexture(TEXTURE_NUM Num)
{
	this->Num = Num;
}

void Object::SetPattern(float Pattern)
{
	this->Pattern = Pattern;
}

void Object::SetPosition(VECTOR3 Position)
{
	this->Position = Position;
}

void Object::SetScale(VECTOR2 Scale)
{
	this->Scale = Scale;
}

void Object::SetColor(D3DCOLOR Color)
{
	this->Color = Color;
}

void Object::SetMirror(BOOL2 Mirror)
{
	this->Mirror = Mirror;
}

void Object::SetAngle(float Angle)
{
	this->Angle = Angle;
}

void Object::SetLockPosition(bool LockPosition)
{
	this->LockPosition = LockPosition;
}

void Object::SetLockColor(bool LockColor)
{
	this->LockColor = LockColor;
}

void Object::SetAll(TEXTURE_NUM Num, float Pattern, VECTOR3 Position, VECTOR2 Scale, D3DCOLOR Color, BOOL2 Mirror)
{
	this->Num = Num;
	this->Pattern = Pattern;
	this->Position = Position;
	this->Scale = Scale;
	this->Color = Color;
	this->Mirror = Mirror;
}

void Object::SetScroll(VECTOR2 Scroll)
{
	this->Scroll = Scroll;
}

void Object::UpdatePattern(float Pattern)
{
	this->Pattern += Pattern;
}

void Object::UpdatePosition(VECTOR3 Position)
{
	this->Position.x += Position.x; this->Inertia.v3.x += Position.x * this->Inertia.Force;
	this->Position.y += Position.y; this->Inertia.v3.y += Position.y * this->Inertia.Force;
	this->Position.z += Position.z; this->Inertia.v3.z += Position.z * this->Inertia.Force;
}

void Object::UpdateScale(VECTOR2 Scale)
{
	this->Scale.x += Scale.x;
	this->Scale.y += Scale.y;
}

void Object::UpdateScroll(VECTOR2 Scroll)
{
	this->Scroll.x += Scroll.x;
	this->Scroll.y += Scroll.y;
}

void Object::UpdateAngle(float Angle)
{
	this->Angle += Angle; this->Inertia.Angle += Angle * Inertia.Force;
}

void Object::Move(VECTOR3 Position)
{
	this->UpdatePosition(Vector3(-sinf(RAD(this->Angle)) * Position.y, cosf(RAD(this->Angle)) * Position.y, 0.0f));
	this->UpdatePosition(Vector3(cosf(RAD(this->Angle)) * Position.x, sinf(RAD(this->Angle)) * Position.x, 0.0f));
}

bool Object::CheckCollision(Object * Obj)
{
	if (this == nullptr)
		return false;
	switch (this->HitBox.Type)
	{
	case HITBOX_RECT:
	{
		if (fabs(this->Position.x - Obj->Position.x) < this->Size.x / 2.0f * this->HitBox.Scale.x + Obj->Size.x / 2.0f * Obj->HitBox.Scale.x
			&&
			fabs(this->Position.y - Obj->Position.y) < this->Size.y / 2.0f * this->HitBox.Scale.y + Obj->Size.y / 2.0f * Obj->HitBox.Scale.y)
		{
			return true;
		}
	}
	break;
	case HITBOX_CIRCLE:
	{
		float r1 = SQRT(this->Size.x / 2.0f * this->HitBox.Scale.x, this->Size.y / 2.0f * this->HitBox.Scale.y);
		float r2 = SQRT(Obj->Size.x / 2.0f * Obj->HitBox.Scale.x, Obj->Size.y / 2.0f * Obj->HitBox.Scale.y);
		float dif = SQRT(fabs(this->Position.x - Obj->Position.x), fabs(this->Position.y - Obj->Position.y));
		if (dif < r1 + r2)
			return true;
	}
	break;
	}

	return false;
}

void Object::SetTimer(int n)
{
	this->Timer = n;
}

int Object::GetTimer(void)
{
	return this->Timer;
}

void Object::SetLimit(void)
{
	if (this == nullptr)
		return;

	switch (this->Limit.Type)
	{
	case LIMIT_RECT:
		if (this->Position.x <= this->Limit.Position.x - this->Limit.Size.x)
			this->Position.x = this->Limit.Position.x - this->Limit.Size.x;
		if (this->Position.x >= this->Limit.Position.x + this->Limit.Size.x)
			this->Position.x = this->Limit.Position.x + this->Limit.Size.x;
		if (this->Position.y <= this->Limit.Position.y - this->Limit.Size.y)
			this->Position.y = this->Limit.Position.y - this->Limit.Size.y;
		if (this->Position.y >= this->Limit.Position.y + this->Limit.Size.y)
			this->Position.y = this->Limit.Position.y + this->Limit.Size.y;
		break;
	case LIMIT_CIRCLE:
		float rad = atan2f(this->Position.y - this->Limit.Position.y, this->Position.x - this->Limit.Position.x);
		VECTOR2 vDistance = { this->Position.x - this->Limit.Position.x, this->Position.y - this->Limit.Position.y };
		float fDistance = SQRT(fabs(vDistance.x), fabs(vDistance.y));
		float fLimit = SQRT(cosf(rad) * this->Limit.Size.x, sinf(rad) * this->Limit.Size.y);
		float fDif = fDistance - fLimit;
		if (fDif > 0)
		{
			this->Position.x -= cosf(rad) * fDif;
			this->Position.y -= sinf(rad) * fDif;
		}
		break;
	}
}