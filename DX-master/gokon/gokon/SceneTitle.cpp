#include "SceneTitle.h"
#include "Input.h"
#include "SceneManager.h"
#include "Polygons.h"

SceneTitle::~SceneTitle() {
}

void SceneTitle::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) {
	m_back.SetPosition(x, y, w, h, u, v, tw, th);
	texture.SetTexture("1-floor.png");
}

void SceneTitle::Update() {
	
}

void SceneTitle::Draw() {
	m_back.Draw(texture.GetTexture());
}

void SceneTitle::Finalize() {
}