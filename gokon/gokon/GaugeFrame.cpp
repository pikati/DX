#include "GaugeFrame.h"
#include "Polygons.h"
#include "Player.h"

void GaugeFrame::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	m_max = 100.0f;
	m_length = 2.0f;
}

void GaugeFrame::Update() {
	m_w = m_max * m_length;

}

void GaugeFrame::Draw(LPDIRECT3DTEXTURE9 texture) {
	Polygons::Draw(m_x, m_y, m_w, m_h, m_u, m_v, m_tw, m_th, texture);
}

void GaugeFrame::Finalize() {
}

float GaugeFrame::GetX() {
	return m_x;
}

float GaugeFrame::GetY() {
	return m_y;
}

float GaugeFrame::GetW() {
	return m_w;
}

float GaugeFrame::GetH() {
	return m_h;
}

void GaugeFrame::SetX(float x) {
	m_x = x;
}

void GaugeFrame::Sety(float y) {
	m_y = y;
}

void GaugeFrame::SetW(float w) {
	m_w = w;
}

void GaugeFrame::SetH(float h) {
	m_h = h;
}

void GaugeFrame::SetAttr(KINDGAUGE kind) {
	m_attribute = kind;
}

void GaugeFrame::SetValue(int value) {
	m_max = value;
}

void GaugeFrame::SetPosition(float x, float y) {
	m_x = x;
	m_y = y;
}

void GaugeFrame::SetLength(float length) {
	m_length = length;
}