#pragma once
#include "Object.h"
#include "Texture.h"
class Scaffold :
	public Object
{
private:
	Texture		texture;
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
};

