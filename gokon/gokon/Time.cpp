#include "Time.h"
#include "Polygons.h"
void Time::Initialize() {
	m_frame = 0;
	m_oneDigit = 0;
	m_tenDigit = 0;
	m_handredDigit = 0;
	m_texture.LoadTexture("Number.png");
	m_texture.LoadTexture("Time.png");
}

void Time::Update() {
	/*if (m_oneDigit == 0 && m_tenDigit == 0 && m_handredDigit == 0) {
		return;
	}*/
	m_frame++;
	if (m_frame >= 60) {
		m_oneDigit++;
		m_frame -= 60;
	}
	if (m_oneDigit >= 10) {
		m_tenDigit++;
		m_oneDigit -= 10;
	}
	if (m_tenDigit >= 10) {
		m_handredDigit++;
		m_tenDigit -= 10;
	}
}

void Time::Draw() {
	Polygons::Draw(1700.0f - 70.0f * 5 - 150.0f, 190.0f, 128.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_texture.SetTexture(1));
	Polygons::Draw(1700.0f - 70.0f * 0, 190.0f, 64.0f, 64.0f, (float)(m_oneDigit % 5) * 0.2f, (float)(m_oneDigit / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
	Polygons::Draw(1700.0f - 70.0f * 1, 190.0f, 64.0f, 64.0f, (float)(m_tenDigit % 5) * 0.2f, (float)(m_tenDigit / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
	Polygons::Draw(1700.0f - 70.0f * 2, 190.0f, 64.0f, 64.0f, (float)(m_handredDigit % 5) * 0.2f, (float)(m_handredDigit / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));

}

void Time::Finalize() {
	m_texture.Finalize();
}
