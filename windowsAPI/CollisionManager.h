#pragma once
#include "Common.h"

namespace sw
{
	class Collider;
	class Scene;
	class CollisionManager
	{
		SINGLE(CollisionManager);

	public:
		void Tick();
		void SetLayer(eColliderLayer left, eColliderLayer right, bool value);
		void LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right);
		bool Intersect(Collider* left, Collider* rgiht);

	private:
		WORD mMatrix[COLLIDER_LAYER];
	};
}

