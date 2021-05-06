#pragma once
#include "Scene.h"
#include "Camera.h"


class SceneManager
{
private:
	static SceneManager* __instance;
	Scene* _scene;
	SceneManager();
public:
	~SceneManager();

	static SceneManager* GetInstance();

	void SetScene(Scene* scene);

	Scene* GetScene();

	void KeyState(BYTE* state);
	void OnKeyDown(int keycode);
	void OnKeyUp(int keycode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();
};

