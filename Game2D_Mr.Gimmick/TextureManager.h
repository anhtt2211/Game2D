#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
	Manage texture database
*/
class CTextureManager
{
	static CTextureManager* __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	CTextureManager();
	void Add(int id, LPCSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static CTextureManager* GetInstance();
};