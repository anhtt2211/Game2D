#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Sprite.h"

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;
public:
	CAnimationFrame(LPSPRITE sprite, DWORD time) {
		this->sprite = sprite;
		this->time = time;
	}
};

