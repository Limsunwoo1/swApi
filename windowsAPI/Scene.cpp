#include "Scene.h"
#include "GameObject.h"

namespace sw
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
		
	}

	void Scene::Initialize()
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			if (!mObjects[i])
				continue;

			mObjects[i]->Initialize();
		}
	}

	void Scene::Tick()
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			if (!mObjects[i])
				continue;

			mObjects[i]->Tick();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			if (!mObjects[i])
				continue;

			mObjects[i]->Render(hdc);
		}
	}

	void Scene::AddGameObject(GameObject* object)
	{
		if (object == nullptr)
			return;

		mObjects.push_back(object);
	}

	void Scene::Enter()
	{
	}

	void Scene::Exit()
	{
	}

	void Scene::Release()
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			if (!mObjects[i])
				continue;

			delete mObjects[i];
			mObjects[i] = nullptr;
		}
	}
}
