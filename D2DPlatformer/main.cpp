#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <time.h>

#include "GameController.h"

GameController *g_pGameController = NULL;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (g_pGameController)
		return g_pGameController->MsgProc(hwnd, uMsg, wParam, lParam);

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	srand(time(nullptr));

	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);

	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "D2DPlatformer", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!hwnd) return -1;

	ShowWindow(hwnd, nCmdShow);

	g_pGameController = new GameController(hwnd);

	if (!g_pGameController->IsGrahpics())
	{
		delete g_pGameController;
		return -1;
	} 

	MSG msg;
	msg.message =  WM_NULL;

	while(msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&msg);
		else
		{
			g_pGameController->Update();
			g_pGameController->Render();
		}
	}

	delete g_pGameController;
	return 0;
}