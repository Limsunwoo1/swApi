#include "TilePalette.h"
#include "Image.h"
#include "ResourceManager.h"

namespace sw
{
	TilePalette::TilePalette()
	{
		mImage = ResourceManager::GetInstance()->Load<Image>(L"TileAtlas", L"..\\Resource\\Image\\Tile.bmp");
	}

	TilePalette::~TilePalette()
	{

	}

	void TilePalette::Tick()
	{

	}

	void TilePalette::Render(HDC hdc)
	{

	}
}