#include "Graphics.h"
#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(wchar_t* szFilename, Graphics* pGraphics)
{
	m_pBitmap = NULL;

	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		szFilename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	if (!wicDecoder)
	{
		MessageBox(
			NULL,
			"Game file is missing. Reinstall application.",
			"Game corrupted",
			MB_ICONERROR | MB_OK
	    );
		exit(-1);
	}

	IWICBitmapFrameDecode *wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);

	hr = pGraphics->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &m_pBitmap);

	m_nAmount = 1;
	m_nWidth = (int) m_pBitmap->GetSize().width;
	m_nHeight = (int) m_pBitmap->GetSize().height;
	m_nFrame = 1;
	m_dwFrameSpeed = 0;
	m_dwLastFrameChange = GetTickCount();
	m_bLoop = false;

	if (wicFactory)   wicFactory->Release();
	if (wicDecoder)   wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame)     wicFrame->Release();
}

SpriteSheet::SpriteSheet(wchar_t* szFilename, Graphics* pGraphics, int nWidth, int nHeight, DWORD dwFrameSpeed, bool bLoop)
{
	m_pBitmap = NULL;

	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		szFilename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	if (!wicDecoder)
	{
		MessageBox(
			NULL,
			"Game file is missing. Reinstall application.",
			"Game corrupted",
			MB_ICONERROR | MB_OK
	    );
		exit(-1);
	}

	IWICBitmapFrameDecode *wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);

	hr = pGraphics->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter, NULL, &m_pBitmap);

	m_nFrame = 0;

	if (wicFactory)   wicFactory->Release();
	if (wicDecoder)   wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame)     wicFrame->Release();

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_dwLastFrameChange = GetTickCount();
	m_dwFrameSpeed = dwFrameSpeed;
	m_bLoop = bLoop;

	m_nAmount = (int) (m_pBitmap->GetSize().width / nWidth);
}


SpriteSheet::~SpriteSheet()
{
	if (m_pBitmap) m_pBitmap->Release();
}

D2D1_RECT_F SpriteSheet::GetSource()
{
	D2D1_RECT_F rect = D2D1::RectF((float) (m_nFrame * m_nWidth), 0, (float) (m_nFrame * m_nWidth + m_nWidth), (float) m_nHeight);
	
	NextFrame();

	return rect;
}

D2D1_RECT_F SpriteSheet::GetSoruce(int nIndex)
{
	return D2D1::RectF((float) (nIndex * m_nWidth), 0, (float) (nIndex * m_nWidth + m_nWidth), (float) m_nHeight);
}

void SpriteSheet::NextFrame()
{
	if (GetTickCount() - m_dwLastFrameChange < m_dwFrameSpeed) return;

	if (m_bLoop)
	{
		m_nFrame = (m_nFrame + 1) % m_nAmount;
	}
	else
	{
		if (m_nFrame < m_nAmount - 1)
			m_nFrame++;
	}

	
	m_dwLastFrameChange = GetTickCount();
}

void SpriteSheet::RestartAnimation()
{
	m_nFrame = 0;
}

void SpriteSheet::SetLastFrame()
{
	m_nFrame = m_nAmount - 1;
}

void SpriteSheet::SetFrameOf(SpriteSheet* pSprite)
{
	m_nFrame = pSprite->GetFrame();
}