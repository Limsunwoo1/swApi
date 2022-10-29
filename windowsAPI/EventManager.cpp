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
		while (!mEventList.empty())
		{
			EventInfo& NewEvent = mEventList.front();

			switch (NewEvent.Type)
			{
				case EventType::AddObejct:
					{
						if (NewEvent.Parameter2)
						{
							SceneManager::GetInstance()->GetPlayScene()->
								AddGameObject(
									(GameObject*)NewEvent.Parameter2,
									*((eColliderLayer*)NewEvent.Parameter1));
						}
					}
					break;

				case EventType::DeleteObject:
					{
						// iter 를 이용하여 scene에 백터 크기도 줄여줘야한다
					}
					break;
			}

			delete NewEvent.Parameter1;
			mEventList.pop();
		}
	}
}