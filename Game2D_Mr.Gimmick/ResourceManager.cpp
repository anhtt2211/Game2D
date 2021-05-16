#include "ResourceManager.h"
ResourceManager* ResourceManager::__instance = NULL;
ResourceManager::ResourceManager() {

}

ResourceManager* ResourceManager::GetInstance() {
	if (__instance == NULL) {
		__instance = new ResourceManager();
	}

	return __instance;
}

void ResourceManager::LoadResource() {
	//this->textures->Add(ID_TEX_GIMMICK, GIMMICK_TEXTURE_PATH, D3DCOLOR_XRGB(0, 0, 255));
	//this->textures->Add(ID_TEX_GOOMBA, ENEMY_TEXTURE_PATH, D3DCOLOR_XRGB(0, 0, 255));

	//LPDIRECT3DTEXTURE9 texGimmick = textures->Get(ID_TEX_GIMMICK);
	//LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_GOOMBA);

	//#pragma region ADD SPRITES GIMMICK
	////walking right
	//sprites->Add(10001, 0, 23, 20, 45, texGimmick);
	//sprites->Add(10002, 19, 23, 39, 45, texGimmick);
	//sprites->Add(10003, 37, 23, 57, 45, texGimmick);
	//sprites->Add(10004, 56, 23, 76, 45, texGimmick);
	//sprites->Add(10005, 77, 23, 97, 45, texGimmick);
	//sprites->Add(10006, 97, 23, 117, 45, texGimmick);
	////walking left
	//sprites->Add(10010, 0, 23, 20, 45, texGimmick);
	//sprites->Add(10011, 19, 23, 39, 45, texGimmick);
	//sprites->Add(10012, 37, 23, 57, 45, texGimmick);
	//sprites->Add(10013, 56, 23, 76, 45, texGimmick);
	//sprites->Add(10014, 77, 23, 97, 45, texGimmick);
	//sprites->Add(10015, 97, 23, 117, 45, texGimmick);
	////jumping right
	//sprites->Add(10020, 1, 45, 20, 71, texGimmick);
	//sprites->Add(10021, 20, 45, 40, 71, texGimmick);
	//#pragma endregion

	//#pragma region ADD SPRITES GIMMICK
	////walking right
	//sprites->Add(20000, 4, 63, 4 + 35, 63 + 35, texGimmick);
	//sprites->Add(20001, 41, 63, 41 + 35, 63 + 35, texGimmick);
	//sprites->Add(20002, 77, 63, 77 + 35, 63 + 35, texGimmick);
	//sprites->Add(20003, 113, 63, 113 + 35, 63 + 35, texGimmick);
	////walking left (flip)
	//sprites->Add(20010, 4, 63, 4 + 35, 63 + 35, texGimmick);
	//sprites->Add(20011, 41, 63, 41 + 35, 63 + 35, texGimmick);
	//sprites->Add(20012, 77, 63, 77 + 35, 63 + 35, texGimmick);
	//sprites->Add(20013, 113, 63, 113 + 35, 63 + 35, texGimmick);
	//#pragma endregion
	//LPANIMATION ani;

	//#pragma region ADD ANIMATION GIMMICK
	//ani = new CAnimation(100);
	//ani->Add(10001);
	//ani->Add(10002);
	//ani->Add(10003);
	//ani->Add(10004);
	//ani->Add(10005);
	//ani->Add(10006);
	//animations->Add(502, ani);	//walking right

	//ani = new CAnimation(100);
	//ani->Add(10010);
	//ani->Add(10011);
	//ani->Add(10012);
	//ani->Add(10013);
	//ani->Add(10014);
	//ani->Add(10015);
	//animations->Add(503, ani);	//walking left

	//ani = new CAnimation(100);
	//ani->Add(10001);
	//animations->Add(500, ani);	//idle right

	//ani = new CAnimation(100);
	//ani->Add(10001);
	//animations->Add(501, ani);	//idle left

	//ani = new CAnimation(100);
	//ani->Add(10020);
	//ani->Add(10021);
	//animations->Add(504, ani);	//jumping right

	//ani = new CAnimation(100);
	//ani->Add(10020);
	//ani->Add(10021);
	//animations->Add(505, ani);	//jumping left

	//#pragma endregion

	//#pragma region ADD ANIMATION ENEMY
	//ani = new CAnimation(100);
	//ani->Add(20000);
	//ani->Add(20001);
	//ani->Add(20002);
	//ani->Add(20003);
	//this->animations->Add(201, ani);	//walking right

	//ani = new CAnimation(100);
	//ani->Add(20010);
	//ani->Add(20011);
	//ani->Add(20012);
	//ani->Add(20013);
	//this->animations->Add(202, ani);	//walking left

	//#pragma endregion
}
