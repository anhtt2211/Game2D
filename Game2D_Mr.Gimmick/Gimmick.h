#pragma once
#include "GameObject.h"
#include "CKeyEventHandler.h"
#include "Game.h"
#include "Goomba.h"

#define GIMMICK_WALKING_SPEED		0.1f
#define GIMMICK_JUMP_SPEED_Y		0.7f
#define GIMMICK_JUMP_DEFLECT_SPEED	0.2f
#define GIMMICK_GRAVITY				0.05f

#define GIMMICK_STATE_IDLE			0
#define GIMMICK_STATE_WALKING_RIGHT	100
#define GIMMICK_STATE_WALKING_LEFT	200
#define GIMMICK_STATE_JUMP			300
#define GIMMICK_STATE_DIE			400

#define GIMMICK_ANI_IDLE_RIGHT			0
#define GIMMICK_ANI_IDLE_LEFT			1
#define GIMMICK_ANI_WALKING_RIGHT		2
#define GIMMICK_ANI_WALKING_LEFT		3
#define GIMMICK_ANI_JUMPING_RIGHT		4
#define GIMMICK_ANI_JUMPING_LEFT		5

#define GIMMICK_BBOX_WIDTH  20
#define GIMMICK_BBOX_HEIGHT 22

#define	GIMMICK_LEVEL_SMALL		1
#define	GIMMICK_LEVEL_BIG		2

#define GIMMICK_UNTOUCHABLE_TIME 5000

class CGimmick : public CGameObject
{
private:
	bool isCollisionAxisYWithBrick = false;
	int level;
	int untouchable;
	DWORD untouchable_start;

	CCamera* camera;
	
public:
	CGimmick() : CGameObject() {
		level = GIMMICK_LEVEL_BIG;
		untouchable = 0;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void Render(CCamera* camera);
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void GetBoundingBox(float&, float&, float&, float&);

	void CollisionWithBrick(const vector<LPGAMEOBJECT>* coObjects = NULL);

	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void KeyState(BYTE* states);
};




