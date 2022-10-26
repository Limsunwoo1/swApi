#include "BackGround.h"
#include "ResourceManager.h"

#include "Image.h"

namespace sw
{
	BackGround::BackGround()
	{
		if (!mImage)
		{
			mImage = ResourceManager<Image>::Load(L"BackGround", L"..\\Resource\\Image\\BackGround.bmp");
		}
	}

	BackGround::~BackGround()
	{

	}

	void BackGround::Render(HDC hdc)
	{
		BitBlt(hdc, 0,0, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, SRCCOPY);
	}
}
