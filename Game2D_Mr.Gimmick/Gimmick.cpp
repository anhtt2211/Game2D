#include "Gimmick.h"
#include <dinput.h>
#include "Debug.h"

void CGimmick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	//CGameObject::Update(dt);

	//// simple fall down
	//vy += GIMMICK_GRAVITY * dt;

	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//// turn off collision when die 
	//if (state != GIMMICK_STATE_DIE) {
	//	CalcPotentialCollisions(coObjects, coEvents);
	//}

	//// reset untouchable timer if untouchable time has passed
	//if (GetTickCount() - untouchable_start > GIMMICK_UNTOUCHABLE_TIME) {
	//	untouchable_start = 0;
	//	untouchable = 0;
	//}

	//// No collision occured, proceed normally
	//if (coEvents.size() == 0) {
	//	x += dx;
	//	y += dy;
	//}
	//else {
	//	float min_tx, min_ty, nx = 0, ny;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//	// block 
	//	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	y += min_ty * dy + ny * 0.4f;

	//	if (nx != 0) {
	//		vx = 0;
	//	}
	//	if (ny != 0) {
	//		vy = 0;
	//	}

	//	// Collision logic with Goombas
	//	for (UINT i = 0; i < coEventsResult.size(); i++) {
	//		LPCOLLISIONEVENT e = coEventsResult[i];

	//		// if e->obj is Goomba 
	//		if (dynamic_cast<CGoomba*>(e->obj)) {	
	//			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	//			// jump on top >> kill Goomba and deflect a bit 
	//			if (e->ny < 0)
	//			{
	//				if (goomba->GetState() != GOOMBA_STATE_DIE)
	//				{
	//					goomba->SetState(GOOMBA_STATE_DIE);
	//					vy = -GIMMICK_JUMP_DEFLECT_SPEED;
	//				}
	//			}
	//			else if (e->nx != 0)
	//			{
	//				if (untouchable == 0)
	//				{
	//					if (goomba->GetState() != GOOMBA_STATE_DIE)
	//					{
	//						if (level > GIMMICK_LEVEL_SMALL)
	//						{
	//							level = GIMMICK_LEVEL_SMALL;
	//							StartUntouchable();
	//						}
	//						else
	//							SetState(GIMMICK_STATE_DIE);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) {
	//	delete coEvents[i];
	//}

	CGameObject::Update(dt);

	// simple fall down
	vy += GIMMICK_GRAVITY;
	if (y > 150)
	{
		vy = 0;
		y = 150.0f;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (vx > 0 && x > SCREEN_WIDTH - 30) {
		x = SCREEN_WIDTH - 10;
	}
	if (vx < 0 && x < 0) {
		x = 0;
	}
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
		break;
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

void CGimmick::GetBoundingBox(float& l, float& t, float& r, float& b) {
	CGameObject::GetBoundingBox(l, t, r, b);

	l = x;
	t = y;
	r = x + GIMMICK_BBOX_WIDTH;
	b = y + GIMMICK_BBOX_HEIGHT;	
}

void CGimmick::CollisionWithBrick(const vector<LPGAMEOBJECT>* coObjects) {
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++) {
		list_Brick.push_back(coObjects->at(i));
		/*if (coObjects->at(i)->GetType() == eType::BRICK) { 
		
		}*/
	}

	CalcPotentialCollisions(&list_Brick, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		isCollisionAxisYWithBrick = false; // đang ko va chạm trục y
	//	DebugOut(L"%d : Col y = false (size = 0) - dt = %d - y = %f - dy = %f\n",GetTickCount(),dt,y, dy);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;

		if (ny == -1)
			y += min_ty * dy + ny * 0.4f;
		else
			y += dy;

		if (ny == -1)
		{
			vy = 0.1f;
			dy = vy * dt;

			/*if (isJumping)
			{
				isJumping = false;
				y = y - PULL_UP_SIMON_AFTER_JUMPING;
			}*/
		}


		if (ny != 0)
		{
			isCollisionAxisYWithBrick = true;
			//		DebugOut(L"%d : Col y = true - dt=%d - y = %f - dy = %f\n", GetTickCount(), dt,y, dy);
		}
		else
		{
			//	DebugOut(L"%d : Col y = false - dt=%d\n", GetTickCount(), dt);
			isCollisionAxisYWithBrick = false;// đang ko va chạm trục y
		}



		/*if (nx != 0 || ny != 0)
		{
			isHurting = 0;
		}*/

	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}