#pragma once
#include "Object.h"
class Player :
	public Object
{
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
};

