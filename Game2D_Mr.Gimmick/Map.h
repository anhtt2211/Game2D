#ifndef _MAP_H_
#define _MAP_H_

#include <Windows.h>
#include "Sprite.h"
#include "TexturesManager.h"
#include <vector>
#include "Debug.h"

#define GIMMICK_TEXTURE_PATH "./Resources/Images/Gimmick/Gimmick.png"
#define MAP1_TEXTURE_PATH "./Resources/Images/Gimmick/bg.png"

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