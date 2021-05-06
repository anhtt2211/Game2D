#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Camera.h"
#include <iostream>
#include <fstream>

#define GRID_CELL_MAX_ROW 20 // số dòng tối đa;
#define GRID_CELL_MAX_COLUMN 100 // số cột tối đa

#define GRID_CELL_WIDTH (SCREEN_WIDTH/4.0f)
#define GRID_CELL_HEIGHT (SCREEN_HEIGHT/4.0f)

using namespace std;

class Grid
{
private:
	vector<CGameObject*> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN];
	char* filePath;

public:
	Grid();
	~Grid();

	void SetFile(char* filePath);
	void ReloadGrid();

	CGameObject* GetNewObject(int type, float x, float y, int w, int h, int Model);
	void GetListObject(vector<CGameObject*>& ListObj, CCamera* camera);
	void Insert(int id, int type, int direction, float x, float y, int w, int h);
};

