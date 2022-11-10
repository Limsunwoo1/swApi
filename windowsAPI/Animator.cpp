#include "Animator.h"
#include "Animation.h"
#include "Image.h"
#include "ResourceManager.h"
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
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Tick();

			// 애니매이션이 끝나도 루프가 재생이면
			// 리셋후 재시작
			if (mbLoop && mPlayAnimation->isComplete())
			{
				Animation::Event& Event = 
					mPlayAnimation->CompleteEvent();

				Event();
				mPlayAnimation->Reset();
			}

			if (!mbLoop && mPlayAnimation->isComplete())
			{
				mPlayAnimation->CompleteEvent();
				Play(L"IDEL", true);
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

	//Sprte 이미지를 Animation 으로 만들어주는 함수
	void Animator::CreatAnimations(const std::wstring& name, const std::wstring& path
		, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images;
		for (auto& file : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring filename = file.path().filename();
			std::wstring fullName = path + L"\\" + filename;
			Image* image = ResourceManager::GetInstance()->Load<Image>(filename, fullName);
			images.push_back(image);

			// 제일큰 리소스의 크기 셋팅
			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		mSpriteSheet = Image::Create(name, width * fileCount, height);
		int index = 0;
		for (Image* image : images)
		{
			BitBlt(mSpriteSheet->GetDC(), width * index, 0, image->GetWidth(), image->GetHeight(), 
				image->GetDC(), 0, 0, SRCCOPY);

			index++;
		}

		Animator::CreateAnimation(name, mSpriteSheet
			, Vector2(0.0f, 0.0f), Vector2(width, height)
			, offset, fileCount, duration);
	}
	void Animator::Play(const std::wstring name, bool bLoop)
	{ 
		if (mPlayAnimation != nullptr)
		{
			Animation::Event StartEvent =
				mPlayAnimation->StartEvent();

			StartEvent();
		}

		Animation* prevAnimation = mPlayAnimation;

		mPlayAnimation = FindAnimation(name);
		mPlayAnimation->Reset();
		mbLoop = bLoop;

		// 이전 애니매이션에 End 이벤트 호출
		if (prevAnimation != mPlayAnimation && prevAnimation != nullptr)
		{
			Animation::Event EndEvent =
				prevAnimation->EndEvent();

			EndEvent();
		}
	}

	bool Animator::bPlayAnimation()
	{
		if (mPlayAnimation)
			return true;
		
		return false;
	}
}