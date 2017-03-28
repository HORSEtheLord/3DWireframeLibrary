#include "Graphics.h"
#include "Logger.h"

Graphics::Graphics(int centerX, int centerY)
	: m_centerX(centerX), m_centerY(centerY)
{
}

Graphics::~Graphics()
{
	if (m_factory)
		m_factory->Release();
	if (m_renderTarget)
		m_renderTarget->Release();
	if (m_brush)
		m_brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
	if (res != S_OK)
	{
		Logger::Log(L"D2D1Factory creation failed.");
		return false;
	}

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = m_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&m_renderTarget);

	if (res != S_OK)
	{
		Logger::Log(L"D2D1RenderTarget creation failed.");
		return false;
	}

	res = m_renderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::LightSlateGray),
		&m_brush);

	if (res != S_OK)
	{
		Logger::Log(L"ID2D1SolidColorBrush creation failed.");
		return false;
	}

	return true;
}

void Graphics::DrawLine(float x1, float y1, float x2, float y2) const
{
	m_renderTarget->DrawLine(
		D2D1::Point2F(x1 + m_centerX, y1 + m_centerY),
		D2D1::Point2F(x2 + m_centerX, y2 + m_centerY),
		m_brush);
}

void Graphics::ClearScreen(float r, float g, float b) const
{
	m_renderTarget->Clear(D2D1::ColorF(r, g, b));
}
