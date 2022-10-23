#pragma once
#include "GameObject.h"


namespace sw
{
	class Meteor;
	class MeteorControler : public GameObject
	{
	public:
		static MeteorControler* GetMeteorControler() {return &meteorControler;}
		virtual void Tick() override;


	private:
		std::vector<Meteor*> Meteors;
		float mDeltaTime = 0.0f;

		static MeteorControler meteorControler;
	};
}

