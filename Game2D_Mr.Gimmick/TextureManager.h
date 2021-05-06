#ifndef _TEXTTURESMANAGER_H_
#define _TEXTTURESMANAGER_H_


#include <unordered_map>
#include <d3dx9.h>
#include "Texture.h"

using namespace std;
#define ID_TEX_MAP1 1
#define ID_TEX_MAP2 2
#define ID_TEX_GIMMICK 10
#define ID_TEX_ENEMY 20

#define ENEMY_TEX_PATH "./Resources/Images/Enemies_Bosses/Boss.png"
#define PATH_TEX_MAP1 "./Resources/tiles.png"
#define PATH_TEX_MAP2
#define PATH_TEX_GIMMICK "./Resources/Gimmick.png"
/*
	Manage texture database
*/
class CTextureManager
{
	static CTextureManager* __instance;

	unordered_map<int, CTexture*> arrTextures;

public:
	CTextureManager();
	void AddTextures(int id, CTexture* tex);
	void LoadResources();
	CTexture* GetTexture(unsigned int i);

	static CTextureManager* GetInstance();
};
#endif