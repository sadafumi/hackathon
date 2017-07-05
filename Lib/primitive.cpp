//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// primitive.cpp 2017.06.12
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// インクルードファイル
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "core.h" //コアヘッダー

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 静的変数
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 静的関数
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// メンバー関数
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
Primitive::Primitive(void)
{
	this->ObjectType = OBJ_PRIMITIVE;
	this->Size = Vector2(1.0f, 1.0f);
	this->PrimitiveType = PRIMITIVE_OPEN;
	this->VertexNum = 12;
	this->Scale = Vector2(100.0f, 100.0f);
	this->HitBox.Type = HITBOX_NONE;
}

Primitive::Primitive(PRIMITIVE_TYPE PrimitiveType, int VertexNum)
{
	this->ObjectType = OBJ_PRIMITIVE;
	this->Size = Vector2(1.0f, 1.0f);
	this->PrimitiveType = PrimitiveType;
	this->VertexNum = VertexNum;
	this->Scale = Vector2(100.0f, 100.0f);
}

void Primitive::CreateVertex(void)
{
	//カラーブレンディング
	D3DXCOLOR newColor;
	D3DXCOLOR OldColor = this->Color;
	D3DXCOLOR CameraColor = Camera::Color;
	D3DXColorModulate(&newColor, &OldColor, &CameraColor);
	this->Color = newColor;

	//VERTEX設定
	this->vtx = new VERTEX[100];
	static float centerX = 0; static float centerY = 0;
	if (this->PrimitiveType == PRIMITIVE_FILL)
	{
		if(this->LockPosition)
		{
			centerX = this->Position.x;
			centerY = this->Position.y;
		}
		else
		{
			centerX = this->Position.x - Camera::Position.x;
			centerY = this->Position.y - Camera::Position.y;
		}

		vtx->x = centerX;
		vtx->y = centerY;
		vtx->rhw = 1.0f;
		vtx->z = 1.0f;
		vtx->rgba = this->Color;
	}

	for (int n = (this->PrimitiveType == PRIMITIVE_FILL) ? 1 : 0; n <= this->VertexNum; n++, vtx++)
	{
		if (this->LockPosition)
		{
			centerX = this->Position.x;
			centerY = this->Position.y;
		}
		else
		{
			centerX = this->Position.x - Camera::Position.x;
			centerY = this->Position.y - Camera::Position.y;
		}

		static float x = 0; static float y = 0;
		x = cosf(RAD(360 / this->VertexNum * n)) * this->Size.x * Camera::Zoom.x;
		y = sinf(RAD(360 / this->VertexNum * n)) * this->Size.y * Camera::Zoom.y;

		static float range = 0;
		range = sqrtf(x*x + y*y);

		static float oldAngle = 0; static float newAngle = 0;
		oldAngle = atan2f(y, x);
		newAngle = oldAngle + RAD(this->Angle + Camera::Angle);

		range = sqrtf(x*x + y*y);

		vtx->x = centerX + cosf(newAngle) * range;
		vtx->y = centerY + sinf(newAngle) * range;
		vtx->rhw = 1.0f;
		vtx->z = 1.0f;
		vtx->rgba = this->Color;
	}
	this->vtx -= VertexNum + 1;
}

void Primitive::Draw(void)
{
	this->CreateVertex();
	DirectX::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DirectX::pDevice->SetTexture(0, NULL);
	if(this->PrimitiveType == PRIMITIVE_FILL)
		DirectX::pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, this->VertexNum, vtx, sizeof(VERTEX));
	if(this->PrimitiveType == PRIMITIVE_OPEN)
		DirectX::pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, this->VertexNum, vtx, sizeof(VERTEX));
	DirectX::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	SAFE_DELETE(this->vtx);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// End.
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+