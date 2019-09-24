#include "LevelUp.h"
#include "Polygons.h"
#include "Sound.h"
void LevelUp::Initialize() {
	m_hpl = 1;
	m_mpl = 1;
	m_atkl = 1;
	m_heal = 1;

	m_hpexp[0] = 50;
	for (int i = 1; i < MAX_LV - 1; i++) {
		m_hpexp[i] = m_hpexp[i-1] + 50 * i;
	}

	m_mpexp[0] = 100;
	for (int i = 1; i < MAX_LV - 1; i++) {
		m_mpexp[i] = m_mpexp[i - 1] + 75 * i;
	}

	m_atkexp[0] = 50;
	for (int i = 1; i < MAX_LV - 1; i++) {
		m_atkexp[i] = m_atkexp[i - 1] + 100 * i;
	}

	m_healexp[0] = 200;
	for (int i = 1; i < MAX_LV - 1; i++) {
		m_healexp[i] = m_healexp[i - 1] + 150 * i;
	}
	m_hpexp[8] = m_mpexp[8] = m_atkexp[8] = m_healexp[8] = 0;
	m_texture.LoadTexture("Number.png");
	m_texture.LoadTexture("HP.png");
	m_texture.LoadTexture("MP.png");
	m_texture.LoadTexture("ATK.png");
	m_texture.LoadTexture("Heal.png");
}

void LevelUp::Update() {

}

void LevelUp::Draw() {
	Polygons::Draw(120.0f, 950.0f, 256.0f, 128.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_texture.SetTexture(1));
	Polygons::Draw(600.0f, 950.0f, 256.0f, 128.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_texture.SetTexture(2));
	Polygons::Draw(1080.0f, 950.0f, 256.0f, 128.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_texture.SetTexture(3));
	Polygons::Draw(1560.0f, 950.0f, 256.0f, 128.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_texture.SetTexture(4));
	Polygons::Draw(120.0 + 150.0f, 957.0f, 40.0f, 40.0f, (float)(m_hpl % 5) * 0.2f, (float)(m_hpl / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
	Polygons::Draw(600.0f + 150.0f, 957.0f, 40.0f, 40.0f, (float)(m_mpl % 5) * 0.2f, (float)(m_mpl / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
	Polygons::Draw(1110.0f + 150.0f, 957.0f, 40.0f, 40.0f, (float)(m_atkl % 5) * 0.2f, (float)(m_atkl / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
	Polygons::Draw(1610.0f + 150.0f, 957.0f, 40.0f, 40.0f, (float)(m_heal % 5) * 0.2f, (float)(m_heal / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
	DrawEXP(m_hpexp[m_hpl - 1], 120.0 + 235.0f);
	DrawEXP(m_mpexp[m_mpl - 1], 600.0f + 235.0f);
	DrawEXP(m_atkexp[m_atkl - 1], 1080.0f + 235.0f);
	DrawEXP(m_healexp[m_heal - 1], 1560.0f + 235.0f);
}

void LevelUp::Finalize() {
	m_texture.Finalize();
}

void LevelUp::UpHP(int *exp) {
	if (m_hpl == 9) {
		Sound::SE(4)->Stop();
		Sound::SE(3)->SetCurrentPosition(0);
		Sound::SE(3)->Play(0, 0, 0);
		return;
	}
	if (m_hpexp[m_hpl - 1] <= *exp) {
		Sound::SE(3)->Stop();
		Sound::SE(4)->SetCurrentPosition(0);
		Sound::SE(4)->Play(0, 0, 0);
		*exp -= m_hpexp[m_hpl - 1];
		m_hpl++;
		return;
	}
	Sound::SE(4)->Stop();
	Sound::SE(3)->SetCurrentPosition(0);
	Sound::SE(3)->Play(0, 0, 0);
}

void LevelUp::UpMP(int *exp) {
	if (m_mpl == 9) {
		Sound::SE(4)->Stop();
		Sound::SE(3)->SetCurrentPosition(0);
		Sound::SE(3)->Play(0, 0, 0);
		return;
	}
	if (m_mpexp[m_mpl - 1] <= *exp) {
		Sound::SE(3)->Stop();
		Sound::SE(4)->SetCurrentPosition(0);
		Sound::SE(4)->Play(0, 0, 0);
		*exp -= m_mpexp[m_mpl - 1];
		m_mpl++;
		return;
	}
	Sound::SE(4)->Stop();
	Sound::SE(3)->SetCurrentPosition(0);
	Sound::SE(3)->Play(0, 0, 0);
}

void LevelUp::UpATK(int *exp) {
	if (m_atkl == 9) {
		Sound::SE(4)->Stop();
		Sound::SE(3)->SetCurrentPosition(0);
		Sound::SE(3)->Play(0, 0, 0);
		return;
	}
	if (m_atkexp[m_atkl - 1] <= *exp) {
		Sound::SE(3)->Stop();
		Sound::SE(4)->SetCurrentPosition(0);
		Sound::SE(4)->Play(0, 0, 0);
		*exp -= m_atkexp[m_atkl - 1];
		m_atkl++;
		return;
	}
	Sound::SE(4)->Stop();
	Sound::SE(3)->SetCurrentPosition(0);
	Sound::SE(3)->Play(0, 0, 0);
}

void LevelUp::UpHeal(int *exp) {
	if (m_heal == 9) {
		Sound::SE(4)->Stop();
		Sound::SE(3)->SetCurrentPosition(0);
		Sound::SE(3)->Play(0, 0, 0);
		return;
	}
	if (m_healexp[m_heal - 1] <= *exp) {
		Sound::SE(3)->Stop();
		Sound::SE(4)->SetCurrentPosition(0);
		Sound::SE(4)->Play(0, 0, 0);
		*exp -= m_healexp[m_heal - 1];
		m_heal++;
		return;
	}
	Sound::SE(4)->Stop();
	Sound::SE(3)->SetCurrentPosition(0);
	Sound::SE(3)->Play(0, 0, 0);
}

int LevelUp::GetHPLV() {
	return m_hpl;
}

int LevelUp::GetMPLV() {
	return m_mpl;
}

int LevelUp::GetATKLV() {
	return m_atkl;
}

int LevelUp::GetHealLV() {
	return m_heal;
}

void LevelUp::DrawEXP(int exp, float x) {
	int i = 0;
	for (; i < 5; i++) {
		int num = exp % 10;
		if (exp == 0) {
			Polygons::Draw(x, 1025.0f, 40.0f, 40.0f, 0.0f, 0.0f, 0.2f, 0.5f, m_texture.SetTexture(0));
		}
		else {
			Polygons::Draw(x - 40.0f * i, 1025.0f, 40.0f, 40.0f, (float)(num % 5) * 0.2f, (float)(num / 5) * 0.5f, 0.2f, 0.5f, m_texture.SetTexture(0));
		}
		exp /= 10;
	}
}