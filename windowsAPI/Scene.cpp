#include "Scene.h"
#include "GameObject.h"

namespace sw
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			delete mObjects[i];
			mObjects[i] = nullptr;
		}
	}

	void Scene::Initialize()
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			mObjects[i]->Initialize();
		}
	}

	void Scene::Tick()
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			mObjects[i]->Tick();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (int i = 0; i < mObjects.size(); i++)
		{
			mObjects[i]->Render(hdc);
		}
	}

	void Scene::AddGameObject(GameObject* object)
	{
		if (object == nullptr)
			return;
		mObjects.push_back(object);
	}
}
