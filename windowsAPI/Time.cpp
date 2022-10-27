#include "Time.h"
#include "Application.h"

namespace sw
{
	static int CallCount = 0;
	static float AccDeltaTime = 0.0f;
	static int fps = 0;

	LARGE_INTEGER Time::mCpuFrequency;
	LARGE_INTEGER Time::mPrevFrequency;
	LARGE_INTEGER Time::mCurFrequency;
	float Time::mDeltaTime;

	void Time::Initialize()
	{
		// CPU 초당 반복되는 진동수를 얻어오는 함수
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램 시작 했을때 cpu의 클럭 수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequendy
			= mCurFrequency.QuadPart - mPrevFrequency.QuadPart;
		mDeltaTime = differenceFrequendy / mCpuFrequency.QuadPart;

		// 다시 이전의 값을 새로운 지금 값으로 세팅
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

		++CallCount;
		AccDeltaTime += mDeltaTime;
	}

	void Time::Render(HDC hdc)
	{
		wchar_t szFloat[50] = {};
		// 델타 타임
		// 한프레임 도는 동안 총 걸린시간

		/*int fps = 1.0f / mDeltaTime;

		swprintf_s(szFloat, 50, L"fps : %d", fps);
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 10, 10, szFloat, strLen);*/
		
		if (AccDeltaTime > 1.f)
		{
			fps = CallCount;
			CallCount = 0;
			AccDeltaTime = 0.f;

			wchar_t szBuffer[255] = {};
			swprintf_s(szBuffer, L"FPS : %d, DT : %lf", fps, mDeltaTime);
			SetWindowText(Application::GetInstance().GetWindowData().hWnd, szBuffer);
		}
	}
}
