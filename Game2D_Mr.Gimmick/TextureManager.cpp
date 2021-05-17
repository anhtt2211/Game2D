#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "TextureManager.h"
#include "Game.h"

CTextureManager* CTextureManager::__instance = NULL;

CTextureManager::CTextureManager()
{
	LoadResources();
}

CTextureManager* CTextureManager::GetInstance() {
	if (__instance == NULL) {
		__instance = new CTextureManager();
	}
	return __instance;
}

void CTextureManager::AddTextures(int id, CTexture* tex)
{
	arrTextures[id] = tex;
}

CTexture* CTextureManager::GetTexture(unsigned int i)
{
	return arrTextures[i];
}
void CTextureManager::LoadResources()
{
	AddTextures(ID_TEX_MAP1, new CTexture(PATH_TEX_MAP1, 9, 8, 72));
	AddTextures(ID_TEX_MAP2, new CTexture(PATH_TEX_MAP2));
	AddTextures(ID_TEX_GIMMICK, new CTexture(PATH_TEX_GIMMICK, 1, 1, 1, 0, 0, 255));
	AddTextures(ID_TEX_GOOMBA, new CTexture(PATH_TEX_GOOMBA, 1, 1, 1, 57, 189, 255));
	//AddTextures(ID_TEX_BRICK, new CTexture(PATH_TEX_BRICK, 1, 1, 1, 0, 0, 0));
}