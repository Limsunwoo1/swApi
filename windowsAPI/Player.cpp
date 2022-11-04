#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"

#include "Scene.h"
#include "Missile.h"
#include "Image.h"
#include "Animator.h"
#include "Collider.h"


namespace sw
{
	Player::Player()
		: mSpeed(1.0f)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 100.0f, 100.0f });

		if (!mImage)
		{
			mImage = ResourceManager::GetInstance()->Load<Image>(L"PLAYER", L"..\\Resource\\Image\\payer1.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());

		Camera::GetInstance()->SetTarget(this);
	}

	Player::~Player()
	{
		GameObject::~GameObject();
	}

	void Player::Tick()
	{
		GameObject::Tick();

		int speed = 10;
		Vector2 pos = GetPos();
		if (KEY_PRESSE(eKeyCode::W))
		{
			pos.y -= 120.0f * Time::GetInstance()->DeltaTime() * speed;
		}
		if (KEY_PRESSE(eKeyCode::S))
		{
			pos.y += 120.0f * Time::GetInstance()->DeltaTime() * speed;
		}
		if (KEY_PRESSE(eKeyCode::A))
		{
			pos.x -= 120.0f * Time::GetInstance()->DeltaTime() * speed;
		}
		if (KEY_PRESSE(eKeyCode::D))
		{
			pos.x += 120.0f * Time::GetInstance()->DeltaTime() * speed;
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Missile* missile = new Missile();

			Scene* playScene = SceneManager::GetInstance()->GetPlayScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_ProjectTile);

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
		finalPos.x = pos.x - (scale.x * 0.5f);
		finalPos.y = pos.y - (scale.y * 0.5f);

		Vector2 rect;
		rect.x = scale.x ;
		rect.y = scale.y ;

		finalPos = Camera::GetInstance()->CalculatePos(finalPos);

		/*TransparentBlt(hdc,
			(float)pos.x - (scale.x * 0.5f), (float)pos.y - (scale.y * 0.5f),
			scale.x, scale.y,
			mImage->GetDC(),
			0, 0, mImage->GetWidth(), mImage->GetHeight(),
			RGB(255, 0, 255));*/

		// 총알 충돌박스 만들기
		// 플레이어 scale 다시생각해보기 
		
		TransparentBlt(hdc, 
			finalPos.x, finalPos.y,
			rect.x, rect.y,
			mImage->GetDC(), 
			0, 0, mImage->GetWidth(), mImage->GetHeight(), 
			RGB(255,0,255));

		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
	}
}
