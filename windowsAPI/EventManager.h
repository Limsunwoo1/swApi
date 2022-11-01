#pragma once
#include "Common.h"

namespace sw
{	
	class GameObject;
	class EventManager
	{
		SINGLE(EventManager);

	public:
		void Tick();
		void EventPush(EventInfo& InEvent) { mEventList.push(InEvent); }

	private:
		std::queue<EventInfo> mEventList;
	};
}

