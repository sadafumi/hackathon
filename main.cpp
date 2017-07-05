//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// main.cpp 2017.06.18
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// インクルードファイル
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "main.h"

INT WINAPI WinMain(MAIN_PARAM)
{
	//初期化
	Init();

	//ゲームループ
	while (Update());

	//終了
	UnInit();
}

void Init(void)
{
	//ランダムシード初期化
	(unsigned)time(NULL);
	//DirectX初期化
	DirectX::Init("げーむたいとる。", Coord(SCREEN_WIDTH, SCREEN_HEIGHT));
	//テクスチャ読込
	Texture::Init();
}

bool Update(void)
{
	//DirectX更新
	return DirectX::Update();
}

void UnInit(void)
{	
	//DirectX終了
	DirectX::UnInit();
}