#include "Bullet.h"
#include "Polygons.h"

Bullet::Bullet(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	m_attr = attr;
	m_dir = dir;
}

void Bullet::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	m_attr = attr;
	m_dir = dir;
}

void Bullet::Update() {
	Move();
}

void Bullet::Draw(LPDIRECT3DTEXTURE9 texture) {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture);
}

void Bullet::Finalize() {

}

float Bullet::GetX() {
	return m_x;
}

float Bullet::GetY() {
	return m_y;
}

float Bullet::GetW() {
	return m_w;
}

float Bullet::GetH() {
	return m_h;
}

void Bullet::SetX(float x) {
	m_x = x;
}

void Bullet::Sety(float y) {
	m_y = y;
}

void Bullet::SetW(float w) {
	m_w = w;
}

void Bullet::SetH(float h) {
	m_h = h;
}

void Bullet::Move() {
	switch (m_dir)
	{
	case RIGHT:
		m_x += 10.0f;
		break;
	case LEFT:
		m_x += -10.0f;
		break;
	default:
		break;
	}
}

int Bullet::HitDamage() {
	Erase();
	return m_atk;
}

void Bullet::Erase() {
	m_y = 1000.0f;
	m_dir = NON;
}