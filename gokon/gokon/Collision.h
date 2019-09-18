#pragma once

enum DIR {
	DIR_UP,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_LEFT
};

class Collision
{
public:
	template<typename T>
	bool	IsCollisionEnter(T a, T b);
	template<typename T>
	DIR		CollisionDirection(T a, T b);
};

