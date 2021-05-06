#pragma once

#include "Sprite.h"
#include "Gimmick.h"
#include "Enemy.h"

#define ID_TEX_GIMMICK 10
#define ID_TEX_ENEMY 20


#define GIMMICK_TEXTURE_PATH "./Resources/Images/Gimmick/Gimmick.png"
#define ENEMY_TEXTURE_PATH "./Resources/Images/Enemies_Bosses/Boss.png"

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

