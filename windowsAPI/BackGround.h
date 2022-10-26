#pragma once
#include "GameObject.h"

namespace sw
{
	class Image;
	class BackGround : public GameObject
	{
	public:
		BackGround();
		virtual ~BackGround();
		virtual void Render(HDC hdc) override;

	private:
		Image* mImage;
	};
}

