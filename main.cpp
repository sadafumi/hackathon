//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// main.cpp 2017.06.18
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// インクルードファイル
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "main.h"

MAIN(MAIN_PARAM)
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
	//DirectX初期化
	DirectX::Init("げーむたいとる。", SCREEN_WIDTH, SCREEN_HEIGHT);
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