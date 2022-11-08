#pragma once
#include "Component.h"
#include "Animation.h"

namespace sw
{
	class Animation;
	class Image;
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Play(const std::wstring name, bool bLoop = false);

		void CreateAnimation(const std::wstring name, Image* image
			, Vector2 leftTop, Vector2 Size, Vector2 offset
			, UINT spriteLegth, float duration, bool bAffectedCamera = true);

		Animation::Event& StartEvent() {return mPlayAnimation->StartEvent();}
		Animation::Event& CompleteEvent() { return mPlayAnimation->CompleteEvent(); }
		Animation::Event& EndEvent() { return mPlayAnimation->EndEvent(); }

	private:
		Animation* FindAnimation(const std::wstring name);
		void AnimationSwap();

	private:
		std::map<const std::wstring, Animation*> mAnimations;
		Animation* mPlayAnimation;

		eObjectState mCurState;
		bool mbLoop;
	};
}

