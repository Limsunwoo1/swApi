#pragma once
#include "Component.h"

namespace sw
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetScale(Vector2D scale) { mScale = scale; }
		void SetPos(Vector2D pos) { mPos = pos; }
		void SetOffset(Vector2D pos) { mOffset = pos; }

	private:
		Vector2D mOffset;
		Vector2D mPos;
		Vector2D mScale;
	};
}

