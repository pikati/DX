
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
	player.SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	texture.SetTexture("runa.png");
	anim.Initialize(RUNA);
}

void Player::Update() {
	if (Input::GetKey(DIK_RIGHT)) {
		m_x += 1.0f;
	}
	if (Input::GetKey(DIK_LEFT)) {
		m_x += -1.0f;
	}
	if (Input::GetKey(DIK_Q)) {
		anim.SetState(RUNA_IDOL);
	}
	if (Input::GetKey(DIK_W)) {
		anim.SetState(RUNA_MOVE);
	}
	if (Input::GetKey(DIK_E)) {
		anim.SetState(RUNA_JUMP);
	}
	if (Input::GetKey(DIK_R)) {
		anim.SetState(RUNA_ATTACK);
	}
	if (Input::GetKey(DIK_T)) {
		anim.SetState(RUNA_DAMAGE);
	}
	anim.Update();
	player.SetPosition(m_x, m_y, m_w, m_h, m_u, m_v, m_w, m_h);
	FLOAT2 uv = anim.GetTexturePosition();
	m_u = uv.x;
	m_v = uv.y;
	/*ìñÇΩÇËîªíËÇ∆Ç©Ç¢ÇÎÇ¢ÇÎèàóù*/
}

void Player::Draw() {
	player.Draw(texture.GetTexture());
}

void Player::Finalize() {
}