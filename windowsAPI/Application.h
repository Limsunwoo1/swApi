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

		void Clear();

		WindowData GetWindowData() { return mWindowData; }
		const HPEN &GetPen(ePenColor color)const { return mPens[(UINT)color]; }
		const HBRUSH &GetBrush(eBrushColor color)const { return mBrushes[(UINT)color]; }

	private:
		Application();
		~Application();

		void initialize(WindowData data);
		void Distroyer();

	private:
		//static Application mInstance;
		WindowData mWindowData;


		HPEN mPens[(UINT)ePenColor::End];
		HBRUSH mBrushes[(UINT)eBrushColor::End];
	};
}

