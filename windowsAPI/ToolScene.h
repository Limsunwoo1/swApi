#pragma once
#include "Scene.h"
#include "TilePalette.h"

namespace sw
{
	class Image;
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		virtual ~ToolScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

		Image* GetAtlasImage() {return mTilePalette->GetAtlasImage();}

	private:
		TilePalette* mTilePalette;

	};
}

