#pragma once

#include "GameObject.h"

#define GOOMBA_WALKING_SPEED		0.05f;

#define GOOMBA_BBOX_WIDTH			18
#define GOOMBA_BBOX_HEIGHT			18
#define GOOMBA_BBOX_HEIGHT_DIE		9

#define GOOMBA_STATE_WALKING		100
#define GOOMBA_STATE_DIE			200

#define GOOMBA_ANI_WALKING_LEFT		6
#define GOOMBA_ANI_WALKING_RIGHT	7
#define GOOMBA_ANI_DIE				1

class CGoomba : public CGameObject
{
public:
	CGoomba();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void SetState(int state);
};

