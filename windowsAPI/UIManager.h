#pragma once
#include "Common.h"
#include "UiBase.h"

namespace sw
{
	/// <summary>
	/// 플레이어의 조작에 영향을 받지 않죠 (위치 크기등등)
	/// 전체 화면 UI
	/// 기본 UI 
	/// HUD 이미지와 정보만 잇는 UI
	/// 버튼
	/// 내 UI 내 자식구조로 여러가지 다른 ui들을 구성해서
	/// 같이 움직이는 하나의 큰 UI 도 될수 있따.
	/// </summary>
	
	class UIManager
	{
		SINGLE(UIManager);

	public:
		void Initialize();
		void OnLoad(eUIType type);
		void Tick();
		void Render(HDC hdc);
		void OnComplete(UiBase* addUI);
		void OnFail();

		void Push(eUIType type);
		void Pop(eUIType type);

	private:
		std::unordered_map<eUIType, UiBase*> mUIs;
		std::queue<eUIType> mRequestUIQueue;
		std::stack<UiBase*> mUiBases;
		UiBase* mCurrentData;
	};
}

