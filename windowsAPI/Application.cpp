#include "Application.h"


namespace sw
{
	Application Application::mInstance;


	Application::Application()
	{
		mWindowDate.clear();
	}

	Application::~Application()
	{

	}

	void Application::Initialize(WindowData data)
	{
		mWindowDate = data;
		mWindowDate.hdc = GetDC(data.hWnd);
	}

	void Application::Tick()
	{

	}
}
