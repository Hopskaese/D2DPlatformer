#pragma once

#include <Windows.h>
#include <d2d1.h>

#include "Player.h"
#include "Background.h"
#include "Brick.h"
#include "Dummy.h"

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 700

class Graphics
{
	ID2D1Factory			*m_pFactory;
	ID2D1HwndRenderTarget	*m_pRenderTarget;
	ID2D1SolidColorBrush	*m_pBrush;

public:

	UINT m_nScreenWidth;
	UINT m_nScreenHeight;

	Graphics();
	~Graphics();

	bool Init(HWND hWnd);

	void BeginDraw() { m_pRenderTarget->BeginDraw(); }
	void EndDraw()   { m_pRenderTarget->EndDraw();   }

	void SetCenter(float fX, float fY);
	void ResetTransform() { m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); }

	void ClearScreen(float fRed, float fGreen, float fBlue);

	void DrawCircle(float fX, float fY, float fRadius, float fRed, float fGreen, float fBlue);
	void DrawRectangle(float fX, float fY, float fWidth, float fHeight, float fRed, float fGreen, float fBlue);

	void Draw(Object *pObject);
	void Draw(Player *pPlayer);
	void Draw(Background *pBackground);
	void Draw(Brick *pBrick);
	void Draw(Dummy *pDummy);

	ID2D1HwndRenderTarget *GetRenderTarget() { return m_pRenderTarget; }
};