#define _CRT_SECURE_NO_WARNINGS
#include "SceneGame.h"
#include "Input.h"
#include "Polygons.h"
#include "Collision.h"
#include "Cat.h"
#include "Utility.h"
#include "Bullet.h"
#include "GameUI.h"
#include <vector>
#include "Sound.h"
#include "Camera.h"

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
	texture.LoadTexture("BackGround.png");
	texture.LoadTexture("runa.png");
	texture.LoadTexture("Floor.png");
	texture.LoadTexture("Cat.png");
	m_cat[0].Initialize(600.0f, 300.0f, 128.0f, 128.0f, 0.0f, 0.0f, 0.25f, 0.25f, ENEMY, LEFT);
	player.Initialize(100.0f, 300.0f, 128.0f, 128.0f, 0.0f, 0.0f, 0.125f, 0.125f, PLAYER, RIGHT);
	m_gameUI.Initialize();
	for (int i = 0; i < BLOCK_NUM - 3; i++) {
		m_scaffold[i].Initialize(100.0f + i * 250.0f, 800.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	}
	/*for (int i = BLOCK_NUM - 5; i < BLOCK_NUM; i++) {
		m_scaffold[i].Initialize(100.0f + i * 250.0f, 650.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	}*/
	m_scaffold[4].Initialize(100.0f + 1 * 250.0f, 550.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[5].Initialize(100.0f + -1 * 250.0f, 736.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[6].Initialize(100.0f + 4 * 250.0f, 736.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_playerHit = true;
	Sound::SE(0)->Stop();
	Sound::BGM(1)->SetCurrentPosition(0);
	Sound::BGM(1)->Play(0, 0, DSBPLAY_LOOPING);
	Camera::Initialize();
}

void SceneGame::Update() {
	UpdatePlayer();
	UpdateEnemy();
	UpdateCollision();
	m_gameUI.Update();
	Camera::Update();
}

void SceneGame::Draw() {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture.SetTexture(0));
	DrawScaffold();
	DrawPlayer();
	DrawEnemy();
	m_gameUI.Draw();
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
	texture.Finalize();
	player.Finalize();
	m_cat[0].Finalize();
	m_gameUI.Fianlize();
}

void SceneGame::UpdatePlayer() {
	player.Update();
}

void SceneGame::UpdateEnemy() {
	m_cat[0].Update();
}

void SceneGame::UpdateCollision() {
	ColPandS();
	ColCandS();
	ColCandA();
	ColPandA();
}

void SceneGame::DrawPlayer() {
	player.Draw(texture.SetTexture(1));
}

void SceneGame::DrawEnemy() {
	m_cat[0].Draw(texture.SetTexture(3));
}

void SceneGame::DrawScaffold() {
	for (int i = 0; i < BLOCK_NUM; i++) {
		m_scaffold[i].Draw(texture.SetTexture(2));
	}
}

void SceneGame::ColPandS() {
	m_playerHit = false;
	MyOutputDebugString("px::%f sx::%f\n", player.GetFirstX(), m_cat[0].GetX());
	for (int i = 0; i < BLOCK_NUM; i++) {
		if (Collision::IsCollisionEnter(player.GetFirstX(), player.GetY(), player.GetW(), player.GetH(), m_scaffold[i].GetX(), m_scaffold[i].GetY(), m_scaffold[i].GetW(), m_scaffold[i].GetH())) {
			DIR dir = Collision::CollisionDirection(player.GetFirstX(), player.GetY(), player.GetW(), player.GetH(), m_scaffold[i].GetX(), m_scaffold[i].GetY(), m_scaffold[i].GetW(), m_scaffold[i].GetH());
			switch (dir) {
			case DOWN:
				player.SetY(m_scaffold[i].GetY() + m_scaffold[i].GetH() + 1.0f);
				m_playerHit = true;
				break;
			case RIGHT:
				player.SetX(RIGHT);
				m_playerHit = true;
				break;
			case LEFT:
				player.SetX(LEFT);
				m_playerHit = true;
				break;
			case UP:
				player.SetY(m_scaffold[i].GetY() - player.GetH() - 1.0f);
				player.Grounded(true);
				m_playerHit = true;
				break;
			default:
				break;
			}
		}

	}
	if (!m_playerHit) {
		player.Grounded(false);
	}
}

void SceneGame::ColCandS() {
	for (int i = 0; i < BLOCK_NUM; i++) {
		if (Collision::IsCollisionEnter(m_cat[0].GetX(), m_cat[0].GetY(), m_cat[0].GetW(), m_cat[0].GetH(), m_scaffold[i].GetX(), m_scaffold[i].GetY(), m_scaffold[i].GetW(), m_scaffold[i].GetH())) {
			DIR dir = Collision::CollisionDirection(m_cat[0].GetX(), m_cat[0].GetY(), m_cat[0].GetW(), m_cat[0].GetH(), m_scaffold[i].GetX(), m_scaffold[i].GetY(), m_scaffold[i].GetW(), m_scaffold[i].GetH());
			if (dir == UP) {
				//m_cat[0].SetY(m_scaffold[i].GetY() + m_scaffold[i].GetH() + 1.0f);
				m_cat[0].SetY(m_scaffold[i].GetY() - m_cat[0].GetH() - 1.0f);
			}
			if (dir == LEFT) {
				m_cat[0].SetDirection(LEFT);
				m_cat[0].SetX(LEFT);
			}
			if (dir == RIGHT) {
				m_cat[0].SetDirection(RIGHT);
				m_cat[0].SetX(RIGHT);
			}
		}

	}
}

void SceneGame::ColCandA() {
	std::vector < Bullet >* bullet = player.GetBullet();
	for (unsigned int i = 0; i < bullet->size(); i++) {
		for (int j = 0; j < CAT_MAX; j++) {
			if (!m_cat[j].GetActive()) {
				continue;
			}
			if (Collision::IsCollisionEnter(m_cat[j].GetX(), m_cat[j].GetY(), m_cat[j].GetW(), m_cat[j].GetH(), (*bullet)[i].GetX(), (*bullet)[i].GetY(), (*bullet)[i].GetW(), (*bullet)[i].GetH())) {
				m_cat[0].Damage(player.GetAtk());
				(*bullet)[i].Finalize();
				(*bullet).erase((*bullet).begin() + i);
			}
		}
	}
}

void SceneGame::ColPandA() {
	std::vector < Bullet >* bullet = m_cat[0].GetBullet();
	for (unsigned int i = 0; i < bullet->size(); i++) {
		for (int j = 0; j < CAT_MAX; j++) {
			if (Collision::IsCollisionEnter(player.GetFirstX(), player.GetY(), player.GetW(), player.GetH(), (*bullet)[i].GetX(), (*bullet)[i].GetY(), (*bullet)[i].GetW(), (*bullet)[i].GetH())) {
				player.Damage(m_cat[0].GetAtk());
				(*bullet)[i].Finalize();
				(*bullet).erase((*bullet).begin() + i);
			}
		}
	}
}

Player* SceneGame::SetPlayer() {
	return &player;
}

Scaffold* SceneGame::SetS() {
	return m_scaffold;
}

Cat* SceneGame::SetCat() {
	return m_cat;
}