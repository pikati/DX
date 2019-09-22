#pragma once
#include "Object.h"
#include "Texture.h"
class Scaffold :
	public Object
{
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir);
	void Update();
	void Draw(LPDIRECT3DTEXTURE9 texture);
	void Finalize();
	float GetX() override;
	float GetY() override;
	float GetW() override;
	float GetH() override;
};

