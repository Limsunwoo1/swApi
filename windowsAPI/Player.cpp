#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"

#include "Scene.h"
#include "Missile.h"
#include "Image.h"
#include "ResourceManager.h"


namespace sw
{
	Player::Player()
		: mSpeed(1.0f)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 3.0f, 3.0f });

		if (!mImage)
		{
			mImage = ResourceManager::Load<Image>(L"PLAYER", L"..\\Resource\\Image\\payer1.bmp");
		}
	}

	Player::~Player()
	{

	}

	void Player::Tick()
	{
		int speed = 10;
		Vector2 pos = GetPos();
		if (KEY_PRESSE(eKeyCode::W))
		{
			pos.y -= 120.0f * Time::DeltaTime() * speed;
		}
		if (KEY_PRESSE(eKeyCode::S))
		{
			pos.y += 120.0f * Time::DeltaTime() * speed;
		}
		if (KEY_PRESSE(eKeyCode::A))
		{
			pos.x -= 120.0f * Time::DeltaTime() * speed;
		}
		if (KEY_PRESSE(eKeyCode::D))
		{
			pos.x += 120.0f * Time::DeltaTime() * speed;
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Missile* missile = new Missile();

			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(missile);

			Vector2D playerpos = GetPos();
			Vector2D playerscale = GetScale() / 2.0f;

			Vector2D missileScale = missile->GetScale();

			missile->SetPos((playerpos + playerscale) - (missileScale / 2.0f));
		}

		SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();


		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.0f));
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.y / 2.0f));

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		/*TransparentBlt(hdc,
			(float)pos.x - (scale.x * 0.5), (float)pos.y - (scale.y * 0.5),
			scale.x, scale.y,
			mImage->GetDC(),
			0, 0, mImage->GetWidth(), mImage->GetHeight(),
			RGB(255, 0, 255));*/


		TransparentBlt(hdc, 
			finalPos.x, finalPos.y,
			rect.x, rect.y,
			mImage->GetDC(), 
			0, 0, mImage->GetWidth(), mImage->GetHeight(), 
			RGB(255,0,255));
	}
}
