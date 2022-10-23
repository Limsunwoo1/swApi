#pragma once
#include "GameObject.h"

namespace sw
{
	class Meteor : public GameObject
	{
	public:
		Meteor();
		virtual ~Meteor();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Vector2D speed;
	};
}

