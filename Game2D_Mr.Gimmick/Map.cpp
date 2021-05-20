#include "Map.h"
#include <fstream>
void CMap::LoadMap(int id)
{
	switch (id)
	{
	case ID_TEX_MAP1:
		ReadMap(PATH_TILEMAP1_TXT);
		break;
	case ID_TEX_MAP2:
		ReadMap(PATH_TILEMAP2_TXT);
		break;
	case ID_TEX_MAP7:
		ReadMap(PATH_TILEMAP7_TXT);
		break;
	default:
		break;
	}
	_texture = CTextureManager::GetInstance()->GetTexture(id);
	_texture->SetColumn(this->ColumnTile);
	_texture->SetRow(this->RowTile);
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
			float x = _texture->GetFrameWidth() * j;
			float y = _texture->GetFrameHeight() * (i+1);
			if (i >= 0 && i < RowMap && j >= 0 && j < ColumnMap)
				_sprite->DrawFrame(TileMap[RowMap - 1 - i][j], x, y);
		}
	}
}
