#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;
class CCamera
{
	float camWidth, camHeight;
	D3DXVECTOR2 mPosition; // vị trí của camera so với map
public:
	CCamera(float width, float height) { this->camWidth = width; this->camHeight = height; mPosition = D3DXVECTOR2(0, 0); }

	void SetPosition(float x, float y) { this->mPosition = D3DXVECTOR2(x, y); }
	D3DXVECTOR2 GetPosition() { return this->mPosition; }

	RECT GetBound();
	RECT GetLockBound();

	float GetXCam() {
		return this->mPosition.x;
	}
	float GetYCam() {
		return this->mPosition.y;
	}

	D3DXVECTOR2 Transform(float, float);

	void Update(D3DXVECTOR2 mainPlayerPos, D3DXVECTOR2 mapPos, D3DXVECTOR2 mapDimen);

	D3DXVECTOR2 CamToWorld(float x, float y);
	D3DXVECTOR2 WorldToCam(float x, float y);

	float GetWidth() { return camWidth; }
	float GetHeight() { return camHeight; }
	~CCamera(){}
};
