#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "Input.h"
#include "main.h"

//BaseScene			SceneManager::*m_scene[2];ただのグローバル変数
BaseScene			*SceneManager::m_scene[2];
SCENE_STATE			SceneManager::m_sceneState;
PDIRECT3DDEVICE9	SceneManager::m_d3dDevice;

void SceneManager::Initialize() {
	m_d3dDevice = GetDevice();
	//各シーンのインスタンス作成
	m_scene[0] = new SceneTitle;
	m_scene[1] = new SceneGame;
	//初期シーン設定
	m_sceneState = SCENE_TITLE;
	//初期シーン初期化
	m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f, 1.0f);
}

void SceneManager::Update() {
	if (Input::TriggerKey(DIK_A)) {
		SceneManager::ChangeSceneState();
	}
	m_scene[m_sceneState]->Update();
}

void SceneManager::Draw() {
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	m_scene[m_sceneState]->Draw();
	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void SceneManager::Finalize() {
	delete m_scene[1];
	delete m_scene[0];
}

void SceneManager::ChangeSceneState() {
	switch (m_sceneState)
	{
	case SCENE_TITLE:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_GAME;
		m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 256.0f, 256.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case SCENE_GAME:
		m_scene[m_sceneState]->Finalize();
		m_sceneState = SCENE_TITLE;
		m_scene[m_sceneState]->Initialize(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}
}