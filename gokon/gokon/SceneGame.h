#pragma once
#include "BaseScene.h"
#include "Object.h"
#include "main.h"

class SceneGame : public BaseScene, public Object
{
public:
	~SceneGame();
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
};

