#pragma once
#include "Common.h"
#include "Entity.h"

namespace sw
{
	class GameObject;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

		void AddGameObject(GameObject* object);

		virtual void Release();

	private:
		std::vector<GameObject*> mObjects;
	};
}
