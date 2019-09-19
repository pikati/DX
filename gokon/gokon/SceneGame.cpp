#include "SceneGame.h"
#include "Input.h"
#include "SceneManager.h"
#include "Polygons.h"

SceneGame::~SceneGame() {
}

void SceneGame::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	texture.SetTexture("1-background.png");
	texture.SetTexture("runa.png");
	player.Initialize(100.0f, 300.0f, 128.0f, 128.0f, 0.0f, 0.0f, 0.125f, 0.125f);
}

void SceneGame::Update() {
	player.Update();
}

void SceneGame::Draw() {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture.GetTexture(0));
	player.Draw(texture.GetTexture(1));
}

void SceneGame::Finalize() {
	m_x = 0;
	m_y = 0;
	m_w = 0;
	m_h = 0;
	m_u = 0;
	m_v = 0;
	m_tw = 0;
	m_th = 0;
}