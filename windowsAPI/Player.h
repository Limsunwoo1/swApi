#pragma once
#include "GameObject.h"

namespace sw
{
	class Image;
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		float mSpeed;
		Image* mImage;
	};
}

