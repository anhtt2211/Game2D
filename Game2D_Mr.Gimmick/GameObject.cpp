#include "GameObject.h"

vector<LPANIMATION> CGameObject::animations;

void CGameObject::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	/*left = x;
	top = y;
	right = left + this->texture->GetFrameWidth();
	bottom = top + this->texture->GetFrameHeight();*/
}

void CGameObject::SetPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void CGameObject::SetSpeed(float vx, float vy) {
	this->vx = vx;
	this->vy = vy;
}

void CGameObject::SetState(int state) {
	this->state = state;

}

void CGameObject::SetHealth(int h) {
	this->health = h;
}

void CGameObject::SetID(int id) {
	this->id = id;
}

void CGameObject::SetDirection(int dir) {
	this->direction = dir;
}

void CGameObject::GetSpeed(float& vx, float& vy) {
	vx = this->vx;
	vy = this->vy;
}

int CGameObject::GetState() {
	return this->state;
}

int CGameObject::GetHealth() {
	return this->health;
}

int CGameObject::GetID() {
	return this->id;
}

float CGameObject::GetX() {
	return this->x;
}

float CGameObject::GetY() {
	return this->y;
}

CGameObject::CGameObject() {
	x = y = 0;
	vx = vy = 0;
	direction = 1;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> * coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;

	/*x += dx;
	y += dy;*/
}

void CGameObject::Render()
{

}

void CGameObject::Render(CCamera* camera)
{

}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimationManager::GetInstance()->Get(aniId);
	animations.push_back(ani);
}

void CGameObject::RenderBoundingBox(CCamera* camera) {
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (LONG)r - (LONG)l;
	rect.bottom = (LONG)b - (LONG)t;

	D3DXVECTOR2 pos = camera->Transform(l, t);

	CGame::GetInstance()->Draw(
		pos.x,
		pos.y,
		CTextureManager::GetInstance()->GetTexture(ID_TEX_GIMMICK)->Texture,
		rect.left,
		rect.top,
		rect.right,
		rect.bottom
	);
}

LPCOLLISIONEVENT CGameObject::SweptAABBEx(CGameObject* coO) {
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CollisionEvent* e = new CollisionEvent(t, nx, ny, coO);
	return e;
}

void CGameObject::CalcPotentialCollisions(vector<CGameObject*>* coObjects, vector<LPCOLLISIONEVENT>& coEvents) {
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx,
	float& min_ty,
	float& nx,
	float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t <= min_tx && c->nx != 0) {
			min_tx = c->t;
			nx = c->nx;
			min_ix = i;
		}

		if (c->t <= min_ty && c->ny != 0) {
			min_ty = c->t;
			ny = c->ny;
			min_iy = i;
		}
	}

	if (min_ix >= 0)
		coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0)
		coEventsResult.push_back(coEvents[min_iy]);
}

bool CGameObject::isCollitionObjectWithObject(CGameObject* obj) {
	if (CheckAABB(obj)) // kiểm tra va chạm bằng AABB trước
		return true;

	LPCOLLISIONEVENT e = SweptAABBEx(obj); // kt va chạm giữa 2 object bằng sweptAABB
	bool res = e->t > 0 && e->t <= 1.0f; // ĐK va chạm
	delete (e);
	e = nullptr;
	return res;
}

bool CGameObject::CheckAABB(CGameObject* obj) {
	float l, t, r, b;
	float l1, t1, r1, b1;
	this->GetBoundingBox(l, t, r, b);
	obj->GetBoundingBox(l1, t1, r1, b1);

	if (CGame::GetInstance()->CheckAABB(l, t, r, b, l1, t1, r1, b1))
		return true;

	return false;
}