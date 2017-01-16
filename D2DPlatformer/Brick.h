#pragma once

#include "Object.h"

class Brick : public Object
{
public:
	Brick(float fX, float fY, float fWidth, float fHeight, float fAngle);

	float m_fWidth;
	float m_fHeight;

	float m_fAngle;

	//void Draw(Graphics* pGraphics) override;
	
	/*
	void Gravity(double dt) override {}
	void Fall(double dt) override {}
	void Collision(Object* pObject) override {}
	*/
	bool IsOverlap(float fX1, float fY1, float fX2, float fY2) override;

	float GetHeight(float fX);
};