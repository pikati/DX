#include "SceneGame.h"
#include "Input.h"
#include "SceneManager.h"
#include "Polygons.h"
#include "Collision.h"
#include "Utility.h"

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
	texture.LoadTexture("1-background.png");
	texture.LoadTexture("runa.png");
	texture.LoadTexture("1-floor.png");
	player.Initialize(100.0f, 300.0f, 128.0f, 128.0f, 0.0f, 0.0f, 0.125f, 0.125f);
	for (int i = 0; i < BLOCK_NUM - 1; i++) {
		m_scaffold[i].Initialize(100.0f + i * 250.0f, 800.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	/*for (int i = BLOCK_NUM - 5; i < BLOCK_NUM; i++) {
		m_scaffold[i].Initialize(100.0f + i * 250.0f, 650.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	}*/
	m_scaffold[4].Initialize(100.0f + 1 * 250.0f, 550.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	m_playerHit = true;
}

void SceneGame::Update() {
	UpdatePlayer();
}

void SceneGame::Draw() {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture.SetTexture(0));
	DrawScaffold();
	DrawPlayer();
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
}

void SceneGame::UpdatePlayer() {
	player.Update();
	m_playerHit = false;
	for (int i = 0; i < BLOCK_NUM; i++) {
		if (Collision::IsCollisionEnter(player.GetX(), player.GetY(), player.GetW(), player.GetH(), m_scaffold[i].GetX(), m_scaffold[i].GetY(), m_scaffold[i].GetW(), m_scaffold[i].GetH())) {
			DIR dir = Collision::CollisionDirection(player.GetX(), player.GetY(), player.GetW(), player.GetH(), m_scaffold[i].GetX(), m_scaffold[i].GetY(), m_scaffold[i].GetW(), m_scaffold[i].GetH());
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
	if(!m_playerHit) {
		player.Grounded(false);
	}
}

void SceneGame::DrawPlayer() {
	player.Draw(texture.SetTexture(1));
}

void SceneGame::DrawScaffold() {
	for (int i = 0; i < BLOCK_NUM; i++) {
		m_scaffold[i].Draw(texture.SetTexture(2));
	}
}