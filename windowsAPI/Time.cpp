#include "Time.h"

namespace sw
{
	LARGE_INTEGER Time::mCpuFrequency;
	LARGE_INTEGER Time::mPrevFrequency;
	LARGE_INTEGER Time::mCurFrequency;
	float Time::mDeltaTime;

	void Time::Initialize()
	{
		// CPU �ʴ� �ݺ��Ǵ� �������� ������ �Լ�
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷� ���� ������ cpu�� Ŭ�� ��
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequendy
			= mCurFrequency.QuadPart - mPrevFrequency.QuadPart;
		mDeltaTime = differenceFrequendy / mCpuFrequency.QuadPart;

		// �ٽ� ������ ���� ���ο� ���� ������ ����
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		wchar_t szFloat[50] = {};
		// ��Ÿ Ÿ��
		// �������� ���� ���� �� �ɸ��ð�

		int fps = 1.0f / mDeltaTime;

		swprintf_s(szFloat, 50, L"fps : %d", fps);
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 10, 10, szFloat, strLen);
	}
}
