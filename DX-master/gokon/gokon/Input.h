#pragma once
#include "main.h"
#define KEY_MAX 256
class Input
{
private:
	static HRESULT					m_ret;
	static LPDIRECTINPUTDEVICE8		m_lpKeyboard;
	static LPDIRECTINPUT8			m_lpDI;
	static BYTE						m_key[256];
	static BYTE						m_oldKey[256];
public:
	static HRESULT	Initialize();
	static void		Finalize();
	static bool		GetKey(UINT keyCode);
	static bool		TriggerKey(UINT keyCode);
};

