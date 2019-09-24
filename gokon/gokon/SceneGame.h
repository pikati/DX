#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Object.h"
#include "Player.h"
#include "main.h"
#include "Scaffold.h"
#include "GameUI.h"
#include "Cat.h"
#include "Score.h"
#include "Time.h"

#define BLOCK_NUM 89
#define CAT_MAX 31

class SceneGame : public BaseScene
{
private:
	Player	player;
	Cat		m_cat[CAT_MAX];
	Texture texture;
	Scaffold m_scaffold[BLOCK_NUM];
	GameUI	m_gameUI;
	Score   m_scor;
	Score   m_exp;
	Time	m_time;
	bool	m_playerHit;
	int		m_score;
	bool	m_end;

	void InitilizeScaffold();
	void InitializeCat();
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