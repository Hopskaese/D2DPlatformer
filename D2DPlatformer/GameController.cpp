#include "GameController.h"

GameController::GameController(HWND hWnd)
{
	m_pGraphics = new Graphics();
	if (!m_pGraphics->Init(hWnd))
	{
		delete m_pGraphics;
		m_pGraphics = NULL;
	}

	m_pHPTimer = new HPTimer();

	m_bActive = true;

	m_D2D1PFLastCenter = D2D1::Point2F(0, 0);
	m_pMap = new Map(m_pGraphics);

	m_pMainPlayer = new Player(200, 200);

	m_pMainPlayer->m_pSprites[Player::PSPRITE_STAND][Player::DIRECTION::LEFT] =	new SpriteSheet(L"data\\player\\PlayerStandLeft.png",	m_pGraphics, 43, 60, 20);
	m_pMainPlayer->m_pSprites[Player::PSPRITE_STAND][Player::DIRECTION::RIGHT] =new SpriteSheet(L"data\\player\\PlayerStandRight.png",	m_pGraphics, 43, 60, 20);
	m_pMainPlayer->m_pSprites[Player::PSPRITE_RUN]	[Player::DIRECTION::LEFT] =	new SpriteSheet(L"data\\player\\PlayerRunLeft.png",		m_pGraphics, 43, 60, 20);
	m_pMainPlayer->m_pSprites[Player::PSPRITE_RUN]	[Player::DIRECTION::RIGHT] =new SpriteSheet(L"data\\player\\PlayerRunRight.png",	m_pGraphics, 43, 60, 20);
	m_pMainPlayer->m_pSprites[Player::PSPRITE_JUMP]	[Player::DIRECTION::LEFT] =	new SpriteSheet(L"data\\player\\PlayerJumpLeft.png",	m_pGraphics, 43, 60, 20, false);
	m_pMainPlayer->m_pSprites[Player::PSPRITE_JUMP]	[Player::DIRECTION::RIGHT] =new SpriteSheet(L"data\\player\\PlayerJumpRight.png",	m_pGraphics, 43, 60, 35, false);
	

	m_pMap->Add(m_pMainPlayer);
}

GameController::~GameController()
{
	if (m_pGraphics) delete m_pGraphics;
	if (m_pMap)		 delete m_pMap;
	if (m_pHPTimer)  delete m_pHPTimer;
}

