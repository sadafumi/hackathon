//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// main.cpp 2017.07.06
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// インクルードファイル
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "Lib/core.h"

MAIN(MAIN_PARAM)
{
	//DirectX初期化
	DirectX::Init("げーむたいとる。", SCREEN_WIDTH, SCREEN_HEIGHT);

	//ゲームループ
	while (DirectX::Update());

	//DirectX終了
	DirectX::UnInit();
}