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
	//�����x���W�A�����y���W�A�����A�c���A�e�N�X�`���i�w�i�j�̍���x���W�A�e�N�X�`���̍���y���W�A�e�N�X�`���̉����A�e�N�X�`���̏c���A�e�N�X�`��
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
};

