#pragma once
#include "Common.h"

namespace sw
{
	class Image;
	class GameObject;
	class Camera
	{
		SINGLE(Camera);

	public:
		void Initialize();
		void Tick();
		void Render(HDC hdc);
		Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }
		void SetTarget(GameObject* Gameobj) {mTarget = Gameobj;}

		void SetCameraEffect(eCameraEffect effect) { mEffect = effect; }

	private:
		Vector2 mResolution; // ȭ�� �ػ�
		Vector2 mLookPosition;
		Vector2 mDistance; // �ػ� �ߤ�����ǥ�� ���� ī�޶��� ������
		GameObject* mTarget;

		eCameraEffect mEffect;
		Image* mCutton;		// �������̹���
		float mAlphaTime;
		float mCuttonAlpha;
		float mEndTime;
	};
}

