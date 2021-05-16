#include "Weapon.h"

Weapon::Weapon() {

}

Weapon::~Weapon() {

}

int Weapon::GetDirection() {
	return this->direction;
}

bool Weapon::GetFinish() {
	return this->isFinish;
}

void Weapon::SetDirection(int dir) {
	this->direction = dir;
}

void Weapon::SetFinish(bool finish) {
	this->isFinish = finish;
}

void Weapon::Attack(float x, float y, int dir) {
	this->x = x;
	this->y = y;
	this->direction = dir;
	this->isFinish = false;	//chua ket thuc
	this->LastTimeAttack = GetTickCount();
}

void Weapon::Render(CCamera* camera) {
	if (this->isFinish) {
		return;
	}

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == 1) {

	}
}