#include "Camera.h"
#include "Debug.h"
#include "Gimmick.h"
RECT CCamera::GetBound()
{
	RECT bound;
	bound.left = mPosition.x;
	bound.right = bound.left + camWidth - 1;
	bound.top = mPosition.y;
	bound.bottom = bound.top + camHeight + 1;
	return bound;
}
RECT CCamera::GetLockBound()
{
	RECT bound;
	bound.left = mPosition.x + camWidth / 3.0f;
	bound.right = bound.left + camWidth / 5.0f;
	bound.top = mPosition.y - camHeight / 4.0f;
	bound.bottom = bound.top - camHeight / 5.0f;
	return bound;
}
void CCamera::Update(D3DXVECTOR2 mainPlayerPos, D3DXVECTOR2 mapPos, D3DXVECTOR2 mapDimen)
{
	//mainPlayerPos la vi tri cua main player so voi world
	RECT r = GetLockBound();
	float lastX, lastY;

	float t = r.top;
	//calculate cam X
	if (mainPlayerPos.x >= r.left && mainPlayerPos.x <= r.right)
	{
		lastX = mPosition.x;
	}
	else if (mainPlayerPos.x < r.left)
	{
		lastX = mPosition.x - (r.left - mainPlayerPos.x);
	}
	else
	{
		lastX = mPosition.x + (mainPlayerPos.x - r.right);
	}
	//calculate cam Y
	if (mainPlayerPos.y >= r.bottom && mainPlayerPos.y <= r.top)
	{	
		lastY = mPosition.y;
	}
	else if (mainPlayerPos.y < r.bottom)
	{
		lastY = mPosition.y - (r.bottom - mainPlayerPos.y);
	}
	else
	{
		lastY = mPosition.y + (mainPlayerPos.y - r.top);
	}

	//Gioi han x, y
	if (lastX < mapPos.x)
	{
		lastX = mapPos.x;
	}
	else if (lastX > mapPos.x + mapDimen.x - camWidth)
	{
		lastX = mapPos.x + mapDimen.x - camWidth;
	}

	if (lastY > mapPos.y)
	{
		lastY = mapPos.y;
	}
	else if (lastY < mapPos.y - mapDimen.y + camHeight)
	{
		lastY = mapPos.y - mapDimen.y + camHeight;
	}
	this->SetPosition(lastX, lastY);
	//DebugOutTitle("%f, %f, %f", mainPlayerPos.y,  (float)r.bottom,(float)r.top ); 
}

D3DXVECTOR2 CCamera::CamToWorld(float x, float y)
{
	float World_X = x + mPosition.x;
	float World_Y = mPosition.y - y;
	return D3DXVECTOR2(World_X, World_Y);
}
D3DXVECTOR2 CCamera::WorldToCam(float x, float y)
{
	float cam_x, cam_y; // vi tri can chuyen qua camera
	cam_x = x - mPosition.x;
	cam_y = mPosition.y - y;
	return D3DXVECTOR2(cam_x, cam_y);
}