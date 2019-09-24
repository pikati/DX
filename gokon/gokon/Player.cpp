#define _CRT_SECURE_NO_WARNINGS
#include "Player.h"
#include "Input.h"
#include "main.h"
#include "Polygons.h"
#include "Utility.h"
#include "Sound.h"
#include "Camera.h"
#include "Score.h"
#include "SceneManager.h"

/*着地したときにキー入力しっぱだとアニメーションが変更されない そんなの知るか*/

void Player::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	anim.Initialize(RUNA);
	m_attribute = attr;
	m_dir = dir;
	m_oldDir = dir;
	m_oldY = m_y;
	m_isGround = false;
	m_upPower = 0;
	m_speed = 5.0f;
	m_enable = true;
	m_mhp = m_hp = 100;
	m_mmp = m_mp = 100;
	m_atk = 1;
	m_move = m_x;
	m_exp = 0;
	m_healSpeed = 1.0f;
	m_texture.LoadTexture("Star.png");
	m_l.Initialize();
	InitializeHP();
	InitializeMP();
	InitializeATK();
	InitializeHeal();
}

void Player::Update() {
	if (!m_enable) {
		if (Input::GetKey(DIK_A)) {
			SceneManager::ChangeSceneState();
		}
		return;
	}
	if (Input::TriggerKey(DIK_RIGHT) || Input::TriggerKey(DIK_LEFT)) {
		anim.SetState(RUNA_MOVE);
		anim.SetSpeed(5);
		anim.SetLoop(true);
	}
	if (Input::ReleaseKey(DIK_RIGHT) || Input::ReleaseKey(DIK_LEFT)) {
		anim.SetState(RUNA_IDOL);
		anim.SetSpeed(10);
		anim.SetLoop(true);
	}
	if (Input::GetKey(DIK_RIGHT)) {
		//Camera::GetDiff(m_speed, 0);
		m_move += m_speed;
		m_dir = RIGHT;
	}
	if (Input::GetKey(DIK_LEFT)) {
		//Camera::GetDiff(-m_speed, 0);
		m_move += -m_speed;
		m_dir = LEFT;
	}
	if (Input::GetKey(DIK_Q)) {
		anim.SetState(RUNA_IDOL);
	}
	if (Input::GetKey(DIK_SPACE)) {
		anim.SetState(RUNA_JUMP);
		anim.SetSpeed(10);
		anim.SetLoop(true);
		Jump();
	}
	if (Input::TriggerKey(DIK_Z)) {
		Attack();
	}
	if (Input::GetKey(DIK_T)) {
		anim.SetState(RUNA_DAMAGE);
		anim.SetSpeed(10);
		anim.SetLoop(true);
	}

	if (Input::TriggerKey(DIK_1)) {
		m_l.UpHP(&m_exp);
		SetHP();
	}
	if (Input::TriggerKey(DIK_2)) {
		m_l.UpMP(&m_exp);
		SetMP();
	}
	if (Input::TriggerKey(DIK_3)) {
		m_l.UpATK(&m_exp);
		SetATK();
	}
	if (Input::TriggerKey(DIK_4)) {
		m_l.UpHeal(&m_exp);
		SetHeal();
	}
	HealMP();
	UpdateJump();
	anim.Update();
	FLOAT2 uv = anim.SetTexturePosition();
	m_u = uv.x;
	m_v = uv.y;
	TextureInverse();
	/*当たり判定とかいろいろ処理*/
	m_oldDir = m_dir;
	for (unsigned int i = 0; i < m_bullet.size(); i++) {
		m_bullet[i].Update();
	}
	CheckHP();
	CheckBullet();
}

void Player::Draw(LPDIRECT3DTEXTURE9 texture) {
	if (!m_enable) {
		return;
	}
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture);
	for (unsigned int i = 0; i < m_bullet.size(); i++) {
		m_bullet[i].Draw(m_texture.SetTexture(0));
	}
	m_l.Draw();
}

void Player::Finalize() {
	m_enable = false;
	m_texture.Finalize();
	Sound::BGM(1)->Stop();
}

void Player::UpdateJump() {
	if (m_isGround) {
		//m_upPower = JUMP_POWER;
		return;
	}
	float tmp = m_y;
	m_y += (m_y - m_oldY) + m_upPower;
	m_oldY = tmp;
	m_upPower = 0.5f;
}

void Player::TextureInverse() {
	if (m_dir == LEFT) {
		m_u += 0.125;
		m_tw = -0.125f;
	}
	else {
		m_tw = 0.125f;
	}
}

float Player::GetX() {
	return m_move;
}

float Player::GetY() {
	return m_y;
}

float Player::GetW() {
	return m_w;
}

float Player::GetH() {
	return m_h;
}

void Player::SetX(float x) {
	m_move = x;
}

