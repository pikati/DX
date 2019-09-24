#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Object.h"
#include "Player.h"
#include "main.h"
#include "Scaffold.h"
#include "GameUI.h"
#include "Cat.h"

#define BLOCK_NUM 21
#define CAT_MAX 1

class SceneGame : public BaseScene
{
private:
	Player	player;
	Cat		m_cat[CAT_MAX];
	Texture texture;
	Scaffold m_scaffold[BLOCK_NUM];
	GameUI	m_gameUI;
	bool		m_playerHit;

	void UpdatePlayer();
	void UpdateEnemy();
	void UpdateScaffold();
	void UpdateCollision();
	void DrawPlayer();
	void DrawEnemy();
	void DrawScaffold();
	void ColPandS();
	void ColCandS();
	void ColCandA();
	void ColPandA();
public:
	~SceneGame();
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th);
	void Update();
	void Draw();
	void Finalize();
	Player* SetPlayer();
	Scaffold* SetS();
	Cat* SetCat();
};