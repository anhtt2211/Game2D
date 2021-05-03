
#include <Windows.h>
#include "Debug.h"

HWND _hwnd = NULL;

void DebugOut(const char* szFormat, ...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg, szFormat);
	_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);
	OutputDebugString(szBuff);
}

void DebugOutTitle(const char* fmt, ...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg, fmt);
	_vsnprintf_s(szBuff, sizeof(szBuff), fmt, arg);
	va_end(arg);
	SetWindowText(_hwnd, szBuff);
}

void SetDebugWindow(HWND hwnd)
{
	_hwnd = hwnd;
}
//////////////////////////////////////////