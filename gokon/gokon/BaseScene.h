#pragma once
#include "main.h"

class BaseScene
{
public:
	virtual ~BaseScene() {};
	virtual void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, LPDIRECT3DTEXTURE9 texture) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
};

