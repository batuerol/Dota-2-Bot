#include "WindowHelper.h"
#include <iostream>

namespace WindowHelper
{
	void MoveMouse(HWND hWnd, WORD x /* = 0 */, WORD y /* = 0 */)
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dx = (rect.left + x) * (0xFFFF / 1920);
		input.mi.dy = (rect.top + y) * (0xFFFF / 1080);
		input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
		input.mi.time = 0;
		input.mi.dwExtraInfo = 0;
		input.mi.mouseData = 0;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(INPUT_DELAY);
	}

	void LeftClick(HWND hWnd, WORD x, WORD y)
	{		
		LPARAM lParam = MAKELPARAM(x, y);					
		PostMessage(hWnd, WM_MOUSEMOVE, 0, lParam);
		Sleep(INPUT_DELAY); // FUCK SOURCE2
		PostMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
		PostMessage(hWnd, WM_LBUTTONUP, 0, lParam);

		Sleep(INPUT_DELAY);
	}

	void RightClick(HWND hWnd, WORD x, WORD y)
	{
		LPARAM lParam = MAKELPARAM(x, y);

		PostMessage(hWnd, WM_MOUSEMOVE, 0, lParam);
		Sleep(INPUT_DELAY);

		PostMessage(hWnd, WM_RBUTTONDOWN, MK_RBUTTON, lParam);
		PostMessage(hWnd, WM_RBUTTONUP, 0, lParam);
		Sleep(INPUT_DELAY);
	}

	void SendKey(HWND hWnd, DWORD vkey)
	{
		WORD wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
		PostMessage(hWnd, WM_KEYDOWN, vkey, 1 | (wScan << 16));
		PostMessage(hWnd, WM_KEYUP, vkey, 1 | (wScan << 16) | (0x1 << 30));
		Sleep(INPUT_DELAY);
	}
}