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

class Polygons
{
private:
	static VERTEX vertex[4];
public:
	static void SetPosition(float x, float y, float w, float h, float tx, float ty, float tw, float th);
	static void SetColor(D3DCOLOR deffuse);
	static void Draw(LPDIRECT3DTEXTURE9 texture);
};
