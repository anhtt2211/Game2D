#include "Texture.h"

CTexture::CTexture(LPCSTR filePath, int R, int G, int B)
{
	
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);
	if (result != D3D_OK)
	{
		return;
	};

	this->width = info.Width;
	this->height = info.Height;
	this->column = 1;
	this->row = 1;

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileExA(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(R, G, B),
		&info,
		NULL,
		&Texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString("[ERROR] CreateTextureFromFile failed\n");
		return;
	}
}

CTexture::CTexture()
{
	this->Texture = NULL;
}
CTexture::~CTexture()
{
	if (this->Texture != NULL)
		this->Texture->Release();
}