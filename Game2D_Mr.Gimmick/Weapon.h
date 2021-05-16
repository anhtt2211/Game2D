#ifndef __WEAPON_H__
#define	__WEAPON_H__

#pragma once

#include "GameObject.h"
#include "Camera.h"


class Weapon : public CGameObject
{
protected:
	bool isFinish;
	DWORD LastTimeAttack;
public:
	Weapon();
	~Weapon();

	int GetDirection();
	bool GetFinish();
	void SetDirection(int dir);
	void SetFinish(bool finish);

	virtual void Attack(float x, float y, int direction);

	virtual void Render(CCamera* camera);
};

#endif