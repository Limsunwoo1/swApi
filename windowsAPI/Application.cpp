#include "Application.h"
#include "SceneManager.h"

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
	}

	void Application::Initialize(WindowData data)
	{
		mWindowDate = data;
		mWindowDate.hdc = GetDC(data.hWnd);

		SceneManager::Initalize();
	}

	void Application::Tick()
	{
		SceneManager::Tick();
		SceneManager::Render(mWindowDate.hdc);
	}
}
