#pragma once
#include "Common.h"


namespace sw
{
	class Time
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static float DeltaTime() { return mDeltaTime; }

		
	private:
		// CPU 고유 진동수 ( 1초당 명번) 1초 12000번 진동하는CPU
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;
	};
}

