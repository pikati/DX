#include "Input.h"

HRESULT					Input::m_ret = NULL;
LPDIRECTINPUTDEVICE8	Input::m_lpKeyboard = NULL;
LPDIRECTINPUT8			Input::m_lpDI = NULL;
BYTE					Input::m_key[256];
BYTE					Input::m_oldKey[256];

HRESULT Input::Initialize() {
	m_ret = DirectInput8Create(GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_lpDI, NULL);
	if (FAILED(m_ret)) {
		return E_FAIL;
	}
	m_ret = m_lpDI->CreateDevice(GUID_SysKeyboard, &m_lpKeyboard, NULL);
	if (FAILED(m_ret)) {
		return E_FAIL;
	}
	m_ret = m_lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(m_ret)) {
		SAFE_RELEASE(m_lpKeyboard);
		SAFE_RELEASE(m_lpDI);
		return E_FAIL;
	}
	m_ret = m_lpKeyboard->SetCooperativeLevel(GetHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(m_ret)) {
		SAFE_RELEASE(m_lpKeyboard);
		SAFE_RELEASE(m_lpDI);

		return E_FAIL;
	}
	memset(&m_key, 0, sizeof(m_key));
	memset(&m_oldKey, 0, sizeof(m_oldKey));
	m_lpKeyboard->Acquire();
	return S_OK;
}

void Input::Finalize() {
	m_lpKeyboard->Unacquire();
	SAFE_RELEASE(m_lpKeyboard);
	SAFE_RELEASE(m_lpDI);
}

bool Input::GetKey(UINT keyCode) {
	//�`�F�b�N�t���O
	bool flag = false;

	//�L�[�����擾
	ZeroMemory(m_key, sizeof(m_key));
	m_ret = m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	if (FAILED(m_ret)) {
		// ���s�Ȃ�ĊJ�����Ă�����x�擾
		m_lpKeyboard->Acquire();
		m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	}
	if (m_key[keyCode] & 0x80)
	{
		flag = true;
	}
	m_oldKey[keyCode] = m_key[keyCode];

	return flag;
}

bool Input::TriggerKey(UINT index)
{
	//�`�F�b�N�t���O
	bool flag = false;

	//�L�[�����擾
	ZeroMemory(m_key, sizeof(m_key));
	m_ret = m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	if (FAILED(m_ret)) {
		// ���s�Ȃ�ĊJ�����Ă�����x�擾
		m_lpKeyboard->Acquire();
		m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	}
	if ((m_key[index] & 0x80) && !(m_oldKey[index] & 0x80))
	{
		flag = true;
	}
	m_oldKey[index] = m_key[index];

	return flag;
}