#pragma once
#include "Animation.h"
#include "Texture.h"
#include "Object.h"
class Player : public Object
{
private:
	Texture		texture;
	Animation	anim;
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
};

