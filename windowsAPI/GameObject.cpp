#include "GameObject.h"
#include "Component.h"

namespace sw
{
	GameObject::GameObject()
		: mPos {0.0f, 0.0f}
		, mScale {1.0f, 1.0f}
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Tick()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Tick();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		// ��� ������Ʈ�� Render ȣ��
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Render(hdc);
		}
	}
}
