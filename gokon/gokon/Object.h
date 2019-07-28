#pragma once
#include "main.h"
typedef struct {
	/*���W���*/
	float x, y, z;		//D3DFVF_XYZRHW��XYZ�̕���
	/*���܂��Ȃ��ł���*/
	float rhw;          //�ˉe�ϊ������t���O D3DFVF_XYZRHW��RHW�̕��� �p�C�v���C���̍Ō�ɍs���X�P�[���ϊ��̒l�ō\���̂̒��ɂ���ƒ��_�����W�ϊ��ς݂ł���Ɣ��f�����
	/*�|���S���̐F���*/
	D3DCOLOR deffuse;	//D3DFVF_DIFFUSE
	/*�e�N�X�`�����W*/
	float tu, tv;		//D3DFVF_TEX1
}VERTEX;

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
	//�I�u�W�F�N�g�̃e�N�X�`��
	LPDIRECT3DTEXTURE9 m_texture;
public:
	virtual void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, LPDIRECT3DTEXTURE9 texture) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
};