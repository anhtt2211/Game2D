#include "Enemy.h"

Enemy::Enemy() {

}

void Enemy::Update(DWORD dt) {
	CGameObject::Update(dt);
}

void Enemy::Render() {
	this->animations[1]->Render(-x, y);
}