#pragma once
#include <d3dx9.h>
#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/*directXデバイス解放マクロ*/
#define SAFE_RELEASE(p) do { if(p){ (p)->Release(); (p) = NULL;} } while(0)
/*頂点フォーマット*/
#define FVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


/*シーンの状態管理変数*/
enum SCENE_STATE {
	SCENE_TITLE,
	SCENE_GAME
};


/*プロトタイプ宣言*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//▼▼▼初期化関数▼▼▼//
HRESULT         Initialize(HWND, HINSTANCE);
//▼▼▼終了処理関数▼▼▼//
void             Finalize(void);
LPDIRECT3DDEVICE9 GetDevice();
HWND GetHWND();
HINSTANCE GetHInstance();
/*getdcテキスト系*/