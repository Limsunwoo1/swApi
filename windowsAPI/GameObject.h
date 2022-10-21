#pragma once
#include "Common.h"
#include "Entity.h"

namespace sw
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();


		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() { return mPos; }
		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() { return mScale; }

	private:
		Vector2D mPos;
		Vector2D mScale;
	};
}

