#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#define WINDOW_CLASS_NAME "WindowClassName"
#define WINDOW_TITLE "Mr.Gimmick"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

#define MAX_FRAME_RATE 120

LPDIRECT3D9 d3d = NULL;						// Direct3D handle
LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

LPDIRECT3DSURFACE9 backBuffer = NULL;
int BackBufferWidth = 0;
int BackBufferHeight = 0;

LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D images 

LPDIRECT3DTEXTURE9 texGimmick;
#define GIMMICK_TEXTURE_PATH "./Resources/Images/Gimmick/Gimmick.png"

#define	GIMMICK_START_X 30.0f
#define	GIMMICK_START_Y 10.0f
#define	GIMMICK_START_VX 0.2f
#define	GIMMICK_WIDTH 16.0f


//#define _W(x)  __W(x)
//#define __W(x)  L##x\
//
//#define VA_PRINTS(s) {				\
//		va_list argp;				\
//		va_start(argp, fmt);		\
//		vswprintf_s(s, fmt, argp);	\
//		va_end(argp);				\
//}	
//
//void DebugOut(wchar_t* fmt, ...)
//{
//	wchar_t s[4096];
//	VA_PRINTS(s);
//	OutputDebugString(s);
//}

void InitDirectX(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	// retrieve window width & height so that we can create backbuffer height & width accordingly 
	RECT r;
	GetClientRect(hWnd, &r);

	BackBufferWidth = r.right + 1;
	BackBufferHeight = r.bottom + 1;

	d3dpp.BackBufferHeight = BackBufferHeight;
	d3dpp.BackBufferWidth = BackBufferWidth;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,			// use default video card in the system, some systems have more than one video cards
		D3DDEVTYPE_HAL,				// HAL = Hardware Abstraction Layer - a "thin" software layer to allow application to directly interact with video card hardware
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		//DebugOut(L"[ERROR] CreateDevice failed\n %s %d", __FILE__, __LINE__);
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	//Initialize Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	//DebugOut("[INFO] InitDirectX OK\n");
}

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
	HRESULT result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		GIMMICK_TEXTURE_PATH,					// Path to the image to load
		D3DX_DEFAULT_NONPOW2, 				// Auto texture width (get from file)
		D3DX_DEFAULT_NONPOW2, 				// Auto texture height (get from file)
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 255),		// Transparent color
		NULL,
		NULL,
		&texGimmick);

	if (result != D3D_OK)
	{
		//DebugOut(L"[ERROR] CreateTextureFromFileEx %s failed\n", BRICK_TEXTURE_PATH);
		return;
	}

	//DebugOut(L"[INFO] Texture loaded Ok: %s \n", BRICK_TEXTURE_PATH);
}
void Update(DWORD dt)
{

}

/*
	Render a frame
	IMPORTANT: world status must NOT be changed during rendering
*/

void Render()
{
	if (d3ddv->BeginScene())
	{
		// Clear the whole window with a color
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXVECTOR3 p(GIMMICK_START_X, GIMMICK_START_Y, 0);
		RECT r;
		r.left = 122;
		r.top = 71;
		r.right = 142;
		r.bottom = 101;
		spriteHandler->Draw(texGimmick, &r, NULL, &p, D3DCOLOR_WHITE);

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
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

void CleanUp()
{
	if (texGimmick != NULL) texGimmick->Release();
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL)backBuffer->Release();
	if (d3ddv != NULL)d3ddv->Release();
	if (d3d != NULL)d3d->Release();
	//DebugOut(L"[INFO] Cleanup Ok\n");
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (hwnd == 0) return 0;

	InitDirectX(hwnd);
	LoadResources();
	Run();
	CleanUp();
	return 0;
}