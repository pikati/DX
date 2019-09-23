#include <windows.h>
#include "main.h"
#include "Input.h"
#include "SceneManager.h"
#include "Sound.h"


//【DirectX9のデバイス】
//LPDIRECT3DDEVICE9は、DirectX9の機能を使う為のハンドル的な奴
//DirectX9の機能がここに詰まってるので間違って消さない様に。
//▼▼▼デバイス▼▼▼//
LPDIRECT3DDEVICE9	g_d3dDevice = NULL;
HWND				g_hWnd = NULL;
HINSTANCE			g_hInstance;
LPDIRECT3D9			g_pD3D = NULL;

HMENU  g_hMenu = NULL;
D3DPRESENT_PARAMETERS g_D3DPPWindow;
D3DPRESENT_PARAMETERS g_D3DPPFull;
D3DPRESENT_PARAMETERS g_D3DPP;    // D3DDeviceの設定(現在)

bool g_bWindow = true;
RECT  g_rectWindow;

void ChangeDisplayMode(void);
//■■■■■■■■■■■■■■■■//
//■■■【エントリポイント】■■■//
//■■■■■■■■■■■■■■■■//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	g_hInstance = hInstance;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.lpszClassName = "PIKATAN";//重要
	wc.lpfnWndProc = (WNDPROC)WndProc;//重要 関数ポインタ
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "ウィンドウクラスの構造体の初期化エラー", "", MB_OK);
	}
	g_hWnd = CreateWindow(wc.lpszClassName,
		"DirectX9　サンプルプログラム",
		WS_VISIBLE /*| WS_POPUP*/,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		720,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	//▼▼▼ここで初期化▼▼▼//
	if (FAILED(Initialize(g_hWnd, hInstance))) return -1;

	//メインループ
	while (1)
	{
		//メッセージあったら実行されるやつ
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0) == 0)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);//システムに返す
		}
		else {
			SceneManager::Update();
			SceneManager::Draw();
		}
	}
	
	//DirectX終了処理関数
	Finalize();
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch (wParam)
		{
		case VK_RETURN:     // Alt + Enterを押すと切り替え
			ChangeDisplayMode();
			break;
		default:
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HRESULT Initialize(HWND hWnd, HINSTANCE hInst)
{
	//▼▼▼どんなDirectX9を作りたいの？▼▼▼//
	//▼▼▼ぶっちゃけおまじない▼▼▼//
	
	ZeroMemory(&g_D3DPPFull, sizeof(g_D3DPPFull));
	//フロントバッファとバックバッファの切り替え方法を定義
	//D3DSWAPEFFECT_DISCARDは自動でで判断してくれるけどαブレンドの効果が保証されないけどなんかこれでええんやって
	g_D3DPPFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3DPPFull.BackBufferFormat = D3DFMT_X8R8G8B8;	//画面のフォーマットを格納 1ピクセルの色の定義情報のこと 楽する設定
	g_D3DPPFull.BackBufferWidth = 1920;
	g_D3DPPFull.BackBufferHeight = 1080;
	g_D3DPPFull.BackBufferCount = 1;
	g_D3DPPFull.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_D3DPPFull.MultiSampleQuality = 0;
	g_D3DPPFull.hDeviceWindow = g_hWnd;
	g_D3DPPFull.Windowed = TRUE;
	g_D3DPPFull.EnableAutoDepthStencil = FALSE;
	g_D3DPPFull.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	g_D3DPPFull.Flags = 0;
	g_D3DPPFull.FullScreen_RefreshRateInHz = 0;
	g_D3DPPFull.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	ZeroMemory(&g_D3DPPWindow, sizeof(g_D3DPPWindow));

	g_D3DPPWindow.BackBufferWidth = 0;
	g_D3DPPWindow.BackBufferHeight = 0;
	g_D3DPPWindow.BackBufferFormat = D3DFMT_UNKNOWN;
	g_D3DPPWindow.BackBufferCount = 1;
	g_D3DPPWindow.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_D3DPPWindow.MultiSampleQuality = 0;
	g_D3DPPWindow.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3DPPWindow.hDeviceWindow = g_hWnd;
	g_D3DPPWindow.Windowed = TRUE;
	g_D3DPPWindow.EnableAutoDepthStencil = FALSE;
	g_D3DPPWindow.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	g_D3DPPWindow.Flags = 0;
	g_D3DPPWindow.FullScreen_RefreshRateInHz = 0;
	g_D3DPPWindow.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	g_rectWindow.top = 0;
	g_rectWindow.left = 0;
	g_rectWindow.right =1920;
	g_rectWindow.bottom = 1080;
	AdjustWindowRect(&g_rectWindow, WS_OVERLAPPEDWINDOW, FALSE);
	g_rectWindow.right = g_rectWindow.right - g_rectWindow.left;
	g_rectWindow.bottom = g_rectWindow.bottom - g_rectWindow.top;
	g_rectWindow.top = 0;
	g_rectWindow.left = 0;

	//IDIRCT3D9コンポーネントの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == g_pD3D)
	{
		return E_FAIL;
	}

	//▼▼▼デバイスの生成▼▼▼//
	HRESULT hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,	//ディスプレイアダプタ番号ほとんどはこれでOK
		D3DDEVTYPE_HAL,		//D3DDEVTYPE列挙型のメンバを指定 HAL:ハードウェアを最大に生かしたパフォーマンス REF:ソフトウェアで描画 基本HALでいいがハードウェアがサポートしていな機能がある場合に注意
		hWnd,				//ウィンドウハンドル	
		D3DCREATE_HARDWARE_VERTEXPROCESSING,//デバイスの作成を制御するオプションフラグ どこで頂点処理させるかを選ぶ
		&g_D3DPPFull,				//D3DPRESENT_PARAMETERS構造体へのポインタを指定
		&g_d3dDevice);		//IDirect3DDevice9コンポーネントへのポインタを指定
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	g_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//dinput初期化
	if (Input::Initialize()) {
		return E_FAIL;
	}
	Sound::Initialize();
	SceneManager::Initialize();
	
	return S_OK;
}

