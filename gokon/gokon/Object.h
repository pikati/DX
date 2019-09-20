#pragma once
#include "main.h"

enum DIR {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class Object
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
	//�I�u�W�F�N�g�̑���
	int		m_attribute;
	//�I�u�W�F�N�g�̌���
	DIR		m_dir;
	//�I�u�W�F�N�g�̃e�N�X�`��
	LPDIRECT3DTEXTURE9 m_texture;
	//�f�o�C�X
	LPDIRECT3DDEVICE9 m_d3dDevice;

	virtual void Inversion() = 0;
public:
	virtual void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DTEXTURE9 texture) = 0;
	virtual void Finalize() = 0;
	
};