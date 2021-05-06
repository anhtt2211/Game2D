#pragma once

#include "Sprite.h"
#include "TextureManager.h"
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
	CTextureManager* textures = CTextureManager::GetInstance();
	SpriteManager* sprites = SpriteManager::GetInstance();
	AnimationManager* animations = AnimationManager::GetInstance();

public:
	ResourceManager();
	static ResourceManager* GetInstance();
	void LoadResource();
};

