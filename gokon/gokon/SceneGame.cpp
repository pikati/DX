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
}

void SceneGame::Update() {
	
}

void SceneGame::Draw() {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, (int)SCENE_GAME);
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