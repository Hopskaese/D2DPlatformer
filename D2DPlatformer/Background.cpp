#include "Background.h"


Background::~Background()
{
	for (int i = 0; i < m_layers.size(); i++)
		delete m_layers[i];
}

void Background::AddLayer(int nIndex, float nSpeedX, float nSpeedY)
{
	m_layers.push_back(new BackgroundLayer(m_fX, m_fY, nIndex, nSpeedX, nSpeedY));
}

/*
void Background::Draw(Graphics* pGraphics)
{
	if (!m_pSpriteSheet) return;

	for (auto pLayer = m_layers.rbegin(); pLayer != m_layers.rend(); ++pLayer)
	{
		pGraphics->GetRenderTarget()->DrawBitmap(
			m_pSpriteSheet->GetBitmap(),
			D2D1::RectF((*pLayer)->m_fX, (*pLayer)->m_fY, (*pLayer)->m_fX + m_pSpriteSheet->GetWidth(), (*pLayer)->m_fY + m_pSpriteSheet->GetHeight()),
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			m_pSpriteSheet->GetSoruce((*pLayer)->m_nIndex)
		);
	}
} */

void Background::OnViewXChange(float fDistance)
{
	for (auto pLayer : m_layers)
		pLayer->m_fX += fDistance * pLayer->m_fSpeedX;
}

void Background::OnViewYChange(float fDistance)
{
	for (auto pLayer : m_layers)
		pLayer->m_fY += fDistance * pLayer->m_fSpeedY;
}