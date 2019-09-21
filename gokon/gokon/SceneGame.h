#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Object.h"
#include "Player.h"
#include "main.h"
#include "Scaffold.h"

#define BLOCK_NUM 5

class SceneGame : public BaseScene
{
private:
	Player	player;
	Texture texture;
	Scaffold m_scaffold[10];
	bool		m_playerHit;
public:
	~SceneGame();
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
	void UpdatePlayer();
	void DrawPlayer();
	void DrawScaffold();
};