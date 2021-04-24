#include "Gimmick.h"
#include <dinput.h>

CGimmick::CGimmick() {
	CGameObject();
}

void CGimmick::Update(DWORD dt) {
	CGameObject::Update(dt);

	// simple fall down
	vy += GIMMICK_GRAVITY;
	if (y > 100)
	{
		vy = 0; y = 100.0f;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}

void CGimmick::Render() {
	int ani;
	if (vx == 0)
	{
		if (nx > 0) ani = GIMMICK_ANI_IDLE_RIGHT;
		else ani = GIMMICK_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = GIMMICK_ANI_WALKING_RIGHT;
	else ani = GIMMICK_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void CGimmick::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case GIMMICK_STATE_WALKING_RIGHT:
		vx = GIMMICK_WALKING_SPEED;
		nx = 1;
		break;
	case GIMMICK_STATE_WALKING_LEFT:
		vx = GIMMICK_WALKING_SPEED;
		nx = -1;
		break;
	case GIMMICK_STATE_JUMP:
		if (y == 100) {
			vy = -GIMMICK_JUMP_SPEED_Y;
		}
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