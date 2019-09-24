#include "Sound.h"


const int Sound::BGM_NUM;
const int Sound::SE_NUM;
//�T�E���h�f�o�C�X
LPDIRECTSOUND8 Sound::m_pDS = NULL;
//�v���C�}���T�E���h�o�b�t�@
LPDIRECTSOUNDBUFFER Sound::m_pPrimary = NULL;
//�Z�J���_���T�E���h�o�b�t�@
LPDIRECTSOUNDBUFFER Sound::m_pSecondaryBGM[BGM_NUM];
LPDIRECTSOUNDBUFFER Sound::m_pSecondarySE[SE_NUM];

void Sound::Initialize() {
	HRESULT ret = DirectSoundCreate8(NULL, &m_pDS, NULL);
	ret = m_pDS->SetCooperativeLevel(GetHWND(), DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	CreatePrimaryBuffer();
	CreateSecondaryBuffer(&m_pSecondaryBGM[0], "BGM/Title.wav");
	CreateSecondaryBuffer(&m_pSecondaryBGM[1], "BGM/Game.wav");
	CreateSecondaryBuffer(&m_pSecondaryBGM[2], "BGM/Result.wav");
	CreateSecondaryBuffer(&m_pSecondarySE[0], "SE/Decision.wav");
	CreateSecondaryBuffer(&m_pSecondarySE[1], "SE/StarAtk.wav");
	CreateSecondaryBuffer(&m_pSecondarySE[2], "SE/Damage.wav");
	CreateSecondaryBuffer(&m_pSecondarySE[3], "SE/Cancel.wav");
	CreateSecondaryBuffer(&m_pSecondarySE[4], "SE/LVUP.wav");
}

void Sound::Finalize() {
	for (int i = SE_NUM; i >= 0; i--) {
		SAFE_RELEASE(m_pSecondarySE[i]);
	}
	for (int i = BGM_NUM; i >= 0; i--) {
		SAFE_RELEASE(m_pSecondaryBGM[i]);
	}
	SAFE_RELEASE(m_pPrimary);
}

bool Sound::CreatePrimaryBuffer() {
	WAVEFORMATEX wf;

	// �v���C�}���T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;
	HRESULT ret = m_pDS->CreateSoundBuffer(&dsdesc, &m_pPrimary, NULL);
	if (FAILED(ret)) {
		return FALSE;
	}

	// �v���C�}���o�b�t�@�̃X�e�[�^�X������
	wf.cbSize = sizeof(WAVEFORMATEX);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	ret = m_pPrimary->SetFormat(&wf);
	if (FAILED(ret)) {
		return FALSE;
	}

	return TRUE;
}

bool Sound::CreateSecondaryBuffer(LPDIRECTSOUNDBUFFER *dsb, const char *file)
{
	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveData;
	LPWAVEFORMATEX wf;

	// WAV�t�@�C�������[�h
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc) {
		return FALSE;
	}

	// 'WAVE'�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	HRESULT ret = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	if (mSrcWaveFile.fccType != mmioFOURCC('W', 'A', 'V', 'E')) {
		mmioClose(hSrc, 0);
		return FALSE;
	}

	// 'fmt '�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	if (mSrcWaveFmt.ckid != mmioFOURCC('f', 'm', 't', ' ')) {
		mmioClose(hSrc, 0);
		return FALSE;
	}

	// �w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// �w�b�_�������m��
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	if (!wf) {
		mmioClose(hSrc, 0);
		return FALSE;
	}
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVE�t�H�[�}�b�g�̃��[�h
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);
	if (FAILED(ret)) {
		free(wf);
		mmioClose(hSrc, 0);
		return FALSE;
	}


	// fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// data�`�����N��T��
	while (1) {
		// ����
		ret = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
		if (FAILED(ret)) {
			free(wf);
			mmioClose(hSrc, 0);
			return FALSE;
		}
		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
			break;
		// ���̃`�����N��
		ret = mmioAscend(hSrc, &mSrcWaveData, 0);
	}


	// �T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	ret = m_pDS->CreateSoundBuffer(&dsdesc, dsb, NULL);
	if (FAILED(ret)) {
		free(wf);
		mmioClose(hSrc, 0);
		return FALSE;
	}

	// ���b�N�J�n
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	if (FAILED(ret)) {
		free(wf);
		mmioClose(hSrc, 0);
		return FALSE;
	}

	// �f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ���b�N����
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// �w�b�_�p���������J��
	free(wf);

	// WAV�����
	mmioClose(hSrc, 0);

	return TRUE;
}

LPDIRECTSOUNDBUFFER Sound::SE(int idx) {
	return m_pSecondarySE[idx];
}

LPDIRECTSOUNDBUFFER Sound::BGM(int idx) {
	return m_pSecondaryBGM[idx];
}