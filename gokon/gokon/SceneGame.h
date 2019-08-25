#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Object.h"
#include "main.h"

class SceneGame : public BaseScene, public Object
{
private:
	Texture texture;
public:
	~SceneGame();
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
};

