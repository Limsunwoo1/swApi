#include "Application.h"
#include "windowsAPI.h"
#include "Application.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "Time.h"
#include "Input.h"
#include "CollisionManager.h"
#include "Camera.h"

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

		Time::GetInstance()->Initialize();
		Input::GetInstance()->Initialize();
		SceneManager::GetInstance()->Initalize();
		Camera::GetInstance()->Initialize();
	}

	void Application::initializeAtlasWindow(WindowData data)
	{
		mAtlasWindowData = data;
		mAtlasWindowData.hdc = GetDC(data.hWnd);
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

		// �޸� ���� ���־���Ѵ�.
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		mBrushes[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)eBrushColor::Black] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)eBrushColor::Gray] = CreateSolidBrush(RGB(71, 71, 71));
		mBrushes[(UINT)eBrushColor::White] = (HBRUSH)GetStockObject(WHITE_BRUSH);

		mMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINDOWSAPI));
	}

	void Application::SetMenuBar(bool power)
	{
		SetMenu(mWindowData.hWnd, mMenu);

		// Ŭ���̾�Ʈ ũ��� ����
		RECT rect = { 0, 0, mWindowData.width, mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);

		//������ ũ�⺯��
		SetWindowPos(mWindowData.hWnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);

		ShowWindow(mWindowData.hWnd, true);
	}

	void Application::Tick()
	{
		Time::GetInstance()->Tick();
		Input::GetInstance()->Tick();
		Camera::GetInstance()->Tick();

		CollisionManager::GetInstance()->Tick();
		SceneManager::GetInstance()->Tick();
		

		Application::Render();

		// ��� ������Ʈ ������ �� add, delete 
		EventManager::GetInstance()->Tick();
	}

	void Application::Render()
	{
		// Clear
		Rectangle(mWindowData.backbuffer,
			-1, -1, 
			mWindowData.width + 1, mWindowData.height + 1);

		// ���� ���۸�
		// ===========================================
		SceneManager::GetInstance()->Render(mWindowData.backbuffer);

		Camera::GetInstance()->Render(mWindowData.backbuffer);
		Time::GetInstance()->Render(mWindowData.backbuffer);
		Input::GetInstance()->Render(mWindowData.backbuffer);

		// BitBle �Լ��� DC���� �̹����� ���� ���ִ� �Լ�
		BitBlt(mWindowData.hdc, 0, 0, mWindowData.width, mWindowData.height,
			mWindowData.backbuffer, 0, 0, SRCCOPY);
		// ===========================================
	}

	void Application::Clear()
	{
		Application::Distroyer();

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

	void Application::Distroyer()
	{
		// �Ŵ��� Ŭ���� �ν��Ͻ� ����
		SceneManager::GetInstance()->Release();
		ResourceManager::GetInstance()->Release();


		SceneManager::GetInstance()->DistroyInstance();
		ResourceManager::GetInstance()->DistroyInstance();
		Time::GetInstance()->DistroyInstance();
		Input::GetInstance()->DistroyInstance();
		EventManager::GetInstance()->DistroyInstance();
		CollisionManager::GetInstance()->DistroyInstance();
		Camera::GetInstance()->DistroyInstance();
	}
}
