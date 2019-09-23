#pragma once
#include "main.h"
class Camera
{
private:
	static float m_moveX;
	static float m_moveY;
public:
	static void Initialize();
	static void Update();
	static void GetDiff(float x, float y);
};

