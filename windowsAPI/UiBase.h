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

		// UI �� �ε� �Ǿ����� �Ҹ��� �ʱ�ȭ �Լ�
		void Initialize();

		// UI �� Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
		void Active();

		// UI �� ��Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
		void InActive();

		// UI�� ������Ʈ �ɶ����� ȣ��Ǵ� �Լ�
		void Tick();
		void Render(HDC hdc);

		// UI�� ������� ȣ��Ǵ� �Լ�
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

