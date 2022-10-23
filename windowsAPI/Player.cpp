#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"

#include "Scene.h"
#include "Missile.h"



namespace sw
{
	Player::Player()
		: mSpeed(1.0f)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 100.0f, 100.0f });
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
		Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
	}
}
