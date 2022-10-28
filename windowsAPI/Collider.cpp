#include "Collider.h"
#include "GameObject.h"
#include "Application.h"

namespace sw
{
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mScale(Vector2::One)
	{
		mScale = Vector2(150.0f, 150.0f);
	}

	Collider::~Collider()
	{

	}

	void Collider::Tick()
	{
		GameObject* owner = GetOwner();
		mPos = owner->GetPos() + mOffset;
	}

	void Collider::Render(HDC hdc)
	{
		HPEN green = Application::GetInstance().GetPen(ePenColor::Green);
		Pen pen(hdc, green);

		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);

		HPEN red = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		Pen pen1(hdc, red);

		Rectangle(hdc, mPos.x - (mScale.x * 0.5), mPos.y - (mScale.y * 0.5)
			,mPos.x + (mScale.x * 0.5), mPos.y + (mScale.y * 0.5));
	}
}