#include "Scaffold.h"
#include "Polygons.h"

void Scaffold::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	m_attribute = attr;
	m_dir = dir;
	m_firstX = m_x;
	m_aria = false;
}

void Scaffold::Update() {
	if (m_x > -256.0f && m_x < 1920.0f) {
		m_aria = true;
	}
	else{
		m_aria = false;
	}
}

void Scaffold::Draw(LPDIRECT3DTEXTURE9 texture) {
	if (!m_aria) {
		return;
	}
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture);
}

void Scaffold::Finalize() {
}


float Scaffold::GetX() {
	return m_x;
}

float Scaffold::GetY() {
	return m_y;
}

float Scaffold::GetW() {
	return m_w;
}

float Scaffold::GetH() {
	return m_h;
}

void Scaffold::SetX(float x) {
	m_x = x;
}

void Scaffold::Sety(float y) {
	m_y = y;
}

void Scaffold::SetW(float w) {
	m_w = w;
}

void Scaffold::SetH(float h) {
	m_h = h;
}

float Scaffold::GetFirstX() {
	return m_firstX;
}