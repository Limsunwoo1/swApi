#include "Meteor.h"
#include "Time.h"

namespace sw
{
	const Vector2D Gravity = { 0.0f, 9.8f };

	Meteor::Meteor()
		: speed ({ 0.0f, 1.0f })
	{
		SetScale({ 50.f,50.f });
	}

	Meteor::~Meteor()
	{

	}

	void Meteor::Tick()
	{
		float delta = Time::DeltaTime();
		Vector2D pos = GetPos();

		if (pos.y > 1080)
			return;
		speed += Gravity * delta;
		pos += speed * delta * 50;

		SetPos(pos);
	}

	void Meteor::Render(HDC hdc)
	{
		Vector2D pos = GetPos();
		Vector2D scale = GetScale();
		
		Ellipse(hdc, pos.x, pos.y, pos.x +scale.x, pos.y + scale.y);
	}
}