#include "Sprite.h"
#include "Game.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void CSprite::Draw(float x, float y)
{
	CGame* game = CGame::GetInstance();
	if (x > 0)
	{
		game->DrawFlip(x, y, texture, left, top, right, bottom, 1.0f, 1.0f);
	}
	else
	{
		game->DrawFlip(x, y, texture, left, top, right, bottom, -1.0f, 1.0f);
	}
}


CSpriteManager* CSpriteManager::__instance = NULL;

void CSpriteManager::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex) {
	LPSPRITE sprite = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = sprite;
}

LPSPRITE CSpriteManager::Get(int id) {
	return sprites[id];
}

CSpriteManager* CSpriteManager::GetInstance() {
	if (__instance == NULL) {
		__instance = new CSpriteManager();
	}

	return __instance;
}

void CAnimation::Add(int spriteID, DWORD time) {
	int t = time;
	if (time == 0) {
		t = this->defaultTime;
	}

	LPSPRITE sprite = CSpriteManager::GetInstance()->Get(spriteID);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y) {
	DWORD now = GetTickCount();
	if (currentFrame == -1) {
		currentFrame = 0;
		lastFrameTime = now;
	}
	else {
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t) {
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0;
			}
		}
	}
	frames[currentFrame]->GetSprite()->Draw(x, y);
}


CAnimationManager* CAnimationManager::__instance = NULL;

CAnimationManager* CAnimationManager::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimationManager();
	return __instance;
}

void CAnimationManager::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimationManager::Get(int id)
{
	return animations[id];
}