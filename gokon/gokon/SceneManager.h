#pragma once
#include "BaseScene.h"
#include "main.h"

enum SCENE_STATE {
	SCENE_TITLE,
	SCENE_GAME
};

class SceneManager
{
private:
	static BaseScene			*m_scene[2];
	static SCENE_STATE			m_sceneState;
	static LPDIRECT3DTEXTURE9	m_sceneTexture[2];
public:
	static void Initialize();
	static void Update();
	static void Draw();
	static void Finalize();
	static void ChangeSceneState();
};

