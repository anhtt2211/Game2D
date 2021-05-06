#include "Grid.h"

Grid::Grid() {

}

Grid::~Grid() {
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++) {
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++) {
			cells[i][j].clear();
		}
	}
}

void Grid::SetFile(char* filePath) {
	this->filePath = filePath;
}

void Grid::ReloadGrid() {
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++) {
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++) {
			cells[i][j].clear();
		}
	}

	int id, type, direction, w, h, model, n;
	float x, y;

	ifstream input(filePath, ios::in);
	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> id >> type >> direction >> x >> y >> w >> h >> model;
		this->Insert(id, type, direction, x, y, w, h);
	}
	input.close();
}

CGameObject* Grid::GetNewObject(int type, float x, float y, int w, int h, int Model) {

	return NULL;
}

void Grid::GetListObject(vector<CGameObject*>& listObj, CCamera* camera) {
	listObj.clear();

	unordered_map<int, CGameObject*> mapObject;

	int left = (int)((camera->GetXCam() + 1) / GRID_CELL_WIDTH);
	int top = (int)((camera->GetYCam() + 1) / GRID_CELL_HEIGHT);
	int right = (int)((camera->GetXCam() + camera->GetWidth() - 1) / GRID_CELL_WIDTH);
	int bottom = (int)((camera->GetYCam() + camera->GetHeight() - 1) / GRID_CELL_HEIGHT);

	for (int i = top; i <= bottom; i++) {
		for (int j = left; j <= right; j++) {
			for (UINT k = 0; k < cells[i][j].size(); k++) {
				if (cells[i][j].at(k)->GetHealth() > 0) {
					if (mapObject.find(cells[i][j].at(k)->GetID()) == mapObject.end()) // ko tìm thấy
						mapObject[cells[i][j].at(k)->GetID()] = cells[i][j].at(k);
				}
				else {

				}
			}
		}
	}

	for (auto& x : mapObject)
	{
		listObj.push_back(x.second);
	}
}

void Grid::Insert(int id, int type, int direction, float x, float y, int w, int h) {
	int left = (int)(x / GRID_CELL_WIDTH);
	int top = (int)(y / GRID_CELL_HEIGHT);
	int right = (int)((x + w) / GRID_CELL_WIDTH);
	int bottom = (int)((y + h) / GRID_CELL_HEIGHT);

	CGameObject* obj = new CGameObject();
	if (obj == NULL) {
		return;
	}

	obj->SetID(id);
	obj->SetDirection(direction);

	for (int i = top; i <= bottom; i++) {
		for (int j = left; j <= right; j++) {
			cells[i][j].push_back(obj);
		}
	}
}