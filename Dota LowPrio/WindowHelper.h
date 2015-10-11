#pragma once
#include <Windows.h>

namespace WindowHelper
{
	const int INPUT_DELAY = 600;

	void MoveMouse(HWND hWnd, WORD x = 0, WORD y = 0);
	void LeftClick(HWND hWnd, WORD x, WORD y);
	void RightClick(HWND hWnd, WORD x, WORD y);
	void SendKey(HWND hWnd, DWORD vkey);
}