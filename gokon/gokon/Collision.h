#pragma once
#include "main.h"

class Collision
{
public:
	static bool	IsCollisionEnter(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh, int i);
	static DIR	CollisionDirection(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh);
};

