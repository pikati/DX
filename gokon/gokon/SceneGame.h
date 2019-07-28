#pragma once
#include "BaseScene.h"
#include "Object.h"
#include "main.h"

class SceneGame : public BaseScene, public Object
{
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, LPDIRECT3DTEXTURE9 texture);
	void Update();
	void Draw();
	void Finalize();
};

