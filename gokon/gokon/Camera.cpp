#include "Camera.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Scaffold.h"
#include "Cat.h"
#include "SceneGame.h"

float Camera::m_moveX;
float Camera::m_moveY;

void Camera::Initialize() {
	m_moveX = 0;
	m_moveY = 0;
}

void Camera::Update() {
	Player* player = ObjectManager::SetPlayer();
	Scaffold* s = ObjectManager::SetFloor();
	Cat* cat = ObjectManager::SetCat();
	for (int i = 0; i < BLOCK_NUM; i++) {
		(s + i)->SetX(-(player->GetX()) -100.0f + (s + i)->GetFirstX());
	}
	for (int i = 0; i < CAT_MAX; i++) {
		(cat + i)->SetX(-(player->GetX()) - 100.0f + (cat + i)->GetFirstX());
	}
}

void Camera::GetDiff(float x, float y) {
	m_moveX += x;
	m_moveY += y;
}