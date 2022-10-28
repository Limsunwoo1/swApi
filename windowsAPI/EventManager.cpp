#include "EventManager.h"
#include "SceneManager.h"
#include "Scene.h"

namespace sw
{
	EventManager::EventManager()
	{

	}

	EventManager::~EventManager()
	{

	}

	void EventManager::Tick()
	{
		for (EventInfo* newEvent : mEventContainer)
		{
			if (newEvent->Type == EventType::AddObejct) 
			{
				if (!newEvent->Object) 
					continue;

				SceneManager::GetInstance()->GetPlayScene()->AddGameObject(newEvent->Object);
			}
			else if (newEvent->Type == EventType::DeleteObject)
			{
				if (!newEvent->Object)
					continue;

				delete newEvent->Object;
			}

			delete newEvent;
		}

		mEventContainer.clear();
	}
}