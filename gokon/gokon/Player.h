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
	DIR					m_oldDir;
	void Gravity();
	void Inversion() override;
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) override;
	void Update() override;
	void Draw(LPDIRECT3DTEXTURE9 texture) override;
	void Finalize() override;
	void Jump();
};

