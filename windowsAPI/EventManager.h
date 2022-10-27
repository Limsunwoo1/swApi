#pragma once
#include "Common.h"

namespace sw
{
	class EventManager
	{
		SINGLE(EventManager);

	public:
		void Tick();
		void Render();
		void Initilize();
	};
}

