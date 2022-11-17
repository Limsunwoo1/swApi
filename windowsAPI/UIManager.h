#pragma once
#include "Common.h"
#include "UiBase.h"

namespace sw
{
	/// <summary>
	/// �÷��̾��� ���ۿ� ������ ���� ���� (��ġ ũ����)
	/// ��ü ȭ�� UI
	/// �⺻ UI 
	/// HUD �̹����� ������ �մ� UI
	/// ��ư
	/// �� UI �� �ڽı����� �������� �ٸ� ui���� �����ؼ�
	/// ���� �����̴� �ϳ��� ū UI �� �ɼ� �ֵ�.
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

