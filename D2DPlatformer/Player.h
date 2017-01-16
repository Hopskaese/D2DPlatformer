#pragma once

#include "Object.h"

#define PLAYER_WIDTH  43.0f
#define PLAYER_HEIGHT 60.0f
#define PLAYER_SPEED 300.0f
#define PLAYER_JUMPPOWER -400.0f
#define PLAYER_JUMPCOUNT 1

#define PLAYER_SPRITE_LEN 3
#define PLAYER_DIRECTIONS 2

class Player : public Object
{
public:
	enum DIRECTION { LEFT = 0, RIGHT = 1 };

	enum PSTATE
	{
		PS_RUN =		  0x1,
		PS_JUMP =		 0x10,
	};

	enum PSPRITE
	{
		PSPRITE_STAND,
		PSPRITE_RUN,
		PSPRITE_JUMP,
	};

	Player(float fX, float fY);
	~Player();

	bool m_bFalling;
	BYTE m_byJump;

	bool m_bDirection;

	__int64 m_n64PState;


	SpriteSheet *m_pSprites[PLAYER_SPRITE_LEN][PLAYER_DIRECTIONS];

	//void Draw(Graphics* pGraphics) override;
	
	/*
	void Gravity(double dt) override;
	void Fall(double dt) override;
	void Collision(Object* pObject) override;
	*/

	void MoveLeft(double dt);
	void MoveRight(double dt);
	void RunStop();
	void Jump();
	
	void AddPState(__int64 n64PState) { m_n64PState |= n64PState; }
	void SubPState(__int64 n64PState) { m_n64PState &= ~n64PState;}
	bool IsPState (__int64 n64PState) const { return (m_n64PState & n64PState) != 0; }
};