#include "Animator.h"
#include "Animation.h"
#include "GameObject.h"


namespace sw
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mPlayAnimation(nullptr)
		, mbLoop(false)
	{

	}

	Animator::~Animator()
	{

	}

	void Animator::Tick()
	{
		Animator::AnimationSwap();

		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Tick();

			// 애니매이션이 끝나도 루프가 재생이면
			// 리셋후 재시작
			if (mbLoop && mPlayAnimation->isComplete())
			{
				mCompleteEvent();
				mPlayAnimation->Reset();
			}

			if (!mbLoop && mPlayAnimation->isComplete())
			{
				mCompleteEvent();
				Play(L"IDEL", eObjectState::IDEL, true);
				mCurState = eObjectState::IDEL;
			}
		}
	}
	void Animator::Render(HDC hdc)
	{
		if (mPlayAnimation != nullptr)
			mPlayAnimation->Render(hdc);
	}
	Animation* Animator::FindAnimation(const std::wstring name)
	{
		std::map<const std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	void Animator::CreateAnimation(const std::wstring name, Image* image
		, Vector2 leftTop, Vector2 Size, Vector2 offset, UINT spriteLegth
		, float duration, bool bAffectedCamera)
	{
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
		{
			MessageBox(nullptr, L"중복 키 애니메이션 생성",
				L"애니메이션 생성 실패!", MB_OK);

			return;
		}

		animation = new Animation();
		animation->Create(image, leftTop, Size, offset
			, spriteLegth, duration, bAffectedCamera);

		animation->SetName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
	}
	void Animator::Play(const std::wstring name, eObjectState state, bool bLoop)
	{ 
		this->GetOwner()->SetState(state);

		mStartEvent();

		Animation* prevAnimation = mPlayAnimation;

		mPlayAnimation = FindAnimation(name);
		mPlayAnimation->Reset();
		mbLoop = bLoop;

		// 이전 애니매이션에 End 이벤트 호출
		if (prevAnimation != mPlayAnimation)
			mEndEvent();
	}
	
	void Animator::AnimationSwap()
	{
		if (mCurState == this->GetOwner()->GetState())
			return;
		
		mCurState = this->GetOwner()->GetState();

		std::wstring str = L"";
		eObjectState obj = eObjectState::END;
		bool mb = true;

		switch (mCurState)
		{
		case eObjectState::IDEL:
		{
			str = L"IDEL";
			obj = eObjectState::IDEL;
		}
		break;

		case eObjectState::UP:
		{
			str = L"UP";
			obj = eObjectState::UP;
		}
		break;

		case eObjectState::DOWN:
		{
			str = L"DOWN";
			obj = eObjectState::DOWN;
		}
		break;

		case eObjectState::RIGHT:
		{
			str = L"RIGHT";
			obj = eObjectState::RIGHT;
		}
		break;

		case eObjectState::LEFT:
		{
			str = L"LEFT";
			obj = eObjectState::LEFT;
		}
		break;

		case eObjectState::ATTACK_1:
		{
			str = L"ATTACK_1";
			obj = eObjectState::ATTACK_1;
			mb = false;
		}
		break;

		case eObjectState::ATTACK_2:
		{
			str = L"ATTACK_2";
			obj = eObjectState::ATTACK_2;
			mb = false;
		}
		break;
		}

		Play(str, obj, mb);
	}
}