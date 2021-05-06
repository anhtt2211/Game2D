#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "TexturesManager.h"
#include "Game.h"

CTexturesManger* CTexturesManger::__instance = NULL;

CTexturesManger::CTexturesManger()
{
	LoadResources();
}

CTexturesManger* CTexturesManger::GetInstance() {
	if (__instance == NULL) {
		__instance = new CTexturesManger();
	}
	return __instance;
}

void CTexturesManger::AddTextures(int id, CTexture* tex)
{
	arrTextures[id] = tex;
}

CTexture* CTexturesManger::GetTexture(unsigned int i)
{
	return arrTextures[i];
}
void CTexturesManger::LoadResources()
{
	AddTextures(ID_TEX_MAP1, new CTexture(PATH_TEX_MAP1, 9, 8, 72));
	AddTextures(ID_TEX_MAP2, new CTexture(PATH_TEX_MAP2));
	AddTextures(ID_TEX_GIMMICK, new CTexture(PATH_TEX_GIMMICK, 1, 1, 1, 0, 0, 255));
}