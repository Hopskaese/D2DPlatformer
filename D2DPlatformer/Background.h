#pragma once

#include "Object.h"
#include <vector>

struct BackgroundLayer
{
	BackgroundLayer(float fX, float fY, int nIndex, float nSpeedX, float nSpeedY):
		m_fX(fX), m_fY(fY), m_nIndex(nIndex), m_fSpeedX(nSpeedX), m_fSpeedY(nSpeedY) {}

	float m_fX;
	float m_fY;

	float m_fSpeedX;
	float m_fSpeedY;
	
	int m_nIndex;
};

class Background : public Object
{
public:
	std::vector<BackgroundLayer*> m_layers;

	Background(float fX, float fY): Object(fX, fY, OT_BACKGROUND) {}
	~Background();

	void AddLayer(int nIndex, float nSpeedX, float nSpeedY);

	//void Draw(Graphics* pGraphics) override;
	
	void Gravity(double dt) override {}
	void Fall(double dt) override {}
	void Collision(Object *pObject) override {}

	void OnViewXChange(float fDistance);
	void OnViewYChange(float fDistance);
};