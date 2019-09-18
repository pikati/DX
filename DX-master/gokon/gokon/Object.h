#pragma once
#include "main.h"

class Object
{
public:
	void SetPosition(float x, float y, float w, float h, float u, float v, float tw, float th);
	void SetColor(D3DCOLOR deffuse);
	void Draw(LPDIRECT3DTEXTURE9 texture);
};