//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// input.cpp 2017.06.12
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �C���N���[�h�t�@�C��
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "core.h" //�R�A�w�b�_�[

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �ÓI�ϐ�
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool Input::bKeys[KEY_MAX] = {};
UINT Input::uKeys[KEY_MAX] = {};
bool Input::bLClick = false;
bool Input::bRClick = false;
UINT  Input::uLClick = 0;
UINT  Input::uRClick = 0;
COORD Input::MousePos = {};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �ÓI�֐�
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void Input::Update(void)
{
	for (UINT u = 0; u < KEY_MAX; u++)
	{
		if (Input::bKeys[u])
		{
			Input::uKeys[u]++;
		}
		else
		{
			Input::uKeys[u] = 0;
		}
	}
	if (Input::bLClick)
	{
		Input::uLClick++;
	}
	else
	{
		Input::uLClick = 0;
	}
	if (Input::bRClick)
	{
		Input::uRClick++;
	}
	else
	{
		Input::uRClick = 0;
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// End.
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+