LRESULT GameController::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	case WM_QUIT:
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			m_bActive = wParam != 0;
			if (!m_bActive) OnRunStop();
		}
		break;
	case WM_KEYDOWN:
		{
			if (wParam == VK_SPACE)
				OnJump();
		}
		break;
	case WM_KEYUP:
		{
			if (wParam == VK_KEY_A || wParam == VK_KEY_D)
				OnRunStop();
		}
		break;
	case WM_SIZE:
		{
			OnResize(LOWORD(lParam), HIWORD(lParam));
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void GameController::Update()
{
	double dt = m_pHPTimer->GetTimeDelta();

	if (m_bActive)
	{
			 if (GetKeyState(VK_KEY_A) & 0x8000) OnMoveLeft (dt);
		else if (GetKeyState(VK_KEY_D) & 0x8000) OnMoveRight(dt);
	}

	/*
	if (m_pMap) 
	{
		for (auto o : m_pMap->m_objects)
		{
			//o->Fall_(dt);
			o->Gravity	(dt);
			o->Fall		(dt);

			for (auto p : m_pMap->m_objects)
				o->Collision(p);
		}
	}
	*/
	if (m_pMap)
	{
		for (auto o : m_pMap->m_players)
		{
			Gravity(o, dt);
		}
	}

	auto POINTCenter = GetCenter();

	if (auto pBackground = m_pMap->GetBackground()) 
	{
		pBackground->OnViewXChange(m_D2D1PFLastCenter.x - POINTCenter.x);
		pBackground->OnViewYChange(m_D2D1PFLastCenter.y - POINTCenter.y);
	}

	// Save last center coordinates
	m_D2D1PFLastCenter.x = POINTCenter.x;
	m_D2D1PFLastCenter.y = POINTCenter.y;

	m_pGraphics->SetCenter(POINTCenter.x, POINTCenter.y);

	m_pHPTimer->UpdateFramestate();
}

void GameController::Render()
{
	m_pGraphics->BeginDraw();

	m_pGraphics->ClearScreen(255, 255, 255);

	if (m_pMap) 
	{
		for (auto o : m_pMap->m_objects)
			m_pGraphics->Draw(o);
			//o->Draw(m_pGraphics);
	}

	m_pGraphics->ResetTransform();

	m_pGraphics->EndDraw();
}

void GameController::OnJump()
{
	if (m_pMainPlayer) m_pMainPlayer->Jump();
}

void GameController::OnRunStop()
{
	if (m_pMainPlayer) m_pMainPlayer->RunStop();
}

void GameController::OnMoveLeft(double dt)
{
	if (!m_pMainPlayer) return;
	if (!m_pMap) return;

	if (!m_pMap->CanMoveLeft(m_pMainPlayer, dt)) return;

	m_pMainPlayer->MoveLeft(dt);

	// Limit player X coordinate
	if (m_pMainPlayer->m_fX - PLAYER_WIDTH / 2 < m_pMap->m_fMinX)
		m_pMainPlayer->m_fX = m_pMap->m_fMinX + PLAYER_WIDTH / 2;
}

void GameController::OnMoveRight(double dt)
{
	if (!m_pMainPlayer) return;
	if (!m_pMap) return;

	if (!m_pMap->CanMoveRight(m_pMainPlayer, dt)) return;

	m_pMainPlayer->MoveRight(dt);

	// Limit player X coordinate
	if (m_pMainPlayer->m_fX + PLAYER_WIDTH / 2 > m_pMap->m_fMaxX)
		m_pMainPlayer->m_fX = m_pMap->m_fMaxX - PLAYER_WIDTH / 2;
}

void GameController::OnResize(UINT width, UINT height)
{
	D2D1_SIZE_U size;
	size.width = width;
	size.height = height;

	m_pGraphics->GetRenderTarget()->Resize(size);
}

void GameController::Gravity(Player *pPlayer, double dt)
{
	pPlayer->m_fSpeedY += GRAVITY * (float)dt;

	if (auto pBrick = m_pMap->GetGround(pPlayer, dt))
	{
		pPlayer->m_fSpeedY = 0;
		pPlayer->SubPState(Player::PS_JUMP);
		pPlayer->m_byJump = 0;
		pPlayer->m_fY = pBrick->GetHeight(pPlayer->m_fX);
	}
	else
	{
		pPlayer->m_fY += pPlayer->m_fSpeedY * (float)dt;
	}
}

D2D1_POINT_2F GameController::GetCenter()
{
	auto center = D2D1::Point2F(0, 0);

	if (!m_pMainPlayer) return center;
	if (!m_pMap)		return center;

	center.x = m_pMainPlayer->m_fX;
	center.y = m_pMainPlayer->m_fY - PLAYER_HEIGHT / 2;

	/*
	if (m_pMap->m_fMaxY - center.y < SCREEN_HEIGHT / 2) 
		center.y = m_pMap->m_fMaxY - SCREEN_HEIGHT / 2;

	if (m_pMap->m_fMaxX - center.x < SCREEN_WIDTH / 2) 
		center.x = m_pMap->m_fMaxX - SCREEN_WIDTH / 2;

	if (center.x - m_pMap->m_fMinX < SCREEN_WIDTH / 2) 
		center.x = m_pMap->m_fMinX + SCREEN_WIDTH / 2;
	*/

	D2D1_SIZE_F size = m_pGraphics->GetRenderTarget()->GetSize();

	if (m_pMap->m_fMaxY - center.y < size.height / 2)
		center.y = m_pMap->m_fMaxY - size.height / 2;

	if (m_pMap->m_fMaxX - center.x < size.width / 2)
		center.x = m_pMap->m_fMaxX - size.width / 2;

	if (center.x - m_pMap->m_fMinX < size.width / 2)
		center.x = m_pMap->m_fMinX + size.width / 2;

	return center;
}