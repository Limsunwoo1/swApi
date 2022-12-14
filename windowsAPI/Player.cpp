#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "EventManager.h"

#include "Scene.h"
#include "Missile.h"
#include "Image.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Rigidbody.h"


namespace sw
{
	Player::Player()
		: mSpeed(1.0f)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 200.f, 200.0f });

		if (!mImage)
		{
			mImage = ResourceManager::GetInstance()->Load<Image>(L"PLAYER", L"..\\Resource\\Image\\payer1.bmp");
		}

		mAnimator = new Animator();

		AddComponent(mAnimator);
		AddComponent<Rigidbody>();
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(this->GetScale());

		Animation::Sprite sprite;
		sprite.LeftTop = Vector2(0.0f, 0.0f);
		sprite.size = Vector2((mImage->GetWidth() / 8), (mImage->GetHeight() / 8));
		sprite.offest = Vector2(0.0f, 0.0f);
		sprite.duration = 0.1f;

		mAnimator->CreateAnimation(L"IDEL", mImage,
			sprite.LeftTop, sprite.size, sprite.offest,
			7, sprite.duration, true);

		mAnimator->CreatAnimations(L"MonsterAttackW", L"..\\Resource\\Animation\\Monster\\AttackW", Vector2::Zero, 0.4f);

		mAnimator->Play(L"MonsterAttackW",true);


		// Animator 에 현재 진행중인 애니메이션 셋팅후 바인딩
		//animator->StartEvent() = std::bind(&Player::StartEvent, this);
		//animator->EndEvent() = std::bind(&Player::EndEvent, this);
		/*if (mAnimator->bPlayAnimation())
		{
			mAnimator->CompleteEvent() = 
				std::bind(&Player::CompleteEvent, this);
		}*/

		SetState(eObjectState::IDEL);
		Camera::GetInstance()->SetTarget(this);

	}

	Player::~Player()
	{
		GameObject::~GameObject();
	}

	void Player::CompleteEvent()
	{
		Missile* missile = new Missile();
		missile->SetPos(this->GetPos());

		EventInfo info;
		info.Type = EventType::AddObejct;
		info.Parameter1 = new eColliderLayer(eColliderLayer::Monster_ProjectTile);
		info.Parameter2 = missile;

		EventManager::GetInstance()->EventPush(info);
	}

	void Player::Tick()
	{
		GameObject::Tick();

		int speed = 3;
		Vector2 pos = GetPos();

		eObjectState state = GetState();
		if (state != eObjectState::ATTACK_1 && state != eObjectState::ATTACK_2)
		{
			if (KEY_PRESSE(eKeyCode::W))
			{
				//GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -500.0f));
			}
			if (KEY_PRESSE(eKeyCode::S))
			{
				//GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 500.0f));
			}
			if (KEY_PRESSE(eKeyCode::A) &&
				(GetState() != eObjectState::RIGHT))
			{
				GetComponent<Rigidbody>()->AddForce(Vector2(-500.0f, 0.0f));
			}
			if (KEY_PRESSE(eKeyCode::D))
			{
				GetComponent<Rigidbody>()->AddForce(Vector2(500.0f, 0.0f));
			}

			if (KEY_DOWN(eKeyCode::D))
			{
				//SetState(eObjectState::RIGHT);
			}

			if (KEY_UP(eKeyCode::D))
			{
				//SetState(eObjectState::IDEL);
			}

			if (KEY_DOWN(eKeyCode::SPACE))
			{
				Rigidbody* rigidbody = GetComponent<Rigidbody>();
				Vector2 velocity = rigidbody->GetVelocity();
				velocity.y = -700.0f;
				rigidbody->SetVelocity(velocity);

				rigidbody->SetGround(false);
			}
		}


		//if (KEY_DOWN(eKeyCode::SPACE))
		//{
		//	switch (state)
		//	{
		//	case eObjectState::ATTACK_1:
		//	{
		//		//SetState(eObjectState::ATTACK_2);
		//	}
		//	break;

		//	case eObjectState::ATTACK_2:
		//	{
		//		//SetState(eObjectState::ATTACK_3);
		//	}
		//	break;

		//	default:
		//	{
		//		SetState(eObjectState::ATTACK_1);
		//	}
		//	break;

		//	}
		//}

		SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);

		/*transparentblt(hdc,
			(float)pos.x - (scale.x * 0.5f), (float)pos.y - (scale.y * 0.5f),
			scale.x, scale.y,
			mimage->getdc(),
			0, 0, mimage->getwidth(), mimage->getheight(),
			rgb(255, 0, 255));*/

		// 총알 충돌박스 만들기
		// 플레이어 scale 다시생각해보기 
		
		/*TransparentBlt(hdc, 
			finalPos.x, finalPos.y,
			rect.x, rect.y,
			mImage->GetDC(), 
			0, 0, mImage->GetWidth(), mImage->GetHeight(), 
			RGB(255,0,255));*/

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
