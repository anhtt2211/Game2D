#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "Game.h"
#include <d3dx9.h>
class CTexture
{
private:
	int width, height;
	int column, row;

public:
	LPDIRECT3DTEXTURE9 Texture;

	int GetWidth() { return this->width; }
	int GetHeight() { return this->height; }
	int GetColumn() { return this->column; }
	int GetRow() { return this->row; }
	void SetColumn(int col) { this->column = col; }
	void SetRow(int row) { this->row = row; }
	int GetFrameWidth() { return this->width / this->column; }
	int GetFrameHeight() { return this->height / this->row; }

	CTexture(LPCSTR filePath, int R = 255, int G = 0, int B = 255);
	CTexture();
	~CTexture();
};
#endif