#pragma once
#include "main.h"
#include "SceneGame.h"
#include "Player.h"
#include "Scaffold.h"
#include "Cat.h"
class ObjectManager
{
private:
public:
	static Player* SetPlayer();
	static Scaffold* SetFloor();
	static Cat* SetCat();
};

