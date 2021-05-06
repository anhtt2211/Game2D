#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Grid.h"
#include "Scene.h"
#include "TextureManager.h"
#include "Gimmick.h"

#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 240

class SceneGame : public Scene
{
private:
	CGimmick* gimmick;
	CCamera* camera;
	Grid* grid;

	vector <CGameObject*> listObj;
	vector <CGameObject*> listEnemy;
public:
	SceneGame();
	~SceneGame();

	void KeyState(BYTE* state);
	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);
	void LoadResources();

	void InitGame();
	void ResetResource();

	void Update(DWORD dt);
	void Render();

	void LoadMap();
};

