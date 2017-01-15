#include "Player.h"
#include "Brick.h"


Player::Player(float fX, float fY)
	: Object(fX, fY)
{
	m_bFalling = true;
	m_byJump = 0;
	m_bDirection = DIRECTION::RIGHT;
	//m_n64PState = 0;

	for (int i = 0; i < PLAYER_SPRITE_LEN; i++)
		for (int j = 0; j < PLAYER_DIRECTIONS; j++)
		m_pSprites[i][j] = NULL;
}

Player::~Player()
{
	for (int i = 0; i < PLAYER_SPRITE_LEN; i++)
		for (int j = 0; j < PLAYER_DIRECTIONS; j++)
			if (m_pSprites[i][j]) delete m_pSprites[i][j];
}

/*
void Player::Draw(Graphics* pGraphics)
{
	BYTE bySprite = PSPRITE_STAND;

	if (IsPState(PS_JUMP))
	{
		bySprite = PSPRITE_JUMP;
	}
	else if (IsPState(PS_RUN))
	{
		bySprite = PSPRITE_RUN;
	}

	pGraphics->GetRenderTarget()->DrawBitmap(
		m_pSprites[bySprite][m_bDirection]->GetBitmap(),
		D2D1::RectF(m_fX, m_fY - PLAYER_HEIGHT + 5, m_fX + PLAYER_WIDTH, m_fY + 5),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		m_pSprites[bySprite][m_bDirection]->GetSource()
	);
}
*/

void Player::Gravity(double dt)
{
	if (m_bFalling) 
		m_fSpeedY += GRAVITY * dt;
}

void Player::Fall(double dt)
{
	double d = m_fSpeedY * dt;

	//if (d >= MAX_FALL_SPEED) d = MAX_FALL_SPEED - 0.001;
	if (d > MAX_FALL_SPEED) d = MAX_FALL_SPEED;
	m_fY += d;
}

void Player::Collision(Object* pObject)
{

	if (instanceof<Brick>(pObject))
	{
		auto pBrick = (Brick*)pObject;

		// Is not falling
		if (m_fSpeedY <= 0) return;

		if (m_fX + PLAYER_WIDTH < pBrick->m_fX) return;
		if (m_fX > pBrick->m_fX + pBrick->m_fWidth) return;

		float fY = pBrick->GetHeight(m_fX + PLAYER_WIDTH / 2);

		if (m_fY < fY) return;
		if (m_fY > fY + MAX_FALL_SPEED) return;

		m_bFalling = false;
		m_fY = fY;
		m_fSpeedY = 0;
		m_byJump = 0;

		SubPState(PS_JUMP);

		return;
	}

	m_bFalling = true;
}

void Player::MoveLeft(double dt)
{
	m_fX -= PLAYER_SPEED * dt;

	// Direction change
	if (m_bDirection != DIRECTION::LEFT)
	{
		m_bDirection = DIRECTION::LEFT;
		m_pSprites[PSPRITE_JUMP][m_bDirection]->SetFrameOf(m_pSprites[PSPRITE_JUMP][DIRECTION::RIGHT]);
	}

	AddPState(PS_RUN);
}

void Player::MoveRight(double dt)
{
	m_fX += PLAYER_SPEED * dt;

	// Direction change
	if (m_bDirection != DIRECTION::RIGHT)
	{
		m_bDirection = DIRECTION::RIGHT;
		m_pSprites[PSPRITE_JUMP][m_bDirection]->SetFrameOf(m_pSprites[PSPRITE_JUMP][DIRECTION::LEFT]);
	}

	AddPState(PS_RUN);
}

void Player::RunStop()
{
	SubPState(PS_RUN);
}

void Player::Jump()
{
	if (m_byJump >= PLAYER_JUMPCOUNT) return;

	m_byJump++;
	m_fSpeedY = PLAYER_JUMPPOWER;
	m_bFalling = true;
	
	AddPState(PS_JUMP);

	m_pSprites[PSPRITE_JUMP][DIRECTION::LEFT]->RestartAnimation();
	m_pSprites[PSPRITE_JUMP][DIRECTION::RIGHT]->RestartAnimation();
}