#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "Camera.h"

class CGameObject
{
protected:
	float x, y; // position of object in world 
	float vx, vy;

	int id;
	int health;
	int direction;	// 1: to right
					// -1: to left
	int state;

	static vector<LPANIMATION> animations;

public:
	CGameObject();

	void SetPosition(float x, float y);
	void SetSpeed(float vx, float vy);
	void SetState(int state);
	void SetID(int id);
	void SetDirection(int dir);
	void SetHealth(int h);

	int GetState();
	int GetID();
	float GetX();
	float GetY();
	int GetHealth();

	static void AddAnimation(int aniID);

	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Render(CCamera* camera);
};
typedef CGameObject* LPGAMEOBJECT;

