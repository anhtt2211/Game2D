
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#include "Game.h"
#include "Gimmick.h"
#include "TextureManager.h"
#include "CKeyEventHandler.h"
#include "Debug.h"
#include "Map.h"
#include "CKeyEventHandler.h"
#include "Debug.h"
#include "ResourceManager.h"
#include "Goomba.h"
#include "Brick.h"
using namespace std;

#define WINDOW_CLASS_NAME "WindowClassName"
#define WINDOW_TITLE "Mr.Gimmick"

#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200,200,255)

#define MAX_FRAME_RATE 120

LPDIRECT3DTEXTURE9 texGimmick;
#define GIMMICK_TEXTURE_PATH "./Resources/Gimmick.png"

#define	GIMMICK_START_X 30.0f
#define	GIMMICK_START_Y 10.0f
#define	GIMMICK_START_VX 0.2f
#define	GIMMICK_WIDTH 16.0f

D3DXVECTOR2 mainPlayer;
D3DXVECTOR2 mapPos;
D3DXVECTOR2 mapDimen;

CGame* game;
CMap* map = new CMap();

CGimmick* gimmick;
CGoomba* goomba;

vector<LPGAMEOBJECT> objects;

class CKeyGimmickHandler : public CKeyEventHandler {
public:
	void OnKeyDown(int keycode) {
		switch (keycode)
		{
		case DIK_SPACE:
			gimmick->SetState(GIMMICK_STATE_JUMP);
		default:
			break;
		}
	}

	void OnKeyUp(int keycode){}
	void KeyState(BYTE* states) {
		if (game->IsKeyDown(DIK_RIGHT)) {
			gimmick->SetState(GIMMICK_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT)) {
			gimmick->SetState(GIMMICK_STATE_WALKING_LEFT);
		}
		else {
			gimmick->SetState(GIMMICK_STATE_IDLE);
		}
	}
};
CKeyGimmickHandler* keyHandler = new CKeyGimmickHandler();

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		//OutputDebugString("[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

void LoadResources()
{
	CSpriteManager* sprites = CSpriteManager::GetInstance();
	CAnimationManager* animations = CAnimationManager::GetInstance();
	CTexture* texGimmick = CTextureManager::GetInstance()->GetTexture(ID_TEX_GIMMICK);
	CTexture* texGoomba = CTextureManager::GetInstance()->GetTexture(ID_TEX_GOOMBA);
	CTexture* texBrick = CTextureManager::GetInstance()->GetTexture(ID_TEX_BRICK);
	
#pragma region gimmick
	//gimmick walking right
	sprites->Add(10001, 0, 23, 20, 45, texGimmick);
	sprites->Add(10002, 19, 23, 39, 45, texGimmick);
	sprites->Add(10003, 37, 23, 57, 45, texGimmick);
	sprites->Add(10004, 56, 23, 76, 45, texGimmick);
	sprites->Add(10005, 77, 23, 97, 45, texGimmick);
	sprites->Add(10006, 97, 23, 117, 45, texGimmick);
	//gimmick walking left
	sprites->Add(10010, 0, 23, 20, 45, texGimmick);
	sprites->Add(10011, 19, 23, 39, 45, texGimmick);
	sprites->Add(10012, 37, 23, 57, 45, texGimmick);
	sprites->Add(10013, 56, 23, 76, 45, texGimmick);
	sprites->Add(10014, 77, 23, 97, 45, texGimmick);
	sprites->Add(10015, 97, 23, 117, 45, texGimmick);
	//gimmick jumping right
	sprites->Add(10020, 1, 45, 20, 71, texGimmick);
	sprites->Add(10021, 20, 45, 40, 71, texGimmick);

	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	animations->Add(502, ani);	//gimmick walking right

	ani = new CAnimation(100);
	ani->Add(10010);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	ani->Add(10015);
	animations->Add(503, ani);	//gimmick walking left

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(500, ani);	//gimmick idle right

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(501, ani);	//gimmick idle left

	ani = new CAnimation(100);
	ani->Add(10020);
	ani->Add(10021);
	animations->Add(504, ani);	//gimmick jumping right

	ani = new CAnimation(100);
	ani->Add(10020);
	ani->Add(10021);
	animations->Add(505, ani);	//gimmick jumping left

	gimmick = new CGimmick();
	gimmick->AddAnimation(500);	//idle right
	gimmick->AddAnimation(501);	//idle left
	gimmick->AddAnimation(502);	//walking right
	gimmick->AddAnimation(503);	//walking left
	gimmick->AddAnimation(504);	//jumping right
	gimmick->AddAnimation(505);	//jumping left

	gimmick->SetPosition(100.0f, 150.0f);
	objects.push_back(gimmick);
#pragma endregion

#pragma region goomba
	//goomba walk
	sprites->Add(20001, 1, 0, 1 + 18, 18, texGoomba);
	sprites->Add(20002, 19, 0, 19 + 18, 18, texGoomba);
	sprites->Add(20003, 37, 0, 37 + 18, 18, texGoomba);

	ani = new CAnimation(100);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(701, ani);

	for (int i = 0; i < 4; i++) {
		goomba = new CGoomba();
		goomba->AddAnimation(701);
		goomba->SetPosition(200.0f + i * 60, 150.0f);
		goomba->SetState(GOOMBA_STATE_WALKING);
		objects.push_back(goomba);
	}
#pragma endregion

//#pragma region brick
//	sprites->Add(30001, 0, 32, 0 + 16, 32 + 16, texBrick);
//
//	ani = new CAnimation(100);
//	ani->Add(30001);
//	animations->Add(801, ani);
//	for (int i = 0; i < 30; i++)
//	{
//		CBrick* brick = new CBrick();
//		brick->AddAnimation(801);
//		brick->SetPosition(i, 150.0f);
//		objects.push_back(brick);
//	}
//#pragma endregion
}

void Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	//gimmick->Update(dt);
	float x = gimmick->GetX();
	float y = gimmick->GetY();
	mainPlayer = D3DXVECTOR2(x, y);
	mapPos = D3DXVECTOR2(0, 768);
	mapDimen = D3DXVECTOR2(2048, 768);
	game->UpdateCam(mainPlayer, mapPos, mapDimen);
}
	
/*
	Render a frame
	IMPORTANT: world status must NOT be changed during rendering
*/

void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	if (d3ddv->BeginScene() == D3D_OK)
	{
		// Clear the whole window with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		
		map->RenderMap(game->GetCamera());
		/*gimmick->Render();
		goomba->Render();*/
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Render();
		}

		spriteHandler->End();
		d3ddv->EndScene();
	}
	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	game = CGame::GetInstance();
	game->Init(hwnd);
	SetDebugWindow(hwnd);
	map->LoadMap(ID_TEX_MAP1);
	game->InitKeyboard(keyHandler);
	LoadResources();
	Run();

	return 0;
}