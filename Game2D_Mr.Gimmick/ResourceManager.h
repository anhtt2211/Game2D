#pragma once

#include "Sprite.h"
#include "Gimmick.h"
#include "Goomba.h"



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

