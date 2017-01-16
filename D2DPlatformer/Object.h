#pragma once

#include "SpriteSheet.h"

#include "Common.h"

#define GRAVITY 800.0f
#define MAX_FALL_SPEED 20.0


class Object
{
public:
	Object(float fX, float fY, BYTE bType);
	virtual ~Object();

	int m_nID;

	BYTE m_bType;

	float m_fX;
	float m_fY;
	float m_fSpeedY;

	SpriteSheet *m_pSpriteSheet;

	//virtual void Draw(Graphics* pGraphics) = 0;

	virtual void Gravity(double dt) = 0;
	virtual void Fall(double dt) = 0;
	virtual void Collision(Object* pObject) = 0;

	virtual void Fall_(double dt) = 0;
 
	virtual bool IsOverlap(float fX1, float fY1, float fX2, float fY2) { return false; }

	template<typename Base, typename T>
    static bool instanceof(const T *ptr) {
        return dynamic_cast<const Base*>(ptr) != nullptr;
    }
};