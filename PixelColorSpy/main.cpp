#include <Windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	char* szTargetWindow = (char*)malloc(7);
	strcpy_s(szTargetWindow, 7, "Dota 2");

	if (argc > 1)
	{
		size_t temp = strlen(argv[1]);
		if (strlen(szTargetWindow) < temp)
		{
			szTargetWindow = (char*)realloc(szTargetWindow, temp + 1);
			strcpy_s(szTargetWindow, temp, argv[1]);
		}
	}

	HWND hDotaWnd = FindWindow(NULL, szTargetWindow);

	if (!hDotaWnd)
	{			
		MessageBox(NULL, "Window couldn't be found.", "Error!", MB_OK);
		return -1;
	}

	HDC hDC = GetDC(hDotaWnd);
	if (!hDC)
	{
		MessageBox(NULL, "Couldn't get device context.", "Error!", MB_OK);
		return -1;
	}

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO conBufferInfo;
	GetConsoleScreenBufferInfo(hStdOut, &conBufferInfo);
	COORD dwConPos = conBufferInfo.dwCursorPosition;

	while (true)
	{
		SetConsoleCursorPosition(hStdOut, dwConPos);

		RECT rect;
		POINT mousePos;

		GetClientRect(hDotaWnd, &rect);
		ClientToScreen(hDotaWnd, reinterpret_cast<LPPOINT>(&rect.left));
		GetCursorPos(&mousePos);

		POINT relativePoint = { mousePos.x - rect.left, mousePos.y - rect.top };
		COLORREF color = GetPixel(hDC, relativePoint.x, relativePoint.y);

		// Little hack to prevent absurd line ending.
		printf("(X, Y) : (%d, %d) - Color(RGB) : [0x%x] (%d, %d, %d)          \n", relativePoint.x, relativePoint.y, color, GetRValue(color), GetGValue(color), GetBValue(color));
		Sleep(100);
	}

	ReleaseDC(hDotaWnd, hDC);	
	return 0;
}
