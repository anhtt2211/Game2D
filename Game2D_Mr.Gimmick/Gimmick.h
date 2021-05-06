#pragma once
#include "GameObject.h"
#include "CKeyEventHandler.h"
#include "Game.h"

#define GIMMICK_WALKING_SPEED		0.1f
#define GIMMICK_JUMP_SPEED_Y		0.7f
#define GIMMICK_GRAVITY				0.05f

#define GIMMICK_STATE_IDLE			0
#define GIMMICK_STATE_WALKING_RIGHT	100
#define GIMMICK_STATE_WALKING_LEFT	200
#define GIMMICK_STATE_JUMP			300

#define GIMMICK_ANI_IDLE_RIGHT			0
#define GIMMICK_ANI_IDLE_LEFT			1
#define GIMMICK_ANI_WALKING_RIGHT		2
#define GIMMICK_ANI_WALKING_LEFT		3
#define GIMMICK_ANI_JUMPING_RIGHT		4
#define GIMMICK_ANI_JUMPING_LEFT		5

class CGimmick : public CGameObject
{
public:
	CGimmick();

	void Update(DWORD dt);
	void Render();
	virtual void Render(CCamera* camera);
	void SetState(int state);

	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void KeyState(BYTE* states);
};




