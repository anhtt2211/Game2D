#ifndef _TEXTTURESMANAGER_H_
#define _TEXTTURESMANAGER_H_


#include <unordered_map>
#include <d3dx9.h>
#include "Textures.h"

using namespace std;
#define ID_TEX_MAP1 1
#define ID_TEX_MAP2 2
#define ID_TEX_GIMMICK 3

#define PATH_TEX_MAP1 "./Resources/tiles.png"
#define PATH_TEX_MAP2
#define PATH_TEX_GIMMICK "./Resources/Gimmick.png"
/*
	Manage texture database
*/
class CTexturesManger
{
	static CTexturesManger* __instance;

	unordered_map<int, CTexture*> arrTextures;

public:
	CTexturesManger();
	void AddTextures(int id, CTexture* tex);
	void LoadResources();
	CTexture* GetTexture(unsigned int i);

	static CTexturesManger* GetInstance();
};
#endif