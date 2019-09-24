#pragma once
#include "Texture.h"
class Score
{
private:
	static Texture m_texture;
	static int m_score;
public:
	static void Initialize();
	static void Update();
	static void Draw();
	static void Finalize();
	static void AddScore(int score);
	static int  GetScore();
};

