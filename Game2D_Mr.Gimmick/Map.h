#ifndef _MAP_H_
#define _MAP_H_

#include <Windows.h>
#include "Sprite.h"
#include "TextureManager.h"
#include <vector>
#include "Debug.h"

#define PATH_TILEMAP1_TXT "Resources/Map/Level1/TileMap_1.txt"
#define PATH_TILEMAP2_TXT "Resources/Map/Level2/TileMap_2.txt"
#define PATH_TILEMAP7_TXT "Resources/Map/Level7/TileMap_7.txt"

class CMap
{
private:
	CTexture* _texture;
	CSprite* _sprite;
	int ColumnTile, RowTile, TotalTiles;
	int ColumnMap, RowMap;
	vector<vector<int>> TileMap;
public:
	CMap() {}
	~CMap(){}
	void LoadMap(int id);
	void RenderMap(CCamera* cam);
	void ReadMap(LPCSTR filePath);
};
#endif