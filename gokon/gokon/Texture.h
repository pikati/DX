#pragma once
#include "main.h"

class Texture
{
private:
	LPDIRECT3DTEXTURE9 m_texture;
public:
	/// <summary>
	/// �摜��ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	void SetTexture(const char *fileName);

	/// <summary>
	/// �摜��Ԃ�
	/// </summary>
	/// <returns>�e�N�X�`���I�u�W�F�N�g�̃|�C���^</returns>
	LPDIRECT3DTEXTURE9 GetTexture();
	~Texture();
};

