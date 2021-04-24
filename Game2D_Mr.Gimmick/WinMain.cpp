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
#include "Textures.h"
#include "CKeyEventHandler.h"

#define WINDOW_CLASS_NAME "WindowClassName"
#define WINDOW_TITLE "Mr.Gimmick"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200,200,255)

#define MAX_FRAME_RATE 120

int BackBufferWidth = 0;
int BackBufferHeight = 0;

LPDIRECT3DTEXTURE9 texGimmick;
#define GIMMICK_TEXTURE_PATH "./Resources/Images/Gimmick/Gimmick.png"

#define	GIMMICK_START_X 30.0f
#define	GIMMICK_START_Y 10.0f
#define	GIMMICK_START_VX 0.2f
#define	GIMMICK_WIDTH 16.0f

#define ID_TEX_GIMMICK 0

CGame* game;
CGimmick* gimmick;


class CKeyGimmickHandler : public CKeyEventHandler {
public:
	void OnKeyDown(int keycode) {
		if (game->IsKeyDown(DIK_SPACE)) {
			gimmick->OnKeyDown(GIMMICK_STATE_JUMP);
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
	CTextures* textures = CTextures::GetInstance();
	textures->Add(ID_TEX_GIMMICK, GIMMICK_TEXTURE_PATH, D3DCOLOR_XRGB(0, 0, 255));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texGimmick = textures->Get(ID_TEX_GIMMICK);

	//walking right
	sprites->Add(10001, 0, 23, 20, 45, texGimmick);
	sprites->Add(10002, 19, 23, 39, 45, texGimmick);
	sprites->Add(10003, 37, 23, 57, 45, texGimmick);
	sprites->Add(10004, 56, 23, 76, 45, texGimmick);
	sprites->Add(10005, 77, 23, 97, 45, texGimmick);
	sprites->Add(10006, 97, 23, 117, 45, texGimmick);
	//walking left


	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	animations->Add(500, ani);	//walking right

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(501, ani);	//idle right


	gimmick = new CGimmick();
	CGimmick::AddAnimation(501);	//idle right
	CGimmick::AddAnimation(500);	//walking right

	gimmick->SetPosition(0.0f, 100.0f);
}

void Update(DWORD dt)
{
	gimmick->Update(dt);
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
	if (d3ddv->BeginScene())
	{
		// Clear the whole window with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXVECTOR3 p(GIMMICK_START_X, GIMMICK_START_Y, 0);
		
		gimmick->Render();

		//DebugOutTitle(L"%s (%0.1f,%0.1f) v:%0.1f", WINDOW_TITLE, GIMMICK_START_X, GIMMICK_START_Y, GIMMICK_START_VX);

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
	

	game->InitKeyboard(keyHandler);


	LoadResources();
	Run();

	return 0;
}