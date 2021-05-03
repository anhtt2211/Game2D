#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"

class CGameObject
{
protected:
	float x, y;
	float vx, vy;
	int nx;
	int state;

	static vector<LPANIMATION> animations;

public:
	CGameObject();

	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	void SetSpeed(float vx, float vy) {
		this->vx = vx;
		this->vy = vy;
	}
	
	int GetState() {
		return this->state;
	}
	void SetState(int state) {
		this->state = state;
	}

	float GetX() {
		return this->x;
	}
	float GetY() {
		return this->y;
	}

	static void AddAnimation(int aniID);

	virtual void Update(DWORD dt);
	virtual void Render();

	////v/*irtual void OnKeyDown(int keycode);
	//virtual void OnKeyUp(int keycode);
	//virtual void KeyState(BYTE* state);*/
};
typedef CGameObject* LPGAMEOBJECT;

