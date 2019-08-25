#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "main.h"

class SceneManager
{
private:
	static BaseScene			*m_scene[2];
	static SCENE_STATE			m_sceneState;
	static LPDIRECT3DDEVICE9	m_d3dDevice;
public:
	static void					Initialize();
	static void					Update();
	static void					Draw();
	static void					Finalize();
	static void					ChangeSceneState();
	static LPDIRECT3DTEXTURE9	GetTexture(int scene);
};

