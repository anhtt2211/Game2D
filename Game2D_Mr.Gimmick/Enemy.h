#pragma once

#include "GameObject.h"

#define ENEMY_ANI_WALKING_LEFT

class Enemy : public CGameObject
{
public:
	Enemy();

	void Update(DWORD dt);
	void Render();
};

