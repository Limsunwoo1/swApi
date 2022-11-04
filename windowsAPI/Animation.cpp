#include "Animation.h"
#include "GameObject.h"
#include "Image.h"
#include "Animator.h"
#include "Camera.h"

namespace sw
{
	Animation::Animation()
	{

	}

	Animation::~Animation()
	{

	}

	void Animation::Tick()
	{
	}

	void Animation::Render(HDC hdc)
	{
		GameObject* gameobj = mAnimator->GetOwner();
		Vector2 pos = gameobj->GetPos();

		if (mAffectedCamera)
			pos = Camera::GetInstance()->CalculatePos(pos);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 127; // 0 - 225

		AlphaBlend(hdc
			, (int)pos.x - mSpriteSheet[mSpriteIndex].size.x / 2.0f
			, (int)pos.y - mSpriteSheet[mSpriteIndex].size.y / 2.0f
			, (int)mSpriteSheet[mSpriteIndex].size.x
			, (int)mSpriteSheet[mSpriteIndex].size.y
			, mImage->GetDC()
			, (int)mSpriteSheet[mSpriteIndex].LeftTop.x
			, (int)mSpriteSheet[mSpriteIndex].LeftTop.y
			, (int)mSpriteSheet[mSpriteIndex].size.x
			, (int)mSpriteSheet[mSpriteIndex].size.y
			, func);
	}

	void Animation::Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offest
		, float columLength, UINT spriteLegnth, float duration, bool bAffectedCamera)
	{
		mImage = image;
		mAffectedCamera = bAffectedCamera;

		for (int i = 0; i < spriteLegnth; i++)
		{
			Sprite sprite;
			sprite.LeftTop.x = leftTop.x + (columLength * (float)i);
			sprite.LeftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offest = offest;
			sprite.duration = duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
	}

}