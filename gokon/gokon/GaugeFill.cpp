#include "GaugeFill.h"
#include "Polygons.h"
#include "Player.h"

void GaugeFill::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	m_max = 100.0f;
	m_now = 100.0f;
	m_length = 2.0f;
}

void GaugeFill::Update() {
	if (m_attribute == HP) {
		m_w = m_now * m_length;
		if ((float)m_now / (float)m_max > 0.5) {
			m_v = 0.0f;
		}
		else if ((float)m_now / (float)m_max > 0.25) {
			m_v = 0.25f;
		}
		else {
			m_v = 0.5f;
		}
	}
	else if (m_attribute == MP) {
		m_w = m_now * 2;
		m_v = 0.75f;
	}
}

void GaugeFill::Draw(LPDIRECT3DTEXTURE9 texture) {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture);
}

void GaugeFill::Finalize() {
}

float GaugeFill::GetX() {
	return m_x;
}

float GaugeFill::GetY() {
	return m_y;
}

float GaugeFill::GetW() {
	return m_w;
}

float GaugeFill::GetH() {
	return m_h;
}

void GaugeFill::SetX(float x) {
	m_x = x;
}

void GaugeFill::Sety(float y) {
	m_y = y;
}

void GaugeFill::SetW(float w) {
	m_w = w;
}

void GaugeFill::SetH(float h) {
	m_h = h;

}
void GaugeFill::SetAttr(KINDGAUGE kind) {
	m_attribute = kind;
}

void GaugeFill::SetValue(int max, int now) {
	m_max = max;
	m_now = now;
}
void GaugeFill::SetPosition(float x, float y) {
	m_x = x;
	m_y = y;
}

void GaugeFill::SetLength(float length) {
	m_length = length;
}