#pragma once
#include "Common.h"

namespace sw
{
	class Application
	{
	public:
		static Application& GetInstance()
		{
			static Application mInstance;
			return mInstance;
		}


		void Initialize(WindowData data);
		void Tick();
		void Render();

		WindowData GetWindowData() { return mWindowData; }

	private:
		Application();
		~Application();

		void initialize(WindowData data);

	private:
		//static Application mInstance;
		WindowData mWindowData;
		HPEN mPens[(UINT)ePenColor::End];
		HBRUSH mBrushes[(UINT)eBrushColor::End];
	};
}

