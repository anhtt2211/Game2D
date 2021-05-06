#include "SceneManager.h"
SceneManager* SceneManager::__instance = NULL;
SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {

}

SceneManager* SceneManager::GetInstance() {
	if (__instance == NULL) {
		__instance = new SceneManager();
	}

	return __instance;
}

void SceneManager::SetScene(Scene* scene) {
	Scene* temp = this->_scene;
	this->_scene = scene;
	delete (temp);
	temp = nullptr;
}

void SceneManager::KeyState(BYTE* state) {
	this->_scene->KeyState(state);
}

void SceneManager::OnKeyDown(int keycode) {
	this->_scene->OnKeyDown(keycode);
}

void SceneManager::OnKeyUp(int keycode) {
	this->_scene->OnKeyUp(keycode);
}

void SceneManager::LoadResources() {
	this->_scene->LoadResouces();
}

void SceneManager::Update(DWORD dt) {
	this->_scene->Update(dt);
}

void SceneManager::Render() {
	this->_scene->Render();
}

Scene* SceneManager::GetScene() {
	return this->_scene;
}