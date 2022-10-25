#pragma once
#include "Common.h"

namespace sw
{
	class Application
	{
	public:
		static Application& GetInstance()
		{
			return mInstance;
		}


		void Initialize(WindowData data);
		void Tick();
		void Render();

	private:
		Application();
		~Application();

		void initialize(WindowData data);

	private:
		static Application mInstance;
		WindowData mWindowData;
	};
}

