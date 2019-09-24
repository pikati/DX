#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "Input.h"
#include "main.h"
#include "Sound.h"

//BaseScene			SceneManager::*m_scene[2];ただのグローバル変数
BaseScene			*SceneManager::m_scene[2];
SCENE_STATE			SceneManager::m_sceneState;
PDIRECT3DDEVICE9	SceneManager::m_d3dDevice;
const float			SceneManager::MIN_FREAM_TIME = 1.0f / 60;
float				SceneManager::frameTime = 0;
float				SceneManager::fps = 0;
bool				SceneManager::frame = false;
LARGE_INTEGER		SceneManager::timeStart;
LARGE_INTEGER		SceneManager::timeEnd;
LARGE_INTEGER		SceneManager::timeFreq;

void SceneManager::Initialize() {
	m_d3dDevice = GetDevice();
	//各シーンのインスタンス作成
	m_scene[0] = new SceneTitle;
	m_scene[1] = new SceneGame;
	//初期シーン設定
	m_sceneState = SCENE_TITLE;
	//初期シーン初期化
	m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	QueryPerformanceFrequency(&timeFreq);
	// 1度取得しておく(初回計算用)
	QueryPerformanceCounter(&timeStart);
}

void SceneManager::Update() {
	//Input::Update();
	frame = PastOneFrame();
	if (frame)
	{
		if (Input::TriggerKey(DIK_A)) {
			Sound::SE(0)->Play(0, 0, 0);
			SceneManager::ChangeSceneState();
		}
		m_scene[m_sceneState]->Update();
	}
	
}

void SceneManager::Draw() {
	if (frame) {
		m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		GetDevice()->BeginScene();
		m_scene[m_sceneState]->Draw();
		GetDevice()->EndScene();
		m_d3dDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void SceneManager::Finalize() {
	m_scene[1]->Finalize();
	m_scene[0]->Finalize();
	delete m_scene[1];
	delete m_scene[0];
}

void SceneManager::ChangeSceneState() {
	switch (m_sceneState)
	{
	case SCENE_TITLE:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_GAME;
		m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case SCENE_GAME:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_TITLE;
		m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}
}

bool SceneManager::PastOneFrame() {
	QueryPerformanceCounter(&timeEnd);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FREAM_TIME) { // 時間に余裕がある
		// ミリ秒に変換
		DWORD sleepTime = static_cast<DWORD>((MIN_FREAM_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // 分解能を上げる(こうしないとSleepの精度はガタガタ)
		Sleep(sleepTime);   // 寝る
		timeEndPeriod(1);   // 戻す

		// 次週に持ち越し(こうしないとfpsが変になる?)
		return false;
	}

	if (frameTime > 0.0) { // 経過時間が0より大きい(こうしないと下の計算でゼロ除算になると思われ)
		fps = (fps*0.99f) + (0.01f / frameTime); // 平均fpsを計算

	}

	timeStart = timeEnd; // 入れ替え
	return true;
}

BaseScene* SceneManager::SetSceneGame() {
	return m_scene[1];
}