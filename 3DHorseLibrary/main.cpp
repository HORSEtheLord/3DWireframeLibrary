#define _USE_MATH_DEFINES
#include<cmath>
#include <memory>
#include <Windows.h>
#include <Windowsx.h>

#include "Graphics.h"
#include "Logger.h"
#include "Timer.h"
#include "Utils.h"
#include "Scene.h"

#define TRANSLATION_STEP 15
#define ROTATION_STEP M_PI / (36 * 2)

Scene scene;
std::shared_ptr<Timer> timer;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			{
				Matrix3D matrix = Matrix3D::CreateTranslationMatrix(0, TRANSLATION_STEP, 0);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case VK_DOWN:
			{
				Matrix3D matrix = Matrix3D::CreateTranslationMatrix(0, -TRANSLATION_STEP, 0);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case VK_LEFT:
			{
				Matrix3D matrix = Matrix3D::CreateTranslationMatrix(TRANSLATION_STEP, 0, 0);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case VK_RIGHT:
			{
				Matrix3D matrix = Matrix3D::CreateTranslationMatrix(-TRANSLATION_STEP, 0, 0);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case VK_PRIOR:
			{
				Matrix3D matrix = Matrix3D::CreateTranslationMatrix(0, 0, TRANSLATION_STEP);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case VK_NEXT:
			{
				Matrix3D matrix = Matrix3D::CreateTranslationMatrix(0, 0, -TRANSLATION_STEP);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case 'Q':
			{
				Matrix3D matrix = Matrix3D::CreateRotationYMatrix(ROTATION_STEP);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case 'W':
			{
				Matrix3D matrix = Matrix3D::CreateRotationYMatrix(-ROTATION_STEP);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case 'A':
			{
				Matrix3D matrix = Matrix3D::CreateRotationXMatrix(ROTATION_STEP);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case 'S':
			{
				Matrix3D matrix = Matrix3D::CreateRotationXMatrix(-ROTATION_STEP);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case 'Z':
			{
				Matrix3D matrix = Matrix3D::CreateRotationZMatrix(ROTATION_STEP);
				scene.TransformViewMatrix(matrix);
			}
			break;
		case 'X':
			{
				Matrix3D matrix = Matrix3D::CreateRotationZMatrix(-ROTATION_STEP);
				scene.TransformViewMatrix(matrix);
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND createWindow(HINSTANCE hInstance)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "3DHorse", WS_OVERLAPPEDWINDOW, 100, 100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	return windowHandle;
}

void unitialize()
{
	CoUninitialize();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	Logger::Clear();
	Logger::Log(L"Application started.");

	HWND windowHandle = createWindow(hInstance);

	if (!windowHandle)
	{
		Logger::Log(L"Window creation failed.");
		return -1;
	}

	HRESULT hr = CoInitialize(NULL);

	if (hr != S_OK)
	{
		Logger::Log(L"CoInitialize failed.");
		return -1;
	}

	Graphics graphics(400, 300);

	if (!graphics.Init(windowHandle))
	{
		Logger::Log(L"Graphics initialization failed.");
		unitialize();
		return -1;
	}

	ShowWindow(windowHandle, nCmdShow);

	timer = std::make_shared<Timer>();

	double lag = 0.0;

	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}
		else
		{
			lag += timer->Tick();

			while (lag >= MS_PER_UPDATE)
			{
				lag -= MS_PER_UPDATE;
			}

			graphics.BeginDraw();
			graphics.ClearScreen(0, 0, 0);

			scene.Draw(graphics);

			graphics.EndDraw();
		}
	}

	unitialize();

	Logger::Log(L"Application ended.");
	return 0;
}