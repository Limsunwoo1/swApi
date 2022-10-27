#pragma once
#include "Scene.h"

namespace sw
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

	private:


	};
}
