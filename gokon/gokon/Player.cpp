#include "Player.h"
#include "Input.h"
#include "main.h"
#include "Polygons.h"

void Player::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	texture.SetTexture("runa.png");
}

void Player::Update() {
	if (Input::GetKey(DIK_UP)) {
		m_y += 1.0f;
	}
	if (Input::GetKey(DIK_DOWN)) {
		m_y += -1.0f;
	}
	/*ìñÇΩÇËîªíËÇ∆Ç©Ç¢ÇÎÇ¢ÇÎèàóù*/
}

void Player::Draw() {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture.GetTexture());
}

void Player::Finalize() {
	SAFE_RELEASE(m_texture);
	m_texture = NULL;
}