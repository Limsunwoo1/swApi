#include "UIManager.h"
#include "Application.h"

namespace sw
{
	UIManager::UIManager()
	{

	}

	UIManager::~UIManager()
	{

	}

	void UIManager::Initialize()
	{
		// 여기에서 ui 메모리에 할당하면 된다.

		UiBase* newUI = new UiBase(eUIType::HP);
		mUIs.insert(std::make_pair(eUIType::HP, newUI));

		newUI = new UiBase(eUIType::MP);
		mUIs.insert(std::make_pair(eUIType::MP, newUI));

		newUI = new UiBase(eUIType::SHOP);
		mUIs.insert(std::make_pair(eUIType::SHOP, newUI));

		newUI = new UiBase(eUIType::INVENTORY);
		mUIs.insert(std::make_pair(eUIType::INVENTORY, newUI));

		newUI = new UiBase(eUIType::OPTION);
		mUIs.insert(std::make_pair(eUIType::OPTION, newUI));

	}

	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UiBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}

	void UIManager::Tick()
	{


		if (mRequestUIQueue.size() > 0)
		{
			//UI 로드 해줘
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();

			OnLoad(requestUI);
		}
	}


	void UIManager::Render(HDC hdc)
	{
	}
	void UIManager::OnComplete(UiBase* addUI)
	{
	}
	void UIManager::OnFail()
	{
	}
	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}
	void UIManager::Pop(eUIType type)
	{
	}
}