void Player::Sety(float y) {
	m_y = y;
}

void Player::SetW(float w) {
	m_w = w;
}

void Player::SetH(float h) {
	m_h = h;
}

void Player::Grounded(bool isGround) {
	m_isGround = isGround;
}

void Player::Jump() {
	if (m_isGround) {
		m_upPower = JUMP_POWER;
		m_isGround = false;
	}
}

void Player::SetY(float y) {
	m_y = y;
	m_oldY = y;
}

void Player::SetX(DIR dir) {
	if (dir == LEFT) {
		m_move += -m_speed;
	}
	else if (dir == RIGHT) {
		m_move += m_speed;
	}
}

void Player::Attack() {
	if (m_mp < 100) {
		return;
	}
	m_mp -= 100;
	Sound::SE(1)->SetCurrentPosition(0);
	anim.SetState(RUNA_ATTACK);
	anim.SetSpeed(5);
	anim.SetLoop(false);
	m_bullet.push_back(Bullet(m_x, m_y + 32.0f, 64.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, PLAYER, m_dir));
	Sound::SE(1)->Play(0, 0, 0);
}

std::vector<Bullet>* Player::GetBullet() {
	return &m_bullet;
}

void Player::Damage(int damage) {
	anim.SetState(RUNA_DAMAGE);
	Sound::SE(2)->SetCurrentPosition(0);
	Sound::SE(2)->Play(0, 0, 0);
	m_hp += -damage;
}

int Player::GetAtk() {
	return m_atk;
}

void Player::CheckHP() {
	if (m_hp <= 0) {
		m_enable = false;
	}
}

int Player::GetMaxHP() {
	return m_mhp;
}

int Player::GetHP() {
	return m_hp;
}

int Player::GetMaxMP() {
	return m_mmp;
}

int Player::GetMP() {
	return m_mp;
}

float Player::GetFirstX() {
	return m_x;
}

void Player::CheckBullet() {
	for (unsigned int i = 0; i < m_bullet.size(); i++) {
		if (m_bullet[i].GetX() < -100.0f || m_bullet[i].GetX() > 2000.0f) {
			m_bullet.erase(m_bullet.begin() + i);
		}
	}
}

void Player::GetEXP(int exp) {
	m_exp += exp;
}

int Player::SetEXP() {
	return m_exp;
}

void Player::HealMP() {
	m_mp += m_healSpeed;
	if (m_mp > m_mmp) {
		m_mp = m_mmp;
	}
}

void Player::InitializeHP() {
	m_lvhp[0] = 100;
	m_lvhp[1] = 150;
	m_lvhp[2] = 200;
	m_lvhp[3] = 230;
	m_lvhp[4] = 250;
	m_lvhp[5] = 265;
	m_lvhp[6] = 275;
	m_lvhp[7] = 280;
	m_lvhp[8] = 300;
}

void Player::InitializeMP() {
	m_lvmp[0] = 100;
	m_lvmp[1] = 115;
	m_lvmp[2] = 130;
	m_lvmp[3] = 145;
	m_lvmp[4] = 155;
	m_lvmp[5] = 165;
	m_lvmp[6] = 175;
	m_lvmp[7] = 185;
	m_lvmp[8] = 200;
}

void Player::InitializeATK() {
	m_lvatk[0] = 1;
	m_lvatk[1] = 2;
	m_lvatk[2] = 3;
	m_lvatk[3] = 4;
	m_lvatk[4] = 5;
	m_lvatk[5] = 6;
	m_lvatk[6] = 7;
	m_lvatk[7] = 8;
	m_lvatk[8] = 10;
}

void Player::InitializeHeal() {
	m_lvheal[0] = 1.0f;
	m_lvheal[1] = 1.25f;
	m_lvheal[2] = 1.5f;
	m_lvheal[3] = 1.75f;
	m_lvheal[4] = 2.0f;
	m_lvheal[5] = 2.25f;
	m_lvheal[6] = 2.5f;
	m_lvheal[7] = 2.75f;
	m_lvheal[8] = 5.0f;
}

void Player::SetHP() {
	int tmp = m_mhp;
	m_mhp = m_lvhp[m_l.GetHPLV() - 1];
	m_hp += m_mhp - tmp;
}

void Player::SetMP() {
	m_mmp = m_mp =  m_lvmp[m_l.GetMPLV() - 1];
}

void Player::SetATK() {
	m_atk = m_lvatk[m_l.GetATKLV() - 1];
}

void Player::SetHeal() {
	m_healSpeed = m_lvheal[m_l.GetHealLV() - 1];
}

void Player::Heal(int heal) {
	m_hp += (int)((float)m_mhp * (float)heal / 100.0f);
	if (m_hp > m_mhp) {
		m_hp = m_mhp;
	}
}