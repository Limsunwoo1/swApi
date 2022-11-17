#pragma once
#include "Entity.h"
#include "Common.h"

namespace sw
{
	class UiBase : public Entity
	{
	public:
		UiBase(eUIType type);
		virtual ~UiBase();

		// UI 가 로드 되었을때 불리는 초기화 함수
		void Initialize();

		// UI 가 활성화되면 불리는 함수
		void Active();

		// UI 가 비활성화되면 불리는 함수
		void InActive();

		// UI가 업데이트 될때마다 호출되는 함수
		void Tick();
		void Render(HDC hdc);

		// UI가 사라질때 호출되는 함수
		void UIClear();

		virtual void OnInit() {};
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnTick() {};
		virtual void OnUIClear() {};

		eUIType GetType() { return mType; }
		bool GetIsFullScreen() { return mbFullScreen; }
		void SetIsFullScreen(bool enable) { mbFullScreen = enable; }

	private:
		eUIType mType;
		bool mbFullScreen;
		bool mbEnable;
	};
}

