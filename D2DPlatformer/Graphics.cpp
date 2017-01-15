#include "Graphics.h"


Graphics::Graphics()
{
	m_pFactory =		NULL;
	m_pRenderTarget =	NULL;
	m_pBrush =			NULL;
}

Graphics::~Graphics()
{
	if (m_pFactory)			m_pFactory->Release();
	if (m_pRenderTarget)	m_pRenderTarget->Release();
	if (m_pBrush)			m_pBrush->Release();
}

bool Graphics::Init(HWND hWnd)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(hWnd, &rect);

	res = m_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom)),
		&m_pRenderTarget);

	if (res != S_OK) return false;

	res = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &m_pBrush);

	if (res != S_OK) return false;

	return true;
}

void Graphics::SetCenter(float fX, float fY)
{
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(SCREEN_WIDTH / 2 - fX, SCREEN_HEIGHT / 2 - fY));
}

void Graphics::ClearScreen(float fRed, float fGreen, float fBlue)
{
	m_pRenderTarget->Clear(D2D1::ColorF(fRed, fGreen, fBlue));
}

void Graphics::DrawCircle(float fX, float fY, float fRadius, float fRed, float fGreen, float fBlue)
{
	m_pBrush->SetColor(D2D1::ColorF(fRed, fGreen, fBlue));

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(fX, fY), fRadius, fRadius);

	m_pRenderTarget->DrawEllipse(ellipse, m_pBrush, 3.0f);
	m_pRenderTarget->FillEllipse(ellipse, m_pBrush);
}

void Graphics::DrawRectangle(float fX, float fY, float fWidth, float fHeight, float fRed, float fGreen, float fBlue)
{
	m_pBrush->SetColor(D2D1::ColorF(fRed, fGreen, fBlue));

	D2D_RECT_F rect = D2D1::RectF(fX, fY, fX + fWidth, fY + fHeight);

	m_pRenderTarget->FillRectangle(rect, m_pBrush);
}


void Graphics::Draw(Object* pObject)
{
		 if (Object::instanceof<Background>(pObject))
		Draw((Background*)pObject);
	else if (Object::instanceof<Brick>(pObject))
		Draw((Brick*)pObject);
	else if (Object::instanceof<Dummy>(pObject))
		Draw((Dummy*)pObject);
	else if (Object::instanceof<Player>(pObject))
		Draw((Player*)pObject);
}


void Graphics::Draw(Player* pPlayer)
{
	BYTE bySprite = Player::PSPRITE_STAND;

	if (pPlayer->IsPState(Player::PS_JUMP))
	{
		bySprite = Player::PSPRITE_JUMP;
	}
	else if (pPlayer->IsPState(Player::PS_RUN))
	{
		bySprite = Player::PSPRITE_RUN;
	}

	m_pRenderTarget->DrawBitmap(
		pPlayer->m_pSprites[bySprite][pPlayer->m_bDirection]->GetBitmap(),
		D2D1::RectF(pPlayer->m_fX, pPlayer->m_fY - PLAYER_HEIGHT + 5, pPlayer->m_fX + PLAYER_WIDTH, pPlayer->m_fY + 5),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		pPlayer->m_pSprites[bySprite][pPlayer->m_bDirection]->GetSource()
	);
}

void Graphics::Draw(Background* pBackground)
{
	if (!pBackground->m_pSpriteSheet) return;

	for (auto pLayer = pBackground->m_layers.rbegin(); pLayer != pBackground->m_layers.rend(); ++pLayer)
	{
		m_pRenderTarget->DrawBitmap(
			pBackground->m_pSpriteSheet->GetBitmap(),
			D2D1::RectF((*pLayer)->m_fX, (*pLayer)->m_fY, (*pLayer)->m_fX + pBackground->m_pSpriteSheet->GetWidth(), (*pLayer)->m_fY + pBackground->m_pSpriteSheet->GetHeight()),
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			pBackground->m_pSpriteSheet->GetSoruce((*pLayer)->m_nIndex)
		);
	}
}

void Graphics::Draw(Brick* pBrick)
{
	m_pRenderTarget->DrawBitmap(
		pBrick->m_pSpriteSheet->GetBitmap(),
		D2D1::RectF(pBrick->m_fX, pBrick->m_fY, pBrick->m_fX + pBrick->m_fWidth, pBrick->m_fY + pBrick->m_fHeight),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0, 0, pBrick->m_fWidth, pBrick->m_fHeight)
	);

	if (!pBrick->m_pSpriteSheet)
		DrawRectangle(pBrick->m_fX, pBrick->m_fY, pBrick->m_fWidth, pBrick->m_fHeight, 0, 0, 0);
}

void Graphics::Draw(Dummy* pDummy)
{
	if (!pDummy->m_pSpriteSheet) return;

	m_pRenderTarget->DrawBitmap(
		pDummy->m_pSpriteSheet->GetBitmap(),
		D2D1::RectF(pDummy->m_fX, pDummy->m_fY, pDummy->m_fX + pDummy->m_pSpriteSheet->GetBitmap()->GetSize().width, pDummy->m_fY + pDummy->m_pSpriteSheet->GetBitmap()->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0, 0, pDummy->m_pSpriteSheet->GetBitmap()->GetSize().width, pDummy->m_pSpriteSheet->GetBitmap()->GetSize().height)
	);
}