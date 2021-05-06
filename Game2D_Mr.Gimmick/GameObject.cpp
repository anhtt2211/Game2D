#include "GameObject.h"
#include "Sprite.h"

vector<LPANIMATION> CGameObject::animations;

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

void CGameObject::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
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
