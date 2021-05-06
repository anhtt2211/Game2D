#pragma once

#include "Sprite.h"
#include "Gimmick.h"
#include "Enemy.h"



class ResourceManager
{
private:
	static ResourceManager* __instance;
	CSpriteManager* sprites = CSpriteManager::GetInstance();
	CAnimationManager* animations = CAnimationManager::GetInstance();

public:
	ResourceManager();
	static ResourceManager* GetInstance();
	void LoadResource();
};

