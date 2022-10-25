#include "Application.h"
#include "SceneManager.h"
#include "Time.h"
#include "Input.h"

namespace sw
{
	Application Application::mInstance;


	Application::Application()
	{
		mWindowData.clear();
	}

	Application::~Application()
	{
		SceneManager::Release();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hWnd, mWindowData.backbuffer);
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
		// ��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�� ���
		RECT rect = { 0,0, data.width, data.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// ������ ũ�� ����
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

		// ���� ���۸�
		// ===========================================
		Time::Render(mWindowData.backbuffer);
		Input::Render(mWindowData.backbuffer);

		SceneManager::Render(mWindowData.backbuffer);

		// BitBle �Լ��� DC���� �̹����� ���� ���ִ� �Լ�
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height,
			mWindowData.backbuffer, 0, 0, SRCCOPY);
		// ===========================================
	}
}
