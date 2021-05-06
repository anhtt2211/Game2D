#include "Gimmick.h"
#include <dinput.h>
#include "Debug.h"

CGimmick::CGimmick() {
	
}

void CGimmick::Update(DWORD dt) {
	CGameObject::Update(dt);

	// simple fall down
	vy += GIMMICK_GRAVITY;
	if (y > 100)
	{
		vy = 0;
		y = 100.0f;
	}
	if (vx > 0 && x > 360) x = 360;
	if (vx < 0 && x < 0) x = 0;
}

void CGimmick::Render() {
	int ani;
	if (vx == 0)
	{
		if (direction > 0) ani = GIMMICK_ANI_IDLE_RIGHT;
		else ani = GIMMICK_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = GIMMICK_ANI_WALKING_RIGHT;
	else ani = GIMMICK_ANI_WALKING_LEFT;
	if (vy < 0)
	{
		if (direction > 0)
		{
			ani = GIMMICK_ANI_JUMPING_RIGHT;
		}
		else
		{
			ani = GIMMICK_ANI_JUMPING_LEFT;
		}
	}
	//xoay hinh
	if (ani % 2 == 1)
	{
		animations[ani]->Render(-x, y);
	}
	else
	{
		animations[ani]->Render(x, y);
	}
}

void CGimmick::Render(CCamera* camera) {

}

void CGimmick::SetState(int state) {
	CGameObject::SetState(state);

	switch (state) {
	case GIMMICK_STATE_WALKING_RIGHT:
		vx = GIMMICK_WALKING_SPEED;
		direction = 1;
		break;
	case GIMMICK_STATE_WALKING_LEFT:
		vx = -GIMMICK_WALKING_SPEED;
		direction = -1;
		break;
	case GIMMICK_STATE_JUMP:
		
		vy = -GIMMICK_JUMP_SPEED_Y;
		
	case GIMMICK_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CGimmick::OnKeyDown(int keycode) {
	switch (keycode)
	{
	case DIK_SPACE:
		CGimmick::SetState(GIMMICK_STATE_JUMP);
		break;
	}
}