#pragma once
#include "Common.h"

namespace sw
{	
	class GameObject;

	enum class EventType
	{
		NONE,
		AddObejct,
		DeleteObject,
		End,
	};

	struct EventInfo
	{
		EventType Type;
		GameObject* Object;

		EventInfo() : Type(EventType::NONE), Object(nullptr) {};
		EventInfo(EventType InType) : Type(InType), Object(nullptr) {};
		EventInfo(EventType InType, GameObject* InObject) : Type(InType), Object(InObject) {};
		~EventInfo() = default;
	};

	class EventManager
	{
		SINGLE(EventManager);

	public:
		void Tick();
		void EventPush(EventInfo InEvent) { mEventContainer.push_back(InEvent); }

	private:
		std::vector<EventInfo> mEventContainer;
	};
}

