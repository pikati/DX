#pragma once
#include "Texture.h"
class Score
{
private:
	Texture m_texture;
	int m_score;
	float m_y;
	bool m_s;
public:
	void Initialize(bool score, float m_y);
	void Update();
	void Draw();
	void Finalize();
	void AddScore(int score);
	int  GetScore();
	void SetScore(int value);
};

