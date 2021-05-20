#include "Camera.h"
#include "Debug.h"
#include "Gimmick.h"
RECT CCamera::GetBound()
{
	RECT bound;
	bound.left = mPosition.x;
	bound.right = bound.left + camWidth - 1;
	bound.top = mPosition.y;
	bound.bottom = bound.top - camHeight - 1;
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
	RECT lockBound = GetLockBound();
	float lastX, lastY;

	float t = lockBound.top;
	//calculate cam X
	if (mainPlayerPos.x >= lockBound.left && mainPlayerPos.x <= lockBound.right)
	{
		lastX = mPosition.x;
	}
	else if (mainPlayerPos.x < lockBound.left)
	{
		lastX = mPosition.x - (lockBound.left - mainPlayerPos.x);
	}
	else
	{
		lastX = mPosition.x + (mainPlayerPos.x - lockBound.right);
	}
	//calculate cam Y
	if (mainPlayerPos.y >= lockBound.bottom && mainPlayerPos.y <= lockBound.top)
	{	
		lastY = mPosition.y;
	}
	else if (mainPlayerPos.y < lockBound.bottom)
	{
		lastY = mPosition.y - (lockBound.bottom - mainPlayerPos.y);
	}
	else
	{
		lastY = mPosition.y + (mainPlayerPos.y - lockBound.top);
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
	//DebugOutTitle("%f, %f, %f", lastY,  (float)lockBound.bottom,(float)lockBound.	top ); 
}

D3DXVECTOR2 CCamera::Transform(float x, float y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._31 = -(int)mPosition.x;
	matrix._32 = (int)mPosition.y;

	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	D3DXVECTOR2 result = D3DXVECTOR2(MatrixResult.x, MatrixResult.y);
	return result;
}
