#include "Map.h"

Map::Map(Graphics *pGraphics)
{
	Background	*pBackground;
	Brick		*pBrick;
	Dummy		*pDummy;

	pBackground = new Background(-1400, -798);
	pBackground->m_pSpriteSheet = new SpriteSheet(L"data\\background\\BG_la2y.png", pGraphics, 4200, 1500, 0, false);
	Add (pBackground);

	pBackground->AddLayer(0, -0.375f, 0.1f);
	pBackground->AddLayer(1, -0.857f, -0.3f);

	
	pBrick = new Brick(800, 480, 384, 93, 0);
	pBrick->m_pSpriteSheet = new SpriteSheet(L"data\\brick\\19.png", pGraphics);
	Add (pBrick);

	pBrick = new Brick(300, 380, 384, 93, 0);
	pBrick->m_pSpriteSheet = new SpriteSheet(L"data\\brick\\19.png", pGraphics);
	Add (pBrick);

	pBrick = new Brick(10, 280, 384, 93, 0);
	pBrick->m_pSpriteSheet = new SpriteSheet(L"data\\brick\\19.png", pGraphics);
	Add (pBrick);

	pBrick = new Brick(450, 220, 384, 93, 0);
	pBrick->m_pSpriteSheet = new SpriteSheet(L"data\\brick\\19.png", pGraphics);
	Add (pBrick);

	pBrick = new Brick(-1400, 572, 4200, 128, 0);
	pBrick->m_pSpriteSheet = new SpriteSheet(L"data\\brick\\Brick__001.png", pGraphics);
	Add (pBrick);

	pBrick = new Brick(1347, 445, 128, 128, 45.0);
	pBrick->m_pSpriteSheet = new SpriteSheet(L"data\\brick\\Brick__001_45.png", pGraphics);
	Add (pBrick);

	pBrick = new Brick(1474, 445, 128, 128, 0);
	pBrick->m_pSpriteSheet = new SpriteSheet(L"data\\brick\\Brick__002.png", pGraphics);
	Add (pBrick);

	pBrick = new Brick(1601, 445, 256, 128, 150.0);
	pBrick->m_pSpriteSheet = new SpriteSheet(L"data\\brick\\Brick__001_-60.png", pGraphics);
	Add (pBrick);

	
	pDummy = new Dummy(817, 305);
	pDummy->m_pSpriteSheet = new SpriteSheet(L"data\\dummy\\tree01.png", pGraphics);
	Add (pDummy);

	m_fMaxY = 700.0f;
	m_fMinX = -1400.0f;
	m_fMaxX = 2800.0f;
}

Map::~Map()
{
	for (auto o : m_objects)
		delete o;
}

void Map::Add(Player* pPlayer)
{
	m_objects.push_back(pPlayer);
}

void Map::Add(Brick* pBrick)
{
	m_objects.push_back(pBrick);
}

void Map::Add(Background* pBackground)
{
	m_objects.push_back(pBackground);
	m_pBackground = pBackground;
}

void Map::Add(Dummy* pDummy)
{
	m_objects.push_back(pDummy);
}

bool Map::IsFalling(Object* pObject, double dt)
{
	if (!Object::instanceof<Player>(pObject)) return false;

	auto pPlayer = (Player*) pObject;
	if (!pPlayer->m_fSpeedY) return false;

	for (auto o : m_objects)
	{
		if (pPlayer->m_fSpeedY > 0) 
		{
			if (o->IsOverlap(pPlayer->m_fX, pPlayer->m_fY, pPlayer->m_fX, pPlayer->m_fY + pPlayer->m_fSpeedY * (float)dt)) return false;
		}
		else
		{
			if (o->IsOverlap(pPlayer->m_fX, pPlayer->m_fY + pPlayer->m_fSpeedY * (float)dt, pPlayer->m_fX, pPlayer->m_fY)) return false;
		}
	}

	return true;
}

bool Map::CanMoveLeft(Object* pObject, double dt)
{
	return true;
}

bool Map::CanMoveRight(Object* pObject, double dt)
{
	return true;
}

Object* Map::GetGround(Object* pObject, double dt)
{
	if (!Object::instanceof<Player>(pObject)) return nullptr;

	auto pPlayer = (Player*) pObject;
	if (!pPlayer->m_fSpeedY) return nullptr;

	for (auto o : m_objects)
	{
		if (pPlayer->m_fSpeedY > 0) 
		{
			if (o->IsOverlap(pPlayer->m_fX, pPlayer->m_fY, pPlayer->m_fX, pPlayer->m_fY + pPlayer->m_fSpeedY * (float)dt)) return o;
		}
		else
		{
			if (o->IsOverlap(pPlayer->m_fX, pPlayer->m_fY + pPlayer->m_fSpeedY * (float)dt, pPlayer->m_fX, pPlayer->m_fY)) return o;
		}
	}

	return nullptr;
}

Object* Map::FindObject(float fX1, float fY1, float fX2, float fY2)
{
	for (auto o : m_objects)
	{
		if (o->IsOverlap(fX1, fY1, fX2, fY2))
			return o;
	}

	return nullptr;
}