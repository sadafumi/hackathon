//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// main.cpp 2017.06.18
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �C���N���[�h�t�@�C��
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "main.h"

INT WINAPI WinMain(MAIN_PARAM)
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
	//�����_���V�[�h������
	(unsigned)time(NULL);
	//DirectX������
	DirectX::Init("���[�ނ����Ƃ�B", Coord(SCREEN_WIDTH, SCREEN_HEIGHT));
	//�e�N�X�`���Ǎ�
	Texture::Init();
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