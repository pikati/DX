#include "Texture.h"

Texture::Texture() {
	m_textureNum = 0;
}

void Texture::LoadTexture(const char *fileName) {
	D3DXCreateTextureFromFile(GetDevice(), fileName, &m_texture[m_textureNum++]);
}

LPDIRECT3DTEXTURE9 Texture::SetTexture(int i) {
	return m_texture[i];
}

void Texture::Finalize() {
	for (int i = m_textureNum; i >= 0; i--) {
		SAFE_RELEASE(m_texture[i]);
	}
	m_textureNum = 0;
}