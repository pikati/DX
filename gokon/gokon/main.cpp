#include <windows.h>
#include "main.h"
#include "Input.h"
#include "SceneManager.h"
#include "Sound.h"


//�yDirectX9�̃f�o�C�X�z
//LPDIRECT3DDEVICE9�́ADirectX9�̋@�\���g���ׂ̃n���h���I�ȓz
//DirectX9�̋@�\�������ɋl�܂��Ă�̂ŊԈ���ď����Ȃ��l�ɁB
//�������f�o�C�X������//
LPDIRECT3DDEVICE9	g_d3dDevice = NULL;
HWND				g_hWnd = NULL;
HINSTANCE			g_hInstance;
LPDIRECT3D9			g_pD3D = NULL;

HMENU  g_hMenu = NULL;
D3DPRESENT_PARAMETERS g_D3DPPWindow;
D3DPRESENT_PARAMETERS g_D3DPPFull;
D3DPRESENT_PARAMETERS g_D3DPP;    // D3DDevice�̐ݒ�(����)

bool g_bWindow = true;
RECT  g_rectWindow;

void ChangeDisplayMode(void);
//��������������������������������//
//�������y�G���g���|�C���g�z������//
//��������������������������������//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	g_hInstance = hInstance;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.lpszClassName = "PIKATAN";//�d�v
	wc.lpfnWndProc = (WNDPROC)WndProc;//�d�v �֐��|�C���^
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "�E�B���h�E�N���X�̍\���̂̏������G���[", "", MB_OK);
	}
	g_hWnd = CreateWindow(wc.lpszClassName,
		"DirectX9�@�T���v���v���O����",
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

	//�����������ŏ�����������//
	if (FAILED(Initialize(g_hWnd, hInstance))) return -1;

	//���C�����[�v
	while (1)
	{
		//���b�Z�[�W����������s�������
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0) == 0)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);//�V�X�e���ɕԂ�
		}
		else {
			SceneManager::Update();
			SceneManager::Draw();
		}
	}
	
	//DirectX�I�������֐�
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
	case WM_SYSKEYDOWN:     // Alt + ����L�[�̏����Ɏg��
		switch (wParam)
		{
		case VK_RETURN:     // Alt + Enter�������Ɛ؂�ւ�
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
	//�������ǂ��DirectX9����肽���́H������//
	//�������Ԃ����Ⴏ���܂��Ȃ�������//
	
	ZeroMemory(&g_D3DPPFull, sizeof(g_D3DPPFull));
	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̐؂�ւ����@���`
	//D3DSWAPEFFECT_DISCARD�͎����łŔ��f���Ă���邯�ǃ��u�����h�̌��ʂ��ۏ؂���Ȃ����ǂȂ񂩂���ł���������
	g_D3DPPFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3DPPFull.BackBufferFormat = D3DFMT_X8R8G8B8;	//��ʂ̃t�H�[�}�b�g���i�[ 1�s�N�Z���̐F�̒�`���̂��� �y����ݒ�
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

	//IDIRCT3D9�R���|�[�l���g�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == g_pD3D)
	{
		return E_FAIL;
	}

	//�������f�o�C�X�̐���������//
	HRESULT hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,	//�f�B�X�v���C�A�_�v�^�ԍ��قƂ�ǂ͂����OK
		D3DDEVTYPE_HAL,		//D3DDEVTYPE�񋓌^�̃����o���w�� HAL:�n�[�h�E�F�A���ő�ɐ��������p�t�H�[�}���X REF:�\�t�g�E�F�A�ŕ`�� ��{HAL�ł������n�[�h�E�F�A���T�|�[�g���Ă��ȋ@�\������ꍇ�ɒ���
		hWnd,				//�E�B���h�E�n���h��	
		D3DCREATE_HARDWARE_VERTEXPROCESSING,//�f�o�C�X�̍쐬�𐧌䂷��I�v�V�����t���O �ǂ��Œ��_���������邩��I��
		&g_D3DPPFull,				//D3DPRESENT_PARAMETERS�\���̂ւ̃|�C���^���w��
		&g_d3dDevice);		//IDirect3DDevice9�R���|�[�l���g�ւ̃|�C���^���w��
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	g_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//dinput������
	if (Input::Initialize()) {
		return E_FAIL;
	}
	Sound::Initialize();
	SceneManager::Initialize();
	
	return S_OK;
}

//��������������������������������//
//�������yDirectX�I�������z ������//
//��������������������������������//
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
�����_�t�H�[�}�b�g���ĂȂ񂼂�H
�����_�ɂǂ�ȏ����������邩���w�肷��d�g�݁B

D3DFVF�̑g�ݍ��킹�ŐF�X�Ȓ��_�����������鎖���\
�����āA���̃t�H�[�}�b�g�ɑΉ��������_�\���̂������Ő������A
���̍\���̂�GPU�֓]�����鎖�Œ��_����`���鎖���o����B

�Ⴆ�΁AD3DFVF_XYZ�́A���_��XYZ�̍��W��t�^����B

D3DFVF_XYZRHW�́A���_���ƁA�ˉe�ϊ��t���O��t�^����B
�ˉe�ϊ��t���O��2D�`�������Ԃ�1��ݒ肷��B
�ˉe�ϊ��t���O��3D�`����s�����ɏd�v�ƂȂ�B

D3DFVF_DIFFUSE�͒��_�ɐF�����������鎖���o����B
����������鎖�Œ��_�̐F���ς��B

���X�A�l�X�ȃt�H�[�}�b�g������̂Ŏ����Œ��ׂĂ݂悤
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