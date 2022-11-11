#pragma once
#include "Common.h"

namespace sw
{
	class Image;
	class TilePalette
	{
	public:
		TilePalette();
		~TilePalette();

		void Tick();
		void Render(HDC hdc);

		//void CreateTile
		//void CreateTiles

		// void Save
		// void Load

		Image* GetAtlasImage() {return mImage;}

	private:
		Image* mImage;
	};
}

