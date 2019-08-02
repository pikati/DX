#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "Input.h"
#include "main.h"

//BaseScene			SceneManager::*m_scene[2];ただのグローバル変数
BaseScene			*SceneManager::m_scene[2];
SCENE_STATE			SceneManager::m_sceneState;
LPDIRECT3DTEXTURE9	SceneManager::m_sceneTexture[2];

void SceneManager::Initialize() {
	LPDIRECT3DDEVICE9 d3dDevice = GetDevice();
	//各シーンのインスタンス作成
	m_scene[0] = new SceneTitle;
	m_scene[1] = new SceneGame;
	//画像取得
	D3DXCreateTextureFromFile(d3dDevice, "BackGround.bmp", &m_sceneTexture[0]);
	D3DXCreateTextureFromFile(d3dDevice, "test.bmp", &m_sceneTexture[1]);
	//初期シーン設定
	m_sceneState = SCENE_TITLE;
	//初期シーン初期化
	m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_sceneTexture[SCENE_TITLE]);
}

void SceneManager::Update() {
	if (Input::TriggerKey(DIK_A)) {
		SceneManager::ChangeSceneState();
	}
	m_scene[m_sceneState]->Update();
}

void SceneManager::Draw() {
	LPDIRECT3DDEVICE9 d3dDevice = GetDevice();
	m_scene[m_sceneState]->Draw();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void SceneManager::Finalize() {
	SAFE_RELEASE(m_sceneTexture[1]);
	SAFE_RELEASE(m_sceneTexture[0]);
	delete m_scene[1];
	delete m_scene[0];
}

void SceneManager::ChangeSceneState() {
	switch (m_sceneState)
	{
	case SCENE_TITLE:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_GAME;
		m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_sceneTexture[SCENE_GAME]);
		break;
	case SCENE_GAME:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_TITLE;
		m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_sceneTexture[SCENE_TITLE]);
		break;
	default:
		break;
	}
}