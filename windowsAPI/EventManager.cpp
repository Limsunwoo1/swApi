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
		while (!mEventContainer.empty())
		{
			EventInfo* NewEvent = mEventContainer.front();
			if (NewEvent->Type == EventType::AddObejct)
			{
				if (!NewEvent->Object)
					continue;

				SceneManager::GetInstance()->GetPlayScene()->AddGameObject(NewEvent->Object);
			}
			else if (NewEvent->Type == EventType::DeleteObject)
			{
				if (!NewEvent->Object)
					continue;

				delete NewEvent->Object;
			}

			mEventContainer.pop();
		}
	}
}