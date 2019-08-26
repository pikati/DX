#define _CRT_SECURE_NO_WARNINGS
#include "Animation.h"
#include "Utility.h"

void Animation::Initialize(int id) {
	m_frame = 0;
	m_totalFrame = 0;
	m_id = id;
	m_speed = 0;
	m_uv.x = 0;
	m_uv.y = 0;
	m_loop = false;
	InitializeAnimation();
}

void Animation::SetState(ANIMATION newState) {
	m_frame = 0;
	m_state = newState;
	m_totalFrame = m_animation[m_state + 1] - m_animation[m_state];
}

void Animation::SetLoop(bool isLoop) {
	m_loop = isLoop;
}

void Animation::SetSpeed(int speed) {
	m_speed = speed;
}

void Animation::Update() {
	UpdateFrame();
	SetUV();
}

FLOAT2 Animation::GetTexPosition() {
	return m_uv;
}

void Animation::InitializeAnimation() {
	switch (m_id) {
	case RUNA:
		m_animation[RUNA_IDOL] = 0;
		m_animation[RUNA_MOVE] = 16;
		m_animation[RUNA_JUMP] = 24;
		m_animation[RUNA_ATTACK] = 28;
		m_animation[RUNA_DAMAGE] = 32;
		m_animation[RUNA_NON] = 33;
		SetState(RUNA_IDOL);
		SetLoop(true);
		SetSpeed(10);
		break;
	case ENEMY:
		SetState(ENEMY_IDOL);
		SetLoop(true);
		SetSpeed(1);
		break;
	default:
		break;
	}
	
}

void Animation::UpdateFrame() {
	m_frame++;
	if (m_frame > m_totalFrame * m_speed - 1) {
		if (m_loop) {
			m_frame = 0;
		}
		else {
			m_frame = m_totalFrame * m_speed - 1;
		}
	}
}

void Animation::SetUV() {
	m_uv.x = (float)((m_frame / m_speed + m_animation[m_state]) % 8) / 8.0f;
	m_uv.y = (float)((m_frame / m_speed + m_animation[m_state]) / 8) / 8.0f;
}