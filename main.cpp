//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// main.cpp 2017.06.18
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �C���N���[�h�t�@�C��
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "main.h"

MAIN(MAIN_PARAM)
{
	//������
	Init();

	//�Q�[�����[�v
	while (Update());

	//�I��
	UnInit();
}

void Init(void)
{
	//DirectX������
	DirectX::Init("���[�ނ����Ƃ�B", SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool Update(void)
{
	//DirectX�X�V
	return DirectX::Update();
}

void UnInit(void)
{	
	//DirectX�I��
	DirectX::UnInit();
}