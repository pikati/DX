#pragma once
#include "Animation.h"
#include "Texture.h"
#include "Object.h"
/*テクスチャ関係*/
class Player : public Object
{
private:
	Texture				texture;
	Animation			anim;
	LPDIRECT3DTEXTURE9	m_texture;
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
	void SetTexture();
};

