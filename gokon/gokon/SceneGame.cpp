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
#include "Score.h"
#include "SceneManager.h"

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
	texture.LoadTexture("Moon.png");
	texture.LoadTexture("Clear.png");
	m_score = 0;
	m_end = false;
	player.Initialize(120.0f, 228.0f, 128.0f, 128.0f, 0.0f, 0.0f, 0.125f, 0.125f, PLAYER, RIGHT);
	m_gameUI.Initialize();
	InitilizeScaffold();
	InitializeCat();

	m_playerHit = true;
	Sound::SE(0)->Stop();
	Sound::BGM(1)->SetCurrentPosition(0);
	Sound::BGM(1)->Play(0, 0, DSBPLAY_LOOPING);
	Camera::Initialize();
	m_scor.Initialize(true, 50.0f);
	m_exp.Initialize(false, 120.0f);
	m_time.Initialize();
}

void SceneGame::Update() {
	if (player.GetY() > 1200.0f && m_end == false) {
		m_end = true;
	}
	if (m_end) {
		if (Input::GetKey(DIK_A)) {
			SceneManager::ChangeSceneState();
		}
		return;
	}
	UpdatePlayer();
	UpdateEnemy();
	UpdateScaffold();
	UpdateCollision();
	m_gameUI.Update();
	Camera::Update();
	m_time.Update();
}

void SceneGame::Draw() {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture.SetTexture(0));
	DrawScaffold();
	DrawPlayer();
	DrawEnemy();
	m_gameUI.Draw();
	m_scor.SetScore(m_score);
	m_scor.Draw();
	m_exp.SetScore(player.SetEXP());
	m_exp.Draw();
	m_time.Draw();
	if (m_end) {
		m_scaffold[BLOCK_NUM - 1].Draw(texture.SetTexture(5));
	}
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
	m_time.Finalize();
	m_scor.Finalize();
	m_exp.Finalize();
	texture.Finalize();
	player.Finalize();
	for (int i = 0; i < CAT_MAX; i++) {
		m_cat[i].Finalize();
	}
	m_gameUI.Fianlize();
}

void SceneGame::UpdatePlayer() {
	player.Update();
}

void SceneGame::UpdateEnemy() {
	for (int i = 0; i < CAT_MAX; i++) {
		m_cat[i].Update();
	}
}

void SceneGame::UpdateScaffold() {
	for (int i = 0; i < BLOCK_NUM - 1; i++) {
		m_scaffold[i].Update();
	}
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
	for (int i = 0; i < CAT_MAX; i++) {
		m_cat[i].Draw(texture.SetTexture(3));
	}
}

void SceneGame::DrawScaffold() {
	for (int i = 0; i < BLOCK_NUM - 2; i++) {
		m_scaffold[i].Draw(texture.SetTexture(2));
	}
	m_scaffold[BLOCK_NUM - 2].Draw(texture.SetTexture(4));
}

