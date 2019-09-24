#include "Score.h"
#include "Polygons.h"

void Score::Initialize(bool score, float y) {
	m_score = 0;
	m_texture.LoadTexture("Number.png");
	m_s = score;
	if (m_s) {
		m_texture.LoadTexture("Score.png");
	}
	else {
		m_texture.LoadTexture("EXP.png");
	}
	m_y = y;
}

void Score::Update() {
	
}

void Score::Draw() {
	int tmp = m_score;
	int i = 0;
	for (; i < 5; i++) {
		int num = tmp % 10;
		if (tmp == 0) {
			Polygons::Draw(1700.0f, m_y, 64.0f, 64.0f, 0.0f, 0.0f, 0.2f, 0.5f, m_texture.SetTexture(0));
		}
		else {
			Polygons::Draw(1700.0f - 70.0f * i, m_y, 64.0f, 64.0f, (float)(num % 5) * 0.2f, (float)(num / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
		}
		if (tmp == 0) {
			break;
		}
		tmp /= 10;
	}
	Polygons::Draw(1700.0f - 70.0f * 5 - 150.0f, m_y, 128.0f, 60, 0.0f, 0.0f, 1.0f, 1.0f, m_texture.SetTexture(1));
}

void Score::Finalize() {
	m_texture.Finalize();
}

void Score::AddScore(int score) {
	m_score += score;
}

int Score::GetScore() {
	return m_score;
}

void Score::SetScore(int value) {
	m_score = value;
}