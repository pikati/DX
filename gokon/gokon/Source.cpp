//
////----------------------------------------------------------
//// �t���X�N���[���؂�ւ� ( Alt + Enter )
////--------------------------------------------------------------
//
//#include <windows.h>
//#include <d3dx9.h>
//#include <dxerr9.h>
//
//#define RELEASE(x) if(x){x->Release();x=NULL;}
//
//HINSTANCE g_hInstance = NULL; // �C���X�^���X�E�n���h��
//HWND  g_hWindow = NULL; // �E�C���h�E�E�n���h��
//HMENU  g_hMenu = NULL; // ���j���[�E�n���h��
//
//LPCSTR  g_szAppTitle = "DirectX9 Screen Change";
//LPCSTR  g_szWndClass = "Window1";
//
//RECT  g_rectWindow;       // �E�C���h�E�E���[�h�ł̍Ō�̈ʒu
//
//// �N�����̕`��̈�T�C�Y
//bool  g_bWindow = true;      // �N�����̉�ʃ��[�h
//
//SIZE  g_sizeWindowMode = { 640, 480 };  // �E�C���h�E�E���[�h
//SIZE  g_sizeFullMode = { 640, 480 };  // �t���X�N���[���E���[�h
//D3DFORMAT g_formatFull = D3DFMT_X8R8G8B8;  // �f�B�X�v���C(�o�b�N�E�o�b�t�@)�E�t�H�[�}�b�g
//
//// �A�v���P�[�V�����̓���t���O
//bool  g_bActive = false; // �A�N�e�B�u���
//
///*-------------------------------------------
// �O���[�o���ϐ�(DirectX�֘A)
//--------------------------------------------*/
//
//// �C���^�[�t�F�C�X
//LPDIRECT3D9    g_pD3D = NULL; // Direct3D�C���^�[�t�F�C�X
//LPDIRECT3DDEVICE9  g_pD3DDevice = NULL; // Direct3DDevice�C���^�[�t�F�C�X
//D3DPRESENT_PARAMETERS g_D3DPP;    // D3DDevice�̐ݒ�(����)
//
//D3DPRESENT_PARAMETERS g_D3DPPWindow;   // D3DDevice�̐ݒ�(�E�C���h�E�E���[�h�p)
//D3DPRESENT_PARAMETERS g_D3DPPFull;   // D3DDevice�̐ݒ�(�t���X�N���[���E���[�h�p)
//
//bool g_bDeviceLost = false;      // �f�o�C�X�̏����t���O
//
///*-------------------------------------------
// �֐���`
//--------------------------------------------*/
//
//LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam);
//
///*-------------------------------------------
// �A�v���P�[�V�����������i�ŏ��Ɉ�x�����Ă΂��j
//--------------------------------------------*/
//HRESULT InitApp(HINSTANCE hInst)
//{
//	// �A�v���P�[�V�����̃C���X�^���X�E�n���h����ۑ�
//	g_hInstance = hInst;
//
//	// IME���֎~����
//	ImmDisableIME(-1); // ���̃X���b�h�ŋ֎~
//
//	// �E�C���h�E�E�N���X�̓o�^
//	WNDCLASSEX wcex;
//	wcex.cbSize = sizeof(WNDCLASSEX);
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = (WNDPROC)MainWndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInst;
//	wcex.hIcon = NULL;
//	wcex.hIconSm = NULL;
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.lpszMenuName = NULL;
//	wcex.lpszClassName = g_szWndClass;
//
//	if (!RegisterClassEx(&wcex))
//		return DXTRACE_ERR("InitApp", GetLastError());
//
//	// ���C���E�E�C���h�E�쐬
//	g_rectWindow.top = 0;
//	g_rectWindow.left = 0;
//	g_rectWindow.right = g_sizeWindowMode.cx;
//	g_rectWindow.bottom = g_sizeWindowMode.cy;
//	AdjustWindowRect(&g_rectWindow, WS_OVERLAPPEDWINDOW, FALSE);
//	g_rectWindow.right = g_rectWindow.right - g_rectWindow.left;
//	g_rectWindow.bottom = g_rectWindow.bottom - g_rectWindow.top;
//	g_rectWindow.top = 0;
//	g_rectWindow.left = 0;
//
//	RECT rect;
//	if (g_bWindow)
//	{
//		// (�E�C���h�E�E���[�h�p)
//		rect.top = CW_USEDEFAULT;
//		rect.left = CW_USEDEFAULT;
//		rect.right = g_rectWindow.right;
//		rect.bottom = g_rectWindow.bottom;
//	}
//	else
//	{
//		// (�t���X�N���[���E���[�h�p)
//		rect.top = 0;
//		rect.left = 0;
//		rect.right = g_sizeFullMode.cx;
//		rect.bottom = g_sizeFullMode.cy;
//
//		//g_hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_MENU1));
//	}
//
//	g_hWindow = CreateWindow(g_szWndClass, g_szAppTitle,
//		g_bWindow ? WS_OVERLAPPEDWINDOW : WS_POPUP,
//		rect.left, rect.top, rect.right, rect.bottom,
//		NULL, NULL, hInst, NULL);
//	if (g_hWindow == NULL)
//		return DXTRACE_ERR("InitApp", GetLastError());
//
//	// �E�C���h�E�\��
//	ShowWindow(g_hWindow, SW_SHOWNORMAL);
//	UpdateWindow(g_hWindow);
//
//	return S_OK;
//}
//
///*-------------------------------------------
// DirectX Graphics������
//--------------------------------------------*/
//HRESULT InitDXGraphics(void)
//{
//	// Direct3D�I�u�W�F�N�g�̍쐬
//	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
//	if (g_pD3D == NULL)
//		return DXTRACE_ERR("InitDXGraphics Direct3DCreate9", E_FAIL);
//
//	// D3DDevice�I�u�W�F�N�g�̐ݒ�(�E�C���h�E�E���[�h�p)
//	ZeroMemory(&g_D3DPPWindow, sizeof(g_D3DPPWindow));
//
//	g_D3DPPWindow.BackBufferWidth = 0;
//	g_D3DPPWindow.BackBufferHeight = 0;
//	g_D3DPPWindow.BackBufferFormat = D3DFMT_UNKNOWN;
//	g_D3DPPWindow.BackBufferCount = 1;
//	g_D3DPPWindow.MultiSampleType = D3DMULTISAMPLE_NONE;
//	g_D3DPPWindow.MultiSampleQuality = 0;
//	g_D3DPPWindow.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	g_D3DPPWindow.hDeviceWindow = g_hWindow;
//	g_D3DPPWindow.Windowed = TRUE;
//	g_D3DPPWindow.EnableAutoDepthStencil = FALSE;
//	g_D3DPPWindow.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
//	g_D3DPPWindow.Flags = 0;
//	g_D3DPPWindow.FullScreen_RefreshRateInHz = 0;
//	g_D3DPPWindow.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
//
//	// D3DDevice�I�u�W�F�N�g�̐ݒ�(�t���X�N���[���E���[�h)
//	ZeroMemory(&g_D3DPPFull, sizeof(g_D3DPPFull));
//
//	g_D3DPPFull.BackBufferWidth = g_sizeFullMode.cx;
//	g_D3DPPFull.BackBufferHeight = g_sizeFullMode.cy;
//	g_D3DPPFull.BackBufferFormat = g_formatFull;
//	g_D3DPPFull.BackBufferCount = 1;
//	g_D3DPPFull.MultiSampleType = D3DMULTISAMPLE_NONE;
//	g_D3DPPFull.MultiSampleQuality = 0;
//	g_D3DPPFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	g_D3DPPFull.hDeviceWindow = g_hWindow;
//	g_D3DPPFull.Windowed = FALSE;
//	g_D3DPPFull.EnableAutoDepthStencil = FALSE;
//	g_D3DPPFull.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
//	g_D3DPPFull.Flags = 0;
//	g_D3DPPFull.FullScreen_RefreshRateInHz = 0;
//	g_D3DPPFull.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
//
//	// D3DDevice�I�u�W�F�N�g�̍쐬
//	if (g_bWindow)
//		g_D3DPP = g_D3DPPWindow;
//	else
//		g_D3DPP = g_D3DPPFull;
//
//	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWindow,
//		D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
//	if (FAILED(hr))
//	{
//		hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, g_hWindow,
//			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
//		if (FAILED(hr))
//			return DXTRACE_ERR("InitDXGraphics CreateDevice", hr);
//	}
//
//	// �r���[�|�[�g�̐ݒ�
//	D3DVIEWPORT9 vp;
//	vp.X = 0;
//	vp.Y = 0;
//	vp.Width = g_D3DPP.BackBufferWidth;
//	vp.Height = g_D3DPP.BackBufferHeight;
//	vp.MinZ = 0.0f;
//	vp.MaxZ = 1.0f;
//	hr = g_pD3DDevice->SetViewport(&vp);
//	if (FAILED(hr))
//		return DXTRACE_ERR("InitDXGraphics SetViewport", hr);
//
//	return S_OK;
//}
//
//
///*--------------------------------------------
// ��ʂ̕`�揈��
//--------------------------------------------*/
//HRESULT Render(void)
//{
//	// �V�[���̃N���A
//	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
//
//	// �V�[���̕`��J�n
//	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
//	{
//
//		// �V�[���̕`��I��
//		g_pD3DDevice->EndScene();
//	}
//
//	// �V�[���̕\��
//	return g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
//}
//
//
//
///*-------------------------------------------
// �E�C���h�E�E�T�C�Y�̕ύX
//--------------------------------------------*/
//HRESULT ChangeWindowSize(void)
//{
//	// �E�C���h�E�̃N���C�A���g�̈�ɍ��킹��
//
//	HRESULT hr = g_pD3DDevice->Reset(&g_D3DPP);
//	if (FAILED(hr))
//	{
//		if (hr == D3DERR_DEVICELOST)
//			g_bDeviceLost = true;
//		else
//			DestroyWindow(g_hWindow);
//		return DXTRACE_ERR("ChangeWindowSize Reset", hr);
//	}
//
//	// �r���[�|�[�g�̐ݒ�
//	D3DVIEWPORT9 vp;
//	vp.X = 0;
//	vp.Y = 0;
//	vp.Width = g_D3DPP.BackBufferWidth;
//	vp.Height = g_D3DPP.BackBufferHeight;
//	vp.MinZ = 0.0f;
//	vp.MaxZ = 1.0f;
//	hr = g_pD3DDevice->SetViewport(&vp);
//	if (FAILED(hr))
//	{
//		DXTRACE_ERR("ChangeWindowSize SetViewport", hr);
//		DestroyWindow(g_hWindow);
//	}
//	return hr;
//}
//
///*-------------------------------------------
// ��ʃ��[�h�̕ύX
//--------------------------------------------*/
//void ChangeDisplayMode(void)
//{
//	g_bWindow = !g_bWindow;
//
//	if (g_bWindow)
//	{
//		g_D3DPP = g_D3DPPWindow;
//	}
//	else
//	{
//		g_D3DPP = g_D3DPPFull;
//		GetWindowRect(g_hWindow, &g_rectWindow);
//	}
//
//	HRESULT hr = g_pD3DDevice->Reset(&g_D3DPP);
//	if (FAILED(hr))
//	{
//		if (hr == D3DERR_DEVICELOST)
//			g_bDeviceLost = true;
//		else
//			DestroyWindow(g_hWindow);
//		DXTRACE_ERR("ChangeDisplayMode Reset", hr);
//		return;
//	}
//
//
//	if (g_bWindow)
//	{
//		SetWindowLong(g_hWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
//		if (g_hMenu != NULL)
//		{
//			SetMenu(g_hWindow, g_hMenu);
//			g_hMenu = NULL;
//		}
//		SetWindowPos(g_hWindow, HWND_NOTOPMOST,
//			g_rectWindow.left, g_rectWindow.top,
//			g_rectWindow.right - g_rectWindow.left,
//			g_rectWindow.bottom - g_rectWindow.top,
//			SWP_SHOWWINDOW);
//	}
//	else
//	{
//		SetWindowLong(g_hWindow, GWL_STYLE, WS_POPUP | WS_VISIBLE);
//		if (g_hMenu == NULL)
//		{
//			g_hMenu = GetMenu(g_hWindow);
//			SetMenu(g_hWindow, NULL);
//		}
//	}
//}
//
///*-------------------------------------------
// DirectX Graphics�̏I������(�������Ɏ��s�����Ƃ����Ă΂��)
//--------------------------------------------*/
//bool CleanupDXGraphics(void)
//{
//
//	RELEASE(g_pD3DDevice);
//	RELEASE(g_pD3D);
//
//	return true;
//}
//
///*-------------------------------------------
// �A�v���P�[�V�����̏I�������i�Ō�ɌĂ΂��j
//--------------------------------------------*/
//bool CleanupApp(void)
//{
//	// ���j���[�E�n���h���̍폜
//	if (g_hMenu)
//		DestroyMenu(g_hMenu);
//
//	// �E�C���h�E�E�N���X�̓o�^����
//	UnregisterClass(g_szWndClass, g_hInstance);
//	return true;
//}
//
///*-------------------------------------------
// �E�B���h�E����
//--------------------------------------------*/
//LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, UINT wParam, LONG lParam)
//{
//	HRESULT hr = S_OK;
//
//	switch (msg)
//	{
//	case WM_ACTIVATE:
//		g_bActive = (LOWORD(wParam) != 0);
//		break;
//
//	case WM_DESTROY:
//		// DirectX Graphics�̏I������
//		CleanupDXGraphics();
//		// �E�C���h�E�����
//		PostQuitMessage(0);
//		g_hWindow = NULL;
//		return 0;
//
//		// �E�C���h�E�E�T�C�Y�̕ύX����
//	case WM_SIZE:
//		if (g_D3DPP.Windowed != TRUE)
//			break;
//
//		if (!g_pD3DDevice || wParam == SIZE_MINIMIZED)
//			break;
//		g_D3DPP.BackBufferWidth = LOWORD(lParam);
//		g_D3DPP.BackBufferHeight = HIWORD(lParam);
//		if (g_bDeviceLost)
//			break;
//		if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
//			ChangeWindowSize();
//		break;
//
//	case WM_SETCURSOR:
//		if (g_D3DPP.Windowed != TRUE)
//		{
//			SetCursor(NULL);
//			return 1;
//		}
//		break;
//
//	case WM_KEYDOWN:
//		// �L�[���͂̏���
//		switch (wParam)
//		{
//		case VK_ESCAPE: // [ESCAPE]�L�[�ŃE�C���h�E�����
//			PostMessage(hWnd, WM_CLOSE, 0, 0);
//			break;
//		}
//		break;
//	case WM_SYSKEYDOWN:     // Alt + ����L�[�̏����Ɏg��
//		switch (wParam)
//		{
//		case VK_RETURN:     // Alt + Enter�������Ɛ؂�ւ�
//			ChangeDisplayMode();
//			break;
//		default:
//			break;
//		}
//		break;
//	}
//
//	// �f�t�H���g����
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
///*--------------------------------------------
// �A�C�h�����̏���
//--------------------------------------------*/
//bool AppIdle(void)
//{
//	if (!g_pD3D || !g_pD3DDevice)
//		return false;
//
//	if (!g_bActive)
//		return true;
//
//	// ���������f�o�C�X�̕�������
//	HRESULT hr;
//	if (g_bDeviceLost)
//	{
//		Sleep(100); // 0.1�b�҂�
//
//		// �f�o�C�X��Ԃ̃`�F�b�N
//		hr = g_pD3DDevice->TestCooperativeLevel();
//		if (FAILED(hr))
//		{
//			if (hr == D3DERR_DEVICELOST)
//				return true;  // �f�o�C�X�͂܂������Ă���
//
//			if (hr != D3DERR_DEVICENOTRESET)
//				return false; // �\�����ʃG���[
//
//			hr = g_pD3DDevice->Reset(&g_D3DPP); // ���������݂�
//			if (FAILED(hr))
//			{
//				if (hr == D3DERR_DEVICELOST)
//					return true; // �f�o�C�X�͂܂������Ă���
//
//				DXTRACE_ERR("AppIdle Reset", hr);
//				return false; // �f�o�C�X�̕����Ɏ��s
//			}
//
//		}
//		// �f�o�C�X����������
//		g_bDeviceLost = false;
//	}
//
//	// ��ʂ̍X�V
//	hr = Render();
//	if (hr == D3DERR_DEVICELOST)
//		g_bDeviceLost = true; // �f�o�C�X�̏���
//	else if (FAILED(hr))
//		return false;
//
//	return true;
//}
//
///*--------------------------------------------
// ���C��
//---------------------------------------------*/
//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
//{
//	// �A�v���P�[�V�����Ɋւ��鏉����
//	HRESULT hr = InitApp(hInst);
//	if (FAILED(hr))
//	{
//		DXTRACE_ERR("WinMain InitApp", hr);
//		return 0;
//	}
//
//	// DirectX Graphics�̏�����
//	hr = InitDXGraphics();
//	if (FAILED(hr))
//		DXTRACE_ERR("WinMain InitDXGraphics", hr);
//
//
//	// ���b�Z�[�W�E���[�v
//	MSG msg;
//	do
//	{
//		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			// �A�C�h������
//			if (!AppIdle())
//				// �G���[������ꍇ�C�A�v���P�[�V�������I������
//				DestroyWindow(g_hWindow);
//		}
//	} while (msg.message != WM_QUIT);
//
//	// �A�v���P�[�V�����̏I������
//	CleanupApp();
//
//	return msg.wParam;
//}