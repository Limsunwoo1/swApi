#include "BackGround.h"
#include "ResourceManager.h"

#include "Image.h"

namespace sw
{
	BackGround::BackGround()
		: mImage(nullptr)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
	}

	BackGround::~BackGround()
	{

	}

	void BackGround::Initialize()
	{

	}

	void BackGround::Tick()
	{
		GameObject::Tick();
	}

	void BackGround::Render(HDC hdc)
	{
		if (mImage == nullptr)
			return;

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 finalPos = pos;

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		TransparentBlt(hdc,
			finalPos.x, finalPos.y,
			1920, 1080,
			mImage->GetDC(),
			0, 0, mImage->GetWidth(), mImage->GetHeight(),
			RGB(255, 0, 255));
		
		GameObject::Render(hdc);
	}
	void BackGround::SetImage(const std::wstring& key, const std::wstring& filename)
	{
		std::wstring path = L"..\\Resource\\Image\\";
		path += filename;

		mImage = ResourceManager::GetInstance()->Load<Image>(key, path);
	}
}
