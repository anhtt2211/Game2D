#include "Map.h"
#include <fstream>
#define PATH_MAP1_TXT "Resources/tilemap_1new.txt"
void CMap::LoadMap(int id)
{
	switch (id)
	{
	case ID_TEX_MAP1:
		ReadMap(PATH_MAP1_TXT);
		break;
	default:
		break;
	}
	_texture = CTextureManager::GetInstance()->GetTexture(id);

	_sprite = new CSprite(_texture);
}
void CMap::ReadMap(LPCSTR filePath)
{
	ifstream fileIn(filePath, ios::in);
	fileIn >> RowMap >> ColumnMap >> RowTile >> ColumnTile >> TotalTiles;
	for (int i = 0; i < RowMap; i++)
	{
		vector<int> arrValues;
		for (int j = 0; j < ColumnMap; j++)
		{
			int tmp;
			fileIn >> tmp;
			arrValues.push_back(tmp);
		}
		TileMap.push_back(arrValues);
	}
	fileIn.close();
}
void CMap::RenderMap(CCamera* cam)
{
	int start_x = (int)cam->GetPosition().x / _texture->GetFrameWidth();
	int end_x = (int)(cam->GetPosition().x + cam->GetWidth()) / _texture->GetFrameWidth() + 1;
	int start_y = (int)cam->GetPosition().y / _texture->GetFrameHeight();
	int end_y = (int)(cam->GetPosition().y - cam->GetHeight()) / _texture->GetFrameHeight();

	for (int i = start_y; i >= end_y; i--)
	{
		for (int j = start_x; j <= end_x; j++)
		{
			float x = (float)(-(int)(cam->GetPosition().x) % _texture->GetFrameWidth() + _texture->GetFrameWidth() * (j - start_x));
			float y = (float)((int)(cam->GetPosition().y) % _texture->GetFrameHeight() + _texture->GetFrameHeight() * (start_y - i - 1));
			if (i >= 0 && i < RowMap && j >= 0 && j < ColumnMap)
				_sprite->DrawFrame(TileMap[RowMap - 1 - i][j], x, y + 1);
		}
	}
	//DebugOutTitle("%d, %d", (int)cam->GetPosition().x, colunm);
}
