#include "Application.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Time.h"
#include "Input.h"

namespace sw
{
	//Application Application::mInstance;


	Application::Application()
	{
		mWindowData.clear();
	}

	Application::~Application()
	{

	}

	void Application::Initialize(WindowData data)
	{
		Application::initialize(data);

		Time::Initialize();
		Input::Initialize();
		SceneManager::Initalize();
	}
		
	void Application::initialize(WindowData data)
	{
		mWindowData = data;
		mWindowData.hdc = GetDC(data.hWnd);

		// 1922
		// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
		RECT rect = { 0,0, data.width, data.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경
		SetWindowPos(data.hWnd,
			nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(data.hWnd, true);

		mWindowData.backTexture
			= CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);


		mWindowData.backbuffer = CreateCompatibleDC(mWindowData.hdc);
		HBITMAP dafaultBitmap
			= (HBITMAP)SelectObject(mWindowData.backbuffer, mWindowData.backTexture);
		
		DeleteObject(dafaultBitmap);

		// 메모리 해재 해주어야한다.
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		mBrushes[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)eBrushColor::Gray] = CreateSolidBrush(RGB(71, 71, 71));
		mBrushes[(UINT)eBrushColor::White] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	}

	void Application::Tick()
	{
		Time::Tick();
		Input::Tick();
		SceneManager::Tick();

		Application::Render();
	}

	void Application::Render()
	{
		// Clear
		Rectangle(mWindowData.backbuffer,
			-1, -1, 
			mWindowData.width + 1, mWindowData.height + 1);

		// 더블 버퍼링
		// ===========================================
		SceneManager::Render(mWindowData.backbuffer);

		Time::Render(mWindowData.backbuffer);
		Input::Render(mWindowData.backbuffer);

		// BitBle 함수는 DC간에 이미지를 복사 해주는 함수
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height,
			mWindowData.backbuffer, 0, 0, SRCCOPY);
		// ===========================================
	}

	void Application::Clear()
	{
		SceneManager::Release();
		ResourceManager::Release();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hWnd, mWindowData.backbuffer);

		for (HPEN pen : mPens)
		{
			if (!pen)
				continue;

			DeleteObject(pen);
		}

		for (HBRUSH brush : mBrushes)
		{
			if (!brush)
				continue;

			DeleteObject(brush);
		}
	}
}
