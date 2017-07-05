//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// directx.cpp 2017.06.12
// Author: Flauzino Vinicius AT12A242-33 60052
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// インクルードファイル
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "core.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 静的変数
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
int                     DirectX::Scene;
LPDIRECT3D9             DirectX::pD3d;
LPDIRECT3DDEVICE9       DirectX::pDevice;
LPDIRECT3DVERTEXBUFFER9 DirectX::pBuffer;
LPD3DXMATRIX            DirectX::pProj;
D3DPRESENT_PARAMETERS   DirectX::d3dpp;
HWND                    DirectX::hWnd;
HINSTANCE               DirectX::hInstance;
WNDCLASSEX              DirectX::wndClass;
LPSTR                   DirectX::Caption;
COORD                   DirectX::Size;
MSG                     DirectX::msg;
int                     DirectX::FrameCnt;
D3DCOLOR                DirectX::bgColor;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// メンバー関数
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 関数名: 初期化
// 引数：なし
// 戻り値：なし
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::Init(LPSTR Caption, COORD Size)
{
	//Window
	ZeroMemory(&DirectX::msg, sizeof(DirectX::msg));
	DirectX::Caption = Caption;
	DirectX::wndClass.cbSize = sizeof(WNDCLASSEX);
	DirectX::wndClass.style = CS_HREDRAW | CS_VREDRAW;
	DirectX::wndClass.lpfnWndProc = WndProc;
	DirectX::wndClass.cbClsExtra = NULL;
	DirectX::wndClass.cbWndExtra = NULL;
	DirectX::wndClass.hInstance = DirectX::hInstance;
	DirectX::wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	DirectX::wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	DirectX::wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	DirectX::wndClass.lpszMenuName = NULL;
	DirectX::wndClass.lpszClassName = "WndClass";
	DirectX::wndClass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);

	RegisterClassEx(&DirectX::wndClass);

	RECT WindowRect = {
		0, 0, (LONG)Size.X, (LONG)Size.Y
	};
	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, false);
	DirectX::Size.X = (SHORT)(WindowRect.right - WindowRect.left);
	DirectX::Size.Y = (SHORT)(WindowRect.bottom - WindowRect.top);
	RECT DeskRect;
	GetWindowRect(GetDesktopWindow(), &DeskRect);
	int newPosX = (DeskRect.right - DirectX::Size.X) / 2;
	int newPosY = (DeskRect.bottom - DirectX::Size.Y) / 2;
	DirectX::hWnd = CreateWindowEx(0, "WndClass", DirectX::Caption, WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME),
		newPosX, newPosY, Size.X, Size.Y, NULL, NULL, DirectX::hInstance, NULL);

	UpdateWindow(DirectX::hWnd);

	//DirectX
	//「Direct3D」オブジェクトの作成
	if (NULL == (DirectX::pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
		return;
	}

	//「DIRECT3Dデバイス」オブジェクトの作成
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	//d3dpp.EnableAutoDepthStencil = TRUE;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(DirectX::pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DirectX::hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &DirectX::pDevice)))
	{
		MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
		return;
	}

	// 2D描画用射影変換行列
	//DirectX::pDevice->SetRenderState(D3DRS_ZENABLE, true);
	DirectX::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DirectX::pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DirectX::pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DirectX::pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	DirectX::pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DirectX::pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DirectX::pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	DirectX::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DirectX::pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DirectX::pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	DirectX::pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	DirectX::pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	DirectX::pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DirectX::pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DirectX::pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	ShowWindow(DirectX::hWnd, SW_SHOW);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 関数名: 更新
// 引数：なし
// 戻り値：なし
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool DirectX::Update(void)
{
	if (DirectX::msg.message != WM_QUIT)
	{
		if (Object::AutoUpdate)
			Object::UpdateAll();
		if (Object::AutoDraw)
			Object::DrawAll();
		DirectX::FrameCnt++;
		DirectX::FrameCnt %= 60;
		DirectX::pDevice->EndScene();
		DirectX::pDevice->Present(NULL, NULL, NULL, NULL);
		for (;;)
		{
			if (PeekMessage(&DirectX::msg, NULL, 0U, 0U, PM_REMOVE)) {
				TranslateMessage(&DirectX::msg);
				DispatchMessage(&DirectX::msg);
			}
			else
			{
				break;
			}
		}
		DirectX::pDevice->Clear(0, NULL, D3DCLEAR_TARGET, bgColor, 1.0f, 0);
		DirectX::pDevice->BeginScene();
		Input::Update();
		Camera::Update();
		return true;
	}

	return false;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 関数名: 更新
// 引数：なし
// 戻り値：なし
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::UnInit(void)
{
	SAFE_RELEASE(DirectX::pD3d);
	SAFE_RELEASE(DirectX::pDevice);
	SAFE_RELEASE(DirectX::pBuffer);
	SAFE_DELETE(DirectX::pProj);
	Texture::UnInit();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// ウィンドウプロシージャ
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
LRESULT CALLBACK DirectX::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:WmCreate(hWnd); break;                   //ウィンドウが作られた時
	case WM_COMMAND:WmCommand(hWnd, wParam, lParam); break; //コマンドが送られてきた時
	case WM_PAINT:WmPaint(hWnd); break;                     //ウィンドウが再描画された時
	case WM_MOVE:WmMove(hWnd, lParam); break;               //ウィンドウ座標が変わった時
	case WM_SIZE:WmSize(hWnd, lParam); break;               //ウィンドウ座標が変わった時
	case WM_MOUSEMOVE:WmMouseMove(hWnd, lParam); break;     //マウスの座標が変わった時
	case WM_LBUTTONDOWN:WmLButtonDown(hWnd); break;         //左クリックした時
	case WM_RBUTTONDOWN:WmRButtonDown(hWnd); break;         //右クリックした時
	case WM_LBUTTONUP:WmLButtonUp(hWnd); break;             //左クリックをやめた時
	case WM_RBUTTONUP:WmRButtonUp(hWnd); break;             //右クリックをやめた時
	case WM_KEYDOWN:WmKeyDown(hWnd, wParam); break;         //キーが押された時
	case WM_KEYUP:WmKeyUp(hWnd, wParam); break;             //キーが離された時
	case WM_DESTROY:PostQuitMessage(0); break;              //ウィンドウを閉じた時
	/*[×]ボタンが押された時*/
	case WM_CLOSE:
	{
		ShowCursor(true);
		UINT uID = MessageBox(NULL, "しゅうりょうしますか。", "しゅうりょうめっせーじ", MB_YESNO | MB_DEFBUTTON2);
		ShowCursor(false);
		if (uID == IDYES) DestroyWindow(hWnd); else return 0;
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// ウィンドウ生成時
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmCreate(HWND hWnd) {}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// ウィンドウコマンド
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// ウィンドウ描画時
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmPaint(HWND hWnd) {}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// ウィンドウ移動時
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmMove(HWND hWnd, LPARAM lParam) {}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// マウス移動時
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmMouseMove(HWND hWnd, LPARAM lParam)
{
	Input::MousePos.X = (SHORT)LOWORD(lParam);
	Input::MousePos.Y = (SHORT)HIWORD(lParam);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// ウィンドウサイズ変更時
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmSize(HWND hWnd, LPARAM lParam)
{
	if (!DirectX::pD3d)
		return;
	DirectX::d3dpp.BackBufferWidth = LOWORD(lParam);
	DirectX::d3dpp.BackBufferHeight = HIWORD(lParam);
	DirectX::Size.X = (SHORT)LOWORD(lParam);
	DirectX::Size.Y = (SHORT)HIWORD(lParam);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//【自動】左クリックしたとき
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmLButtonDown(HWND hWnd)
{
	//クリック情報更新
	Input::bLClick = true;

	SetFocus(hWnd);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//【自動】右クリックしたとき
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmRButtonDown(HWND hWnd)
{
	//クリック情報更新
	Input::bRClick = true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//【自動】左クリックをやめたとき
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmLButtonUp(HWND hWnd)
{
	//クリック情報更新
	Input::bLClick = false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//【自動】右クリックをやめたとき
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmRButtonUp(HWND hWnd)
{
	//クリック情報更新
	Input::bRClick = false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//【自動】キーが押されたとき
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmKeyDown(HWND hWnd, WPARAM wParam)
{
	//【必須】終了処理
	if (wParam == VK_ESCAPE)
	{
		ShowCursor(true);
		UINT uID = MessageBox(NULL, "しゅうりょうしますか。", "しゅうりょうめっせーじ", MB_YESNO | MB_DEFBUTTON2);
		ShowCursor(false);
		if (uID == IDYES) DestroyWindow(hWnd);
	}
	//キー入力情報更新
	Input::bKeys[wParam] = true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//【自動】キーが離されたとき
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectX::WmKeyUp(HWND hWnd, WPARAM wParam)
{
	//キー入力情報更新
	Input::bKeys[wParam] = false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//【呼出】Coord生成
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
COORD Coord(SHORT x, SHORT y)
{
	COORD coord = { x, y };

	return coord;
}

VECTOR2 Vector2(float x, float y)
{
	VECTOR2 v2 = { x, y };

	return v2;
}

VECTOR3 Vector3(float x, float y, float z)
{
	VECTOR3 v3 = { x, y, z };

	return v3;
}

BOOL2 Bool2(bool x, bool y)
{
	BOOL2 b2 = { x, y };

	return b2;
}