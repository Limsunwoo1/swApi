#include "Camera.h"
#include "Application.h"
#include "Input.h"
#include "Time.h"
#include"GameObject.h"
#include "Image.h"
#include "Time.h"

namespace sw
{
	Camera::Camera()
		: mResolution(Vector2::Zero) // ȭ�� �ػ�
		, mLookPosition(Vector2::Zero)
		, mDistance(Vector2::Zero) // �ػ� �ߤ�����ǥ�� ���� ī�޶��� ������
		, mTarget(nullptr)
		, mEffect(eCameraEffect::None)
		, mCutton(nullptr)
		, mCuttonAlpha(0.0f)
		, mEndTime(3.0f)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::Initialize()
	{
		WindowData data = Application::GetInstance().GetWindowData();
		mResolution = Vector2(data.width, data.height);
		mLookPosition = (mResolution / 2.0f);

		mResolution = Vector2(1600,900);

		mCutton = Image::Create(L"CameraCutton", 1600, 900);
		mEffect = eCameraEffect::FadeIn;
	}

	void Camera::Tick()
	{
		if (mAlphaTime <= mEndTime)
		{
			mAlphaTime += Time::GetInstance()->DeltaTime();
			float ratio = (mAlphaTime / mEndTime);

			if (eCameraEffect::FadeIn == mEffect)
			{
				mCuttonAlpha = 1.0f - ratio;
			}
			else if (eCameraEffect::FadeOut == mEffect)
			{
				mCuttonAlpha = ratio;
			}
		}

		if (KEY_PRESSE(eKeyCode::UP))
		{
			mLookPosition.y -= 600.0f * Time::GetInstance()->DeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::DOWN))
		{
			mLookPosition.y += 600.0f * Time::GetInstance()->DeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			mLookPosition.x -= 600.0f * Time::GetInstance()->DeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			mLookPosition.x += 600.0f * Time::GetInstance()->DeltaTime();
		}


		if (mTarget != nullptr)
			mLookPosition = mTarget->GetPos();

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		if (mEffect == eCameraEffect::None)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

		float width = Application::GetInstance().GetWindowData().width;
		float height = Application::GetInstance().GetWindowData().height;
		AlphaBlend(hdc, 0, 0
			, width, height
			, mCutton->GetDC(), 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, func);
	}
}