#pragma once
#include "main.h"

class Texture
{
private:
	LPDIRECT3DTEXTURE9 m_texture[10];
	int m_textureNum;
public:
	Texture();
	/// <summary>
	/// �摜��ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	void LoadTexture(const char *fileName);

	/// <summary>
	/// �摜��Ԃ�
	/// </summary>
	/// <returns>�e�N�X�`���I�u�W�F�N�g�̃|�C���^</returns>
	LPDIRECT3DTEXTURE9 SetTexture(int i);
	void Finalize();
};

