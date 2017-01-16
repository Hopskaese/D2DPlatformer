#pragma once

#include <vector>

#include "Player.h"
#include "Brick.h"
#include "Dummy.h"
#include "Background.h"

class Map
{
	Background *m_pBackground;

public:
	std::vector<Brick*> m_bricks;
	std::vector<Player*> m_players;
	std::vector<Object*> m_objects;

	Map(Graphics *pGraphics);
	~Map();

	float m_fMaxY;
	float m_fMinX;
	float m_fMaxX;

	void Add(Player *pPlayer);
	void Add(Brick* pBrick);
	void Add(Background *pBackground);
	void Add(Dummy *pDummy);

	bool IsFalling(Object *pObject, double dt);
	bool CanMoveLeft(Object *pObject, double dt);
	bool CanMoveRight(Object *pObject, double dt);
	Object* GetGround(Object *pObject, double dt);

	Object* FindObject(float fX1, float fY1, float fX2, float fY2);

	Background *GetBackground() { return m_pBackground; }
};