#include "Goomba.h"

CGoomba::CGoomba() {

}

void CGoomba::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = this->x;
	t = this->y;
	r = this->x + GOOMBA_BBOX_WIDTH;
	b = this->y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);

	/*x += dx;
	y += dy;*/

	if (vx < 0 && x < 100) {
		x = 100;
		vx = -vx;
	}

	if (vx > 0 && x > 200) {
		x = 190;
		vx = -vx;
	}
}

void CGoomba::Render() {
	int ani;
	if (vx > 0) {
		ani = GOOMBA_ANI_WALKING_RIGHT;
	}
	else {
		ani = GOOMBA_ANI_WALKING_LEFT;
	}

	// xoay hinh
	if (ani % 2 == 0) {
		this->animations[ani]->Render(-x, y);
	}
	else {
		this->animations[ani]->Render(x, y);
	}
	/*int ani = GOOMBA_ANI_WALKING;

	this->animations[ani]->Render(-x, y);*/
}

void CGoomba::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		direction = -1;
		break;
	}
}