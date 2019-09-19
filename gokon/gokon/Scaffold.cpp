#include "Scaffold.h"
#include "Polygons.h"

void Scaffold::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
}

void Scaffold::Update() {
}

void Scaffold::Draw(LPDIRECT3DTEXTURE9 texture) {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture);
}

void Scaffold::Finalize() {
	SAFE_RELEASE(m_texture);
	m_texture = NULL;
}