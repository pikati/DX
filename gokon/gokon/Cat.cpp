#define _CRT_SECURE_NO_WARNINGS
#include "Cat.h"
#include "Polygons.h"
#include "Utility.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "Sound.h"

void Cat::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	m_upPower = 0;
	anim.Initialize(CAT);
	anim.SetSpeed(20);
	m_attribute = attr;
	m_dir = dir;
	m_oldDir = dir;
	m_oldY = m_y;
	m_speed = 3.0f;
	m_enable = true;
	m_frame = 0;
	m_frameEffect = 0;
	m_hpFrame.Initialize(100.0f, 22.0f, 100.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_hpFill.Initialize(100.0f, 22.0f, 100.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.25f, OBJECT, NON);
	m_hpFrame.SetPosition(m_x, m_y - 50.0f);
	m_hpFrame.SetLength(10);
	m_hpFill.SetPosition(m_x, m_y - 50.0f);
	m_hpFill.SetLength(10);
	m_firstX = m_x;
	m_aria = false;
	m_move = true;
	InitStatus();
	m_texture.LoadTexture("DarkStar.png");
	m_texture.LoadTexture("Gauge.png");
	m_texture.LoadTexture("GaugeFill.png");
	m_texture.LoadTexture("Effect.png");
}

void Cat::Update() {
	CheckAria();
	if (!m_enable) {
		return;
	}
	if (!m_aria) {
		return;
	}
	anim.Update();
	Move();
	Gravity();
	if (CheckHP()) {
		m_frameEffect++;
		if (m_frameEffect >= 20) {
			Destroy();
		}
	}
	FLOAT2 uv = anim.SetTexturePosition();
	m_u = uv.x;
	m_v = uv.y;
	TextureInverse();
	Attack();
	for (unsigned int i = 0; i < m_bullet.size(); i++) {
		m_bullet[i].Update();
	}
	m_hpFrame.SetValue(m_mhp);
	m_hpFrame.SetPosition(m_x, m_y - 50.0f);
	m_hpFrame.Update();
	m_hpFill.SetValue(m_mhp, m_hp);
	m_hpFill.SetPosition(m_x, m_y - 50.0f);
	m_hpFill.Update();
	CheckBullet();
}

void Cat::Draw(LPDIRECT3DTEXTURE9 texture) {
	if (!m_enable) {
		return;
	}
	if (!m_aria) {
		return;
	}
	if (m_frameEffect != 0) {
		if (m_frameEffect < 5) {
			m_u = 0.0f;
			m_v = 0.0f;
		}
		else if (m_frameEffect < 10) {
			m_u = 0.5f;
			m_v = 0.0f;
		}
		else if (m_frameEffect < 15) {
			m_u = 0.0f;
			m_v = 0.5f;
		}
		else if (m_frameEffect <= 20) {
			m_u = 0.5f;
			m_v = 0.5f;
		}
		Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, 0.5f, 0.5f, m_texture.SetTexture(3));
	}
	else {
		Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture);
	}
	for (unsigned int i = 0; i < m_bullet.size(); i++) {
		m_bullet[i].Draw(m_texture.SetTexture(0));
	}
	m_hpFill.Draw(m_texture.SetTexture(2));
	m_hpFrame.Draw(m_texture.SetTexture(1));
}

void Cat::Finalize() {
	m_texture.Finalize();
	m_x = 10000.0f;
}

void Cat::TextureInverse() {
	if (m_dir == RIGHT) {
		m_u += 0.25;
		m_tw = -0.25f;
	}
	else {
		m_tw = 0.25f;
	}
}

float Cat::GetX() {
	return m_x;
}

float Cat::GetY() {
	return m_y;
}

float Cat::GetW() {
	return m_w;
}

float Cat::GetH() {
	return m_h;
}

void Cat::SetX(float x) {
	m_x = x;
}

void Cat::Sety(float y) {
	m_y = y;
}

void Cat::SetW(float w) {
	m_w = w;
}

void Cat::SetH(float h) {
	m_h = h;
}

void Cat::SetY(float y) {
	m_y = y;
	m_oldY = y;
}

void Cat::SetX(DIR dir) {
	if (dir == LEFT) {
		m_x += -m_speed;
	}
	else if (dir == RIGHT) {
		m_x += m_speed;
	}
}

void Cat::Attack() {
	Player* player = ObjectManager::SetPlayer();
	if (m_frame == 0) {
		if (m_y < player->GetY() + player->GetH() && m_y + m_h> player->GetY()) {
			m_frame++;
			anim.SetState(CAT_ATTACK);
			anim.SetLoop(false);
		}
	}
	if (m_frame != 0) {
		m_frame++;
	}
	if (m_frame == 20) {
		m_bullet.push_back(Bullet(m_x, m_y + 32.0f, 64.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, ENEMY, m_dir));
		
	}
	if (m_frame > 40) {
		m_frame = 0;
		anim.SetState(CAT_MOVE);
		anim.SetLoop(true);
	}
	
}
	
void Cat::Gravity() {
	float tmp = m_y;
	m_y += (m_y - m_oldY) + m_upPower;
	m_oldY = tmp;
	m_upPower = 0.5f;
}

void Cat::Destroy() {
	m_enable = false;
	Finalize();
}

bool Cat::CheckHP() {
	if (m_hp <= 0) {
		return true;
	}
	return false;
}

void Cat::Damage(int damage) {
	Sound::SE(2)->SetCurrentPosition(0);
	Sound::SE(2)->Play(0, 0, 0);
	m_hp -= damage;
}

void Cat::Move() {
	if (!m_move) {
		return;
	}
	switch (m_dir)
	{
	case LEFT:
		m_firstX += -m_speed;
		break;
	case RIGHT:
		m_firstX += m_speed;
		break;
	default:
		break;
	}
}

void Cat::SetDirection(DIR dir) {
	m_dir = dir;
}

std::vector<Bullet>* Cat::GetBullet() {
	return &m_bullet;
}

int Cat::GetAtk() {
	return m_atk;
}

bool Cat::GetActive() {
	return m_enable;
}

float Cat::GetFirstX() {
	return m_firstX;
}

void Cat::CheckBullet() {
	for (unsigned int i = 0; i < m_bullet.size(); i++) {
		if (m_bullet[i].GetX() < -100.0f || m_bullet[i].GetX() > 2000.0f) {
			m_bullet.erase(m_bullet.begin() + i);
		}
	}
}

void Cat::CheckAria() {
	if (m_x > -500.0f && m_x < 2400.0f) {
		m_aria = true;
	}
	else {
		m_aria = false;
	}
}

void Cat::SetMove(bool move) {
	m_move = move;
}

int Cat::GetEXP() {
	return m_exp;
}

void Cat::InitStatus() {
	if (m_x < 7680) {
		m_hp = m_mhp = 3;
		m_atk = 10;
		m_exp = 300;
	}
	else if (m_x < 12000) {
		m_hp = m_mhp = 5;
		m_atk = 10;
		m_exp = 600;
	}
	else if (m_x < 15800) {
		m_hp = m_mhp = 7;
		m_atk = 15;
		m_exp = 2000;
	}
	else if (m_x < 19200) {
		m_hp = m_mhp = 10;
		m_atk = 5;
		m_exp = 2500;
	}
	else {
		m_hp = m_mhp = 100;
		m_atk = 2;
		m_exp = 10000;
	}
}