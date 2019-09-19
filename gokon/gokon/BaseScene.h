#pragma once
#include "main.h"

class BaseScene
{
protected:
	//�I�u�W�F�N�g�̍����x���W
	float m_x;
	//�I�u�W�F�N�g�̍����y���W
	float m_y;
	//�I�u�W�F�N�g�̉���
	float m_w;
	//�I�u�W�F�N�g�̏c��
	float m_h;
	//�e�N�X�`���̍����x���W
	float m_u;
	//�e�N�X�`���̍����y���W
	float m_v;
	//�e�N�X�`���̉���
	float m_tw;
	//�e�N�X�`���̏c��
	float m_th;
public:
	virtual ~BaseScene() {};
	virtual void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
};

