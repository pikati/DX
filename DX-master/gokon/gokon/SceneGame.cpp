#include "SceneGame.h"
#include "Input.h"
#include "SceneManager.h"
#include "Polygons.h"

SceneGame::~SceneGame() {
}

void SceneGame::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) {
	m_back.SetPosition(x, y, w, h, u, v, tw, th);
	texture.SetTexture("1-background.png");
	player.Initialize(100.0f, 800.0f, 256.0f, 256.0f, 0.0f, 0.0f, 0.125f, 0.125f);
}

void SceneGame::Update() {
	player.Update();
}

void SceneGame::Draw() {
	m_back.Draw(texture.GetTexture());
	player.Draw();
}

void SceneGame::Finalize() {
	player.Finalize();
}