//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// main.cpp 2017.07.06
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �C���N���[�h�t�@�C��
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "Lib/core.h"

MAIN(MAIN_PARAM)
{
	//DirectX������
	DirectX::Init("���[�ނ����Ƃ�B", SCREEN_WIDTH, SCREEN_HEIGHT);

	//�Q�[�����[�v
	while (DirectX::Update());

	//DirectX�I��
	DirectX::UnInit();
}