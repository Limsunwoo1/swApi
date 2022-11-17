#include "Rigidbody.h"
#include "Time.h"
#include "UtilMath.h"
namespace sw
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(400.f)
	{
		mLimitVelocity.x = 200.f;
		mLimitVelocity.y = 1000.f;

		mbGround = false;
		mGravity = Vector2(0.0f, 900.f);
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Tick()
	{
		// �̵�
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ���Ѵ�
		//mVelocity += mAccelation * Time::GetInstance()->DeltaTime();

		if (mbGround)
		{
			// ������ ������
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = sw::UtilMath::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// ���߿� ������
			mVelocity += mGravity * Time::GetInstance()->DeltaTime();
		}


		// �ִ� �ӵ� ����
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = sw::UtilMath::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		// ������ ���� (����� ���� ����, �ӵ��� 0 �� �ƴҶ�)
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	// �ӵ� �ݴ� �������� �������� ����
		//	Vector2 friction = -mVelocity;
		//	friction = 
		//		friction.Normalize() * mFriction * mMass * Time::GetInstance()->DeltaTime();

		//	// ���������� ���� �ӵ� ���ҷ� ���� �ӵ����� �� ū ���
		//	float mVelocityLength = mVelocity.Length();
		//	float frictionLength = friction.Length();
		//	if (mVelocityLength < frictionLength)
		//	{
		//		// �ӵ��� 0 ���� �����
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� ����
		//		mVelocity += friction;
		//	}
		//}

		// �ӵ��� �°� ��ü�� �̵���Ų��
		Vector2 pos = GetOwner()->GetPos();
		if (!mbGround)
		{
			mVelocity = mVelocity + mGravity * Time::GetInstance()->DeltaTime();
			pos = pos + mVelocity * Time::GetInstance()->DeltaTime();
		}

		pos = pos + mForce * Time::GetInstance()->DeltaTime();
		GetOwner()->SetPos(pos);
		mForce.clear();
	}

	void Rigidbody::Render(HDC hdc)
	{

	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}