//■■■■■■■■■■■■■■■■//
//■■■【DirectX終了処理】 ■■■//
//■■■■■■■■■■■■■■■■//
void Finalize(void)
{
	SceneManager::Finalize();
	Sound::Finalize();
	Input::Finalize();
	SAFE_RELEASE(g_d3dDevice);
	SAFE_RELEASE(g_pD3D);
}

LPDIRECT3DDEVICE9 GetDevice() {
	return g_d3dDevice;
}

HWND GetHWND() {
	return g_hWnd;
}

HINSTANCE GetHInstance() {
	return g_hInstance;
}

#if 0
◎頂点フォーマットってなんぞや？
→頂点にどんな情報を持たせるかを指定する仕組み。

D3DFVFの組み合わせで色々な頂点情報を持たせる事が可能
そして、そのフォーマットに対応した頂点構造体を自分で生成し、
その構造体をGPUへ転送する事で頂点情報を伝える事が出来る。

例えば、D3DFVF_XYZは、頂点にXYZの座標を付与する。

D3DFVF_XYZRHWは、頂点情報と、射影変換フラグを付与する。
射影変換フラグは2D描画をする間は1を設定する。
射影変換フラグは3D描画を行う時に重要となる。

D3DFVF_DIFFUSEは頂点に色情報を持たせる事が出来る。
これをいじる事で頂点の色が変わる。

等々、様々なフォーマットがあるので自分で調べてみよう
#endif

void ChangeDisplayMode(void)
{
	g_bWindow = !g_bWindow;

	if (g_bWindow)
	{
		g_D3DPP = g_D3DPPWindow;
	}
	else
	{
		g_D3DPP = g_D3DPPFull;
		GetWindowRect(g_hWnd, &g_rectWindow);
	}

	HRESULT hr = g_d3dDevice->Reset(&g_D3DPP);
	if (FAILED(hr))
	{
		if (hr != D3DERR_DEVICELOST)
			DestroyWindow(g_hWnd);
			
		return;
	}


	if (g_bWindow)
	{
		SetWindowLong(g_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		if (g_hMenu != NULL)
		{
			SetMenu(g_hWnd, g_hMenu);
			g_hMenu = NULL;
		}
		SetWindowPos(g_hWnd, HWND_NOTOPMOST,
			g_rectWindow.left, g_rectWindow.top,
			g_rectWindow.right - g_rectWindow.left,
			g_rectWindow.bottom - g_rectWindow.top,
			SWP_SHOWWINDOW);
	}
	else
	{
		SetWindowLong(g_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		if (g_hMenu == NULL)
		{
			g_hMenu = GetMenu(g_hWnd);
			SetMenu(g_hWnd, NULL);
		}
	}
	g_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}