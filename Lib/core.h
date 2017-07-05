//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// core.h 2017.06.18
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#ifndef _CORE_H_ //�d���C���N���[�h�h�~
#define _CORE_H_
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �C���N���[�h�t�@�C��
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include <windows.h> //Windows���C�u����
#include <d3dx9.h>   //DirectX
#include <tchar.h>   //tChar
#include <stdio.h>   //���o�̓��C�u����
#include <time.h>    //���ԃ��C�u����
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// ���C�u�����t�@�C��
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#pragma comment(lib, "d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �x��
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#pragma warning(disable: 4996)

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �}�N����`
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//�X�N���[���T�C�Y
#define SCREEN_WIDTH  (1280)
#define SCREEN_HEIGHT ( 720)
// "���S��"COM�|�C���^�̉�������}�N��
#define SAFE_RELEASE(p) if(p){ p->Release(); p = NULL; }
// "���S��"�z��̉�������}�N��
#define SAFE_DELETE(p) if(p){ delete[] p; p = NULL; }
// WinMain�̃p�����[�^
#define MAIN_PARAM HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szStr, int nCmdShow
#define MAIN int WINAPI WinMain
//�~����
#define PI 3.141592f
//���Z�֘A
#define ANG(a) (a / PI * 180.0f)
#define RAD(a) (a * PI / 180.0f)
#define SQRT(a,b) sqrtf((float)(a*a+b*b))

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �\���̐錾
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct VERTEX
{
	float    x, y, z;
	float    rhw;
	D3DCOLOR rgba;
	float    u, v;
} *PVERTEX;

typedef struct VECTOR2
{
	float x, y;
} *PVECTOR2;

typedef struct VECTOR3
{
	float x, y, z;
} *PVECTOR3;

typedef struct BOOL2
{
	bool x, y;
} *PBOOL2;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �N���X�錾
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "input.h"
#include "camera.h"
#include "texture.h"
#include "object.h"
#include "primitive.h"
#include "../Player.h"

typedef class DirectX
{
public:
	static int                     Scene;
	static LPDIRECT3D9             pD3d;
	static LPDIRECT3DDEVICE9       pDevice;
	static LPDIRECT3DVERTEXBUFFER9 pBuffer;
	static LPD3DXMATRIX            pProj;
	static D3DPRESENT_PARAMETERS   d3dpp;
	static HWND                    hWnd;
	static HINSTANCE               hInstance;
	static WNDCLASSEX              wndClass;
	static LPSTR                   Caption;
	static COORD                   Size;
	static MSG                     msg;
	static int                     FrameCnt;
	static D3DCOLOR                bgColor;

	static void Init(LPSTR Caption, COORD Size);
	static bool Update(void);
	static void UnInit(void);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void WmCreate(HWND hWnd);
	static void WmCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
	static void WmPaint(HWND hWnd);
	static void WmMove(HWND hWnd, LPARAM lParam);
	static void WmMouseMove(HWND hWnd, LPARAM lParam);
	static void WmSize(HWND hWnd, LPARAM lParam);
	static void WmLButtonDown(HWND hWnd);
	static void WmRButtonDown(HWND hWnd);
	static void WmLButtonUp(HWND hWnd);
	static void WmRButtonUp(HWND hWnd);
	static void WmKeyDown(HWND hWnd, WPARAM wParam);
	static void WmKeyUp(HWND hWnd, WPARAM wParam);

} *pDirectX;

COORD Coord(SHORT x, SHORT y);
VECTOR2 Vector2(float x, float y);
VECTOR3 Vector3(float x, float y, float z);
BOOL2 Bool2(bool x, bool y);

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#endif //ifndef _CORE_H_
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+