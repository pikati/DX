#include "SceneTitle.h"
#include "Input.h"
#include "SceneManager.h"
#include "Polygons.h"

SceneTitle::~SceneTitle() {
}

void SceneTitle::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	texture.SetTexture("background.bmp");
}

void SceneTitle::Update() {
	
}

void SceneTitle::Draw() {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture.GetTexture());
}

void SceneTitle::Finalize() {
	m_x = 0;
	m_y = 0;
	m_w = 0;
	m_h = 0;
	m_u = 0;
	m_v = 0;
	m_tw = 0;
	m_th = 0;
}