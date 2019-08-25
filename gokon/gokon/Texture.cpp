#include "Texture.h"

void Texture::SetTexture(const char *fileName) {
	D3DXCreateTextureFromFile(GetDevice(), fileName, &m_texture);
}

LPDIRECT3DTEXTURE9 Texture::GetTexture() {
	return m_texture;
}

Texture::~Texture() {
	SAFE_RELEASE(m_texture);
}