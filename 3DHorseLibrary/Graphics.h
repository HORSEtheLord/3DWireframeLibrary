#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
private:
	ID2D1Factory *m_factory = nullptr;
	ID2D1HwndRenderTarget *m_renderTarget = nullptr;
	ID2D1SolidColorBrush *m_brush = nullptr;

	int m_centerX;
	int m_centerY;
public:
	Graphics(int centerX, int centerY);
	Graphics(const Graphics &other) = delete;
	~Graphics();

	void operator=(const Graphics&) = delete;

	bool Init(HWND windowHandle);

	ID2D1RenderTarget *GetRenderTarget() const
	{
		return m_renderTarget;
	}

	void BeginDraw() const { m_renderTarget->BeginDraw(); }
	void EndDraw() const { m_renderTarget->EndDraw(); }

	void DrawLine(float x1, float y1, float x2, float y2) const;

	void ClearScreen(float r, float g, float b) const;
};