void SceneGame::ColPandS() {
	m_playerHit = false;
	for (int i = 0; i < BLOCK_NUM - 1; i++) {
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
	for (int i = 0; i < BLOCK_NUM - 1; i++) {
		for (int j = 0; j < CAT_MAX; j++) {
			if (Collision::IsCollisionEnter(m_cat[j].GetX(), m_cat[j].GetY(), m_cat[j].GetW(), m_cat[j].GetH(), m_scaffold[i].GetX(), m_scaffold[i].GetY(), m_scaffold[i].GetW(), m_scaffold[i].GetH())) {
				DIR dir = Collision::CollisionDirection(m_cat[j].GetX(), m_cat[j].GetY(), m_cat[j].GetW(), m_cat[j].GetH(), m_scaffold[i].GetX(), m_scaffold[i].GetY(), m_scaffold[i].GetW(), m_scaffold[i].GetH());
				if (dir == UP) {
					m_cat[j].SetY(m_scaffold[i].GetY() - m_cat[j].GetH() - 1.0f);
				}
				if (dir == LEFT) {
					m_cat[j].SetDirection(LEFT);
					m_cat[j].SetX(LEFT);
				}
				if (dir == RIGHT) {
					m_cat[j].SetDirection(RIGHT);
					m_cat[j].SetX(RIGHT);
				}
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
				m_cat[j].Damage(player.GetAtk());
				if (m_cat[j].CheckHP()) {
					player.GetEXP(m_cat[j].GetEXP());
					player.Heal(10);
					m_score += 100;
				}
				(*bullet)[i].Finalize();
				(*bullet).erase((*bullet).begin() + i);
				return;
			}
		}
	}
}

void SceneGame::ColPandA() {
	for (int k = 0; k < CAT_MAX; k++) {
		std::vector < Bullet >* bullet = m_cat[k].GetBullet();
		for (unsigned int i = 0; i < bullet->size(); i++) {
			if (Collision::IsCollisionEnter(player.GetFirstX(), player.GetY(), player.GetW(), player.GetH(), (*bullet)[i].GetX(), (*bullet)[i].GetY(), (*bullet)[i].GetW(), (*bullet)[i].GetH())) {
				player.Damage(m_cat[k].GetAtk());
				(*bullet)[i].Finalize();
				(*bullet).erase((*bullet).begin() + i);
				return;
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

void SceneGame::InitilizeScaffold() {
	int i = 0;
	int x = 0;
	int y = 0;
	for (; i < 4; i++) {
		m_scaffold[i].Initialize(100.0f, 800.0f - (i + 1) * 64.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	}
	for (; i < 9; i++) {
		m_scaffold[i].Initialize(100.0f + (i - 4) * 256.0f, 800.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	}
	m_scaffold[9].Initialize (100.0f + 5 * 256.0f, 800.0f - 64.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[10].Initialize(100.0f + 6 * 256.0f, 800.0f - 64.0f * 2, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[11].Initialize(100.0f + 7 * 256.0f, 800.0f - 64.0f * 3, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[12].Initialize(100.0f + 8 * 256.0f, 800.0f - 64.0f * 3, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[13].Initialize(100.0f + 9 * 256.0f, 800.0f - 64.0f * 2, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[14].Initialize(100.0f + 10 * 256.0f, 800.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[15].Initialize(100.0f + 11 * 256.0f, 800.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[16].Initialize(100.0f + 12 * 256.0f, 800.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[17].Initialize(100.0f + 13 * 256.0f, 800.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[18].Initialize(100.0f + 14 * 256.0f, 800.0f - 64.0f * 1, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[19].Initialize(100.0f + 15 * 256.0f, 800.0f - 64.0f * 1, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[20].Initialize(100.0f + 16 * 256.0f, 800.0f - 64.0f * 1, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	x = 17;
	for (i = 21; i < 59; i++) {
		if (i == 21 || i == 33 || i == 45 || i == 50 || i == 52 || i == 54 || i == 56) {
			y = 0;
		}
		else if (i == 27 || i == 47) {
			y = 1;
		}
		else if (i == 25 || i == 31 || i == 37 || i == 48) {
			y = 2;
		}
		else if (i == 49 || i == 51 || i == 53 || i == 55) {
			y = 3;
		}
		m_scaffold[i].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * y, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	}
	y = 1;
	for (; i < 62; i++) {
		m_scaffold[i].Initialize(100.0f + 256.0f * x, 800.0f - 64.0f * y++, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	}
	y = 0;
	x++;
	for (; i < 78; i++) {
		m_scaffold[i].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * y, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	}
	m_scaffold[i++].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * 1, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * x, 800.0f - 64.0f * 2, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * 0, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * 1, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * x, 800.0f - 64.0f * 2, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * 0, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * 1, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);

	m_scaffold[i++].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * 0, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * 0, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * (x+2), 800.0f - 64.0f * 1, 256.0f, 256.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_scaffold[i++].Initialize(100.0f + 256.0f * x++, 800.0f - 64.0f * 3, 256.0f, 128.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);

}

void SceneGame::InitializeCat() {
	int i = 0;
	int x = 0;
	int y = 0;
	for (; i < CAT_MAX; i++) {
		if (i == 0 || i == 9 || i == 11 || i == 13) {
			y = 5;
		}
		else if (i >= 4 && i <= 6 || i == 25 || i == 28) {
			y = 4;
		}
		else if (i == 3 || i == 24 || i == 27 || i == 30) {
			y = 3;
		}
		else if (i == 1 || i == 2 || i == 8 || i == 10 || i == 12 || i >= 15 && i <= 23 || i == 26 || i == 27) {
			y = 2;
		}

		if (i == 0) {
			x = 6;
		}
		else if (i == 1) {
			x = 11;
		}
		else if (i == 2) {
			x = 17;
		}
		else if (i == 3) {
			x = 23;
		}
		else if (i == 4) {
			x = 32;
		}
		else if (i == 5) {
			x = 34;
		}
		else if (i == 6) {
			x = 36;
		}
		else if (i == 7) {
			x = 39;
		}
		else if (i == 8) {
			x = 46;
		}
		else if (i == 9 || i == 10 || i == 11 || i == 12 || i == 13) {
			x++;
		}
		else if (i == 14) {
			x = 54;
		}
		else if (i == 15) {
			x = 55;
		}
		else if (i == 16) {
			x = 57;
		}
		else if (i >= 17 && i <= 23) {
			x++;
		}
		else if (i == 24) {
			x = 71;
		}
		else if (i == 25, i == 26) {
			x = 72;
		}
		else if (i == 27) {
			x = 73;
		}
		else if (i == 28 || i == 29) {
			x = 74;
		}
		else if (i == 30) {
			x = 75;
		}
		m_cat[i].Initialize(400.0f + 256.0f * x, 800.0f - 64 * y, 128.0f, 128.0f, 0.0f, 0.0f, 0.25f, 0.25f, ENEMY, LEFT);
		if (i == 0 || i >= 4 && i <= 7 || i == 9 || i == 11 || i == 13 || i == 14 || i == 15 || i == 18 || i == 21 || i >= 24 && i <= 30) {
			m_cat[i].SetMove(false);
		}
	}
	
}