#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Object.h"
#include "main.h"

class SceneTitle : public BaseScene
{
private:
	Texture texture;
public:
	~SceneTitle();
	//左上のx座標、左上のy座標、横幅、縦幅、テクスチャ（背景）の左上x座標、テクスチャの左上y座標、テクスチャの横幅、テクスチャの縦幅、テクスチャ
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
};

