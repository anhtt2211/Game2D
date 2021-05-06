#include "SceneGame.h"

SceneGame::SceneGame() {
	LoadResources();
}

SceneGame::~SceneGame() {

}

void SceneGame::KeyState(BYTE* state) {

}

void SceneGame::OnKeyDown(int keycode) {

}

void SceneGame::OnKeyUp(int keycode) {

}

void SceneGame::LoadResources() {
	CTextureManager* _textureManager = CTextureManager::GetInstance();

	this->grid = new Grid();
	this->camera = new CCamera(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->gimmick = new CGimmick();
}

void SceneGame::InitGame() {

}

void SceneGame::ResetResource() {

}

void SceneGame::Update(DWORD dt) {

}

void SceneGame::Render() {

}

void SceneGame::LoadMap() {

}