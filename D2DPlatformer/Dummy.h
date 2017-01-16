#pragma once

#include "Object.h"

class Dummy : public Object
{
public:
	Dummy(float fX, float fY)
		: Object(fX, fY, OT_DUMMY) {}

	//void Draw(Graphics* pGraphics) override;
	
	void Gravity(double dt) override {}
	void Fall(double dt) override {}
	void Collision(Object* pObject) override {}
};