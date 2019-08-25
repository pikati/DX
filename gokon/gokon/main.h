#pragma once
#include <d3dx9.h>
#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/*directX�f�o�C�X����}�N��*/
#define SAFE_RELEASE(p) do { if(p){ (p)->Release(); (p) = NULL;} } while(0)
/*���_�t�H�[�}�b�g*/
#define FVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


/*�V�[���̏�ԊǗ��ϐ�*/
enum SCENE_STATE {
	SCENE_TITLE,
	SCENE_GAME
};


/*�v���g�^�C�v�錾*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//�������������֐�������//
HRESULT         Initialize(HWND, HINSTANCE);
//�������I�������֐�������//
void             Finalize(void);
LPDIRECT3DDEVICE9 GetDevice();
HWND GetHWND();
HINSTANCE GetHInstance();
/*getdc�e�L�X�g�n*/