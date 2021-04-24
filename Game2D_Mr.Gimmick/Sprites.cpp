#include "Sprites.h"

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex) {
	LPSPRITE sprite = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = sprite;
}

LPSPRITE CSprites::Get(int id) {
	return sprites[id];
}

CSprites* CSprites::GetInstance() {
	if (__instance == NULL) {
		__instance = new CSprites();
	}

	return __instance;
}