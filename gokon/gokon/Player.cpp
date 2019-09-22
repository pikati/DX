#define _CRT_SECURE_NO_WARNINGS
#include "Player.h"
#include "Input.h"
#include "main.h"
#include "Polygons.h"
#include "Utility.h"

/*着地したときにキー入力しっぱだとアニメーションが変更されない*/

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
	m_attribute = PLAYER;
	m_dir = dir;
	m_oldDir = dir;
	m_oldY = m_y;
	m_isGround = false;
	m_upPower = 0;
	m_speed = 5.0f;
	m_attr = attr;
	m_texture.LoadTexture("Star.png");
}

void Player::Update() {
	if (Input::TriggerKey(DIK_RIGHT) || Input::TriggerKey(DIK_LEFT)) {
		anim.SetState(RUNA_MOVE);
	}
	if (Input::ReleaseKey(DIK_RIGHT) || Input::ReleaseKey(DIK_LEFT)) {
		anim.SetState(RUNA_IDOL);
	}
	if (Input::GetKey(DIK_RIGHT)) {
		m_x += m_speed;
		m_dir = RIGHT;
	}
	if (Input::GetKey(DIK_LEFT)) {
		m_x += -m_speed;
		m_dir = LEFT;
	}
	if (Input::GetKey(DIK_Q)) {
		anim.SetState(RUNA_IDOL);
	}
	if (Input::GetKey(DIK_E)) {
		anim.SetState(RUNA_JUMP);
		Jump();
	}
	if (Input::TriggerKey(DIK_Z)) {
		Attack();
	}
	if (Input::GetKey(DIK_T)) {
		anim.SetState(RUNA_DAMAGE);
	}
	UpdateJump();
	anim.Update();
	FLOAT2 uv = anim.SetTexturePosition();
	m_u = uv.x;
	m_v = uv.y;
	//Inversion();
	TextureInverse();
	/*当たり判定とかいろいろ処理*/
	m_oldDir = m_dir;
	MyOutputDebugString("Grounded%s\n", m_isGround ? "true" : "false");
	for (int i = 0; i < m_bullet.size(); i++) {
		m_bullet[i].Update();
	}

}

void Player::Draw(LPDIRECT3DTEXTURE9 texture) {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture);
	for (int i = 0; i < m_bullet.size(); i++) {
		m_bullet[i].Draw(m_texture.SetTexture(0));
	}
}

void Player::Finalize() {
	m_texture.Finalize();
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

void Player::Inversion() {
	if (m_dir != m_oldDir) {
		m_x += m_w;
		m_w *= -1;
	}
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
	return m_x;
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
		m_x += -m_speed;
	}
	else if (dir == RIGHT) {
		m_x += m_speed;
	}
}

void Player::Attack() {
	anim.SetState(RUNA_ATTACK);
	anim.SetLoop(false);
	m_bullet.push_back(Bullet(m_x, m_y + 32.0f, 64.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, PLAYER, m_dir));
}