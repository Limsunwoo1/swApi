#include "Application.h"
#include "SceneManager.h"
#include "Time.h"
#include "Input.h"

namespace sw
{
	Application Application::mInstance;


	Application::Application()
	{
		mWindowDate.clear();
	}

	Application::~Application()
	{
		SceneManager::Release();

		ReleaseDC(mWindowDate.hWnd, mWindowDate.hdc);
		ReleaseDC(mWindowDate.hWnd, mWindowDate.backhdc);
	}

	void Application::Initialize(WindowData data)
	{
		mWindowDate = data;
		mWindowDate.hdc = GetDC(data.hWnd);

		Time::Initialize();
		Input::Initialize();
		SceneManager::Initalize();

		mWindowDate.backhdc = CreateCompatibleDC(mWindowDate.hdc);
		BackBitMap = CreateCompatibleBitmap(mWindowDate.hdc, 1920, 1080);
		BitMap = (HBITMAP)SelectObject(mWindowDate.backhdc, BackBitMap);
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
		Time::Render(mWindowDate.hdc);
		Input::Render(mWindowDate.hdc);

		// 더블 버퍼링
		// ===========================================
		SceneManager::Render(mWindowDate.backhdc);

		BitBlt(mWindowDate.hdc, 0, 0, 1920, 1080,
			mWindowDate.backhdc, 0, 0, SRCCOPY);
		// ===========================================
	}
}
