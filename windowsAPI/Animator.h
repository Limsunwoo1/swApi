#pragma once
#include "Component.h"

namespace sw
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Tick() override;

	private:


	};
}

