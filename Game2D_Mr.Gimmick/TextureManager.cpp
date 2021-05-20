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
	AddTextures(ID_TEX_MAP1, new CTexture(PATH_TEX_MAP1));
	AddTextures(ID_TEX_MAP2, new CTexture(PATH_TEX_MAP2));
	AddTextures(ID_TEX_MAP7, new CTexture(PATH_TEX_MAP7));
	AddTextures(ID_TEX_GIMMICK, new CTexture(PATH_TEX_GIMMICK, 0, 0, 255));
}