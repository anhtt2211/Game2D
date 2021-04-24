#pragma once
#include "GameObject.h"
#include "CKeyEventHandler.h"

#define GIMMICK_WALKING_SPEED		0.1f
#define GIMMICK_JUMP_SPEED_Y		0.5f
#define GIMMICK_GRAVITY				0.5f

#define GIMMICK_STATE_IDLE			0
#define GIMMICK_STATE_WALKING_RIGHT	100
#define GIMMICK_STATE_WALKING_LEFT	200
#define GIMMICK_STATE_JUMP			300

#define GIMMICK_ANI_IDLE_RIGHT			0
#define GIMMICK_ANI_IDLE_LEFT			1
#define GIMMICK_ANI_WALKING_RIGHT		1
#define GIMMICK_ANI_WALKING_LEFT		3

class CGimmick : public CGameObject
{
public:
	CGimmick();

	void Update(DWORD dt);
	void Render();
	void SetState(int state);

	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void KeyState(BYTE* states);
};




