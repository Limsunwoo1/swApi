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

			// �ִϸ��̼��� ������ ������ ����̸�
			// ������ �����
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

	std::wstring Animator::CreateAniamtionKey(std::wstring path)
	{
		std::wstring keyString = path;

		// ��ϸ��̼� ���� �̸� �߷�
		UINT pos = keyString.find_last_of(L"\\");
		std::wstring tail = keyString.substr(pos + 1, keyString.length());
		keyString = keyString.substr(0, pos);

		// �ִϸ��̼� ������Ʈ �̸� ����
		pos = keyString.find_last_of(L"\\");
		std::wstring head = keyString.substr(pos + 1, keyString.length());
		keyString = head + tail;

		return keyString;
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
			MessageBox(nullptr, L"�ߺ� Ű �ִϸ��̼� ����",
				L"�ִϸ��̼� ���� ����!", MB_OK);

			return;
		}

		animation = new Animation();
		animation->Create(image, leftTop, Size, offset
			, spriteLegth, duration, bAffectedCamera);

		animation->SetName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
	}

	//Sprte �̹����� Animation ���� ������ִ� �Լ�
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
			std::wstring cnt = std::to_wstring(fileCount);
			std::wstring filename = file.path().filename();
			std::wstring key = CreateAniamtionKey(path);
			std::wstring fullName = path + L"\\" + filename;
			Image* image = ResourceManager::GetInstance()->Load<Image>(key + cnt, fullName);
			images.push_back(image);

			// ����ū ���ҽ��� ũ�� ����
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
		if (mPlayAnimation == nullptr)
		{
			mPlayAnimation = FindAnimation(name);
			mPlayAnimation->Reset();
			mbLoop = bLoop;

			Animation::Event StartEvent =
				mPlayAnimation->StartEvent();

			StartEvent();
		}
		Animation* prevAnimation = mPlayAnimation;

		// ���� �ִϸ��̼ǿ� End �̺�Ʈ ȣ��
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