#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include "Brick.h"
#include "Player.h"


Brick::Brick(float fX, float fY, float fWidth, float fHeight, float fAngle)
	: Object(fX, fY, OT_BRICK)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	
	m_fAngle = fAngle;
}

/*
void Brick::Draw(Graphics* pGraphics)
{
	if (!m_pSpriteSheet){
		pGraphics->DrawRectangle(m_fX, m_fY, m_fWidth, m_fHeight, 0, 0, 0);
		return;
	}

	pGraphics->GetRenderTarget()->DrawBitmap(
		m_pSpriteSheet->GetBitmap(),
		D2D1::RectF(m_fX, m_fY, m_fX + m_fWidth, m_fY + m_fHeight),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0, 0, m_fWidth, m_fHeight)
	);
}
*/

bool Brick::IsOverlap(float fX1, float fY1, float fX2, float fY2)
{
	if (m_fX < fX1 || m_fX + m_fWidth > fX2)	return false;
	if (m_fY < fY1 || m_fY > fY2)				return false;

	return true;
}

float Brick::GetHeight(float fX)
{
	if (m_fAngle == 0)				return m_fY;

	if (fX < m_fX)					return 0;
	if (fX > m_fX + m_fWidth)		return 0;

	if (m_fAngle <= 90.0)
	{
		float fHeight = ((float)1.0 / (float)tan(m_fAngle * (float)(M_PI / 180))) * (fX - m_fX);

		return m_fY + m_fHeight - fHeight;
	}
	else
	{
		float fAngle = m_fAngle - (float)90.0;
		float fHeight = ((float)1.0 / (float)tan(fAngle * (float)(M_PI / 180))) * (m_fX + m_fWidth - fX);

		return m_fY + m_fHeight - fHeight;
	}
}