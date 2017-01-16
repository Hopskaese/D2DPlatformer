#pragma once

#include <vector>

#include "Graphics.h"
#include "Map.h"
#include "HPTimer.h"

#define VK_KEY_A 0x41
#define VK_KEY_D 0x44



class GameController
{
	Graphics			*m_pGraphics;
	Map					*m_pMap;
	HPTimer				*m_pHPTimer;

	Player				*m_pMainPlayer;

	bool				m_bActive;

	D2D1_POINT_2F		m_D2D1PFLastCenter;

public:
	GameController(HWND hWnd);
	~GameController();

	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void Update();
	void Render();

	void OnJump();
	void OnRunStop();
	void OnMoveLeft(double dt);
	void OnMoveRight(double dt);

	void Gravity(Player *pPlayer, double dt);
	Brick *FindFloor(Player *pPlayer, double dt = 0);

	D2D1_POINT_2F GetCenter();

	bool IsGrahpics() { return m_pGraphics != NULL; }
};