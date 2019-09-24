#pragma once
#include "main.h"
#include "dsound.h"
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
class Sound
{
private:
	static const int				BGM_NUM = 3;
	static const int				SE_NUM = 5;
	//サウンドデバイス
	static LPDIRECTSOUND8			m_pDS;
	//プライマリサウンドバッファ
	static LPDIRECTSOUNDBUFFER		m_pPrimary;
	//セカンダリサウンドバッファ
	static LPDIRECTSOUNDBUFFER		m_pSecondaryBGM[BGM_NUM];
	static LPDIRECTSOUNDBUFFER		m_pSecondarySE[SE_NUM];

	static bool CreatePrimaryBuffer();
	static bool CreateSecondaryBuffer(LPDIRECTSOUNDBUFFER *dsb, const char *file);
public:
	static void Initialize();
	static void Finalize();
	static LPDIRECTSOUNDBUFFER SE(int idx);
	static LPDIRECTSOUNDBUFFER BGM(int idx);
};

