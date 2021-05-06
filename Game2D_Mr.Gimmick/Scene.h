#ifndef _SCENE_H_
#define _SCENE_H_

#include <Windows.h>
class Scene
{
public:
	Scene();

	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int keycode) = 0;
	virtual void OnKeyUp(int keycode) = 0;

	virtual void LoadResouces() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual ~Scene();
};

#endif