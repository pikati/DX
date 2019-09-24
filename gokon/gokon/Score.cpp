#include "Score.h"
#include "Polygons.h"

int Score::m_score = 0;
Texture Score::m_texture;

void Score::Initialize() {
	m_score = 0;
	m_texture.LoadTexture("number.png");
}

void Score::Update() {
	
}

void Score::Draw() {
	int tmp = m_score;
	for (int i = 0; i < 5; i++) {
		int num = tmp % 10;
		if (tmp == 0) {
			Polygons::Draw(1700.0f, 100.0f, 128.0f, 128.0f, 0.0f, 0.0f, 0.2f, 0.5f, m_texture.SetTexture(0));
		}
		else {
			Polygons::Draw(1700.0f - 135.0f * i, 100.0f, 128.0f, 128.0f, (float)(num % 5) * 0.2f, (float)(num / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
		}
		tmp /= 10;
	}
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