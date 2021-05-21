#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <algorithm>
#include "Sprite.h"
#include "Camera.h"
#include "Texture.h"
#include "TextureManager.h"

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent* LPCOLLISIONEVENT;

using namespace std;

struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class CGameObject
{
protected:
	float x, y; // position of object in world 
	float vx, vy;
	float dx, dy;

	int id;
	int health;
	int direction;	// 1: to right
					// -1: to left
	int state;

	DWORD dt;

	static vector<LPANIMATION> animations;
	CTexture* texture;

public:
	CGameObject();

	virtual void GetBoundingBox(float&, float&, float&, float&);

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
	void GetSpeed(float&, float&);

	static void AddAnimation(int aniID);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> * coObjects = NULL);
	virtual void Render();
	virtual void Render(CCamera* camera);

	void RenderBoundingBox(CCamera* camera);
	LPCOLLISIONEVENT SweptAABBEx(CGameObject* coO);
	void CalcPotentialCollisions(vector<CGameObject*>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);
	bool isCollitionObjectWithObject(CGameObject* obj); 	// kiểm tra bằng AABB và Sweept AABB
	bool CheckAABB(CGameObject* obj);
};


