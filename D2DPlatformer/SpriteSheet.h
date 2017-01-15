#pragma once

#include <wincodec.h>
#include <d2d1.h>

class Graphics;

class SpriteSheet
{
	ID2D1Bitmap *m_pBitmap;

	int m_nWidth;
	int m_nHeight;

	int m_nAmount;
	int m_nFrame;
	bool m_bLoop;

	DWORD m_dwFrameSpeed;
	DWORD m_dwLastFrameChange;

public:
	// Single
	SpriteSheet(wchar_t* szFilename, Graphics *pGraphics);

	// Multiple
	SpriteSheet(wchar_t* szFilename, Graphics *pGraphics, int nWidth, int nHeight, DWORD dwFrameSpeed, bool bLoop = true);

	~SpriteSheet();

	ID2D1Bitmap *GetBitmap() { return m_pBitmap; }
	
	// Auto-Framebased
	D2D1_RECT_F GetSource();

	D2D1_RECT_F GetSoruce(int nIndex);

	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }

	int GetFrame() { return m_nFrame; }
	void NextFrame();
	void RestartAnimation();
	void SetLastFrame();
	void SetFrameOf(SpriteSheet *pSprite);
};