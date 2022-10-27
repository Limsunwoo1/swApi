#pragma once
#include "Component.h"

namespace sw
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Tick() override;

	private:


	};
}

