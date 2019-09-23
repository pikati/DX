#include "ObjectManager.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "Cat.h"
#include "Scaffold.h"

Player* ObjectManager::SetPlayer() {
	return ((SceneGame*)SceneManager::SetSceneGame())->SetPlayer();
}

Scaffold* ObjectManager::SetFloor() {
	return ((SceneGame*)SceneManager::SetSceneGame())->SetS();
}

Cat* ObjectManager::SetCat() {
	return ((SceneGame*)SceneManager::SetSceneGame())->SetCat();
}
