#include "MeteorControler.h"
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Meteor.h"

namespace sw
{
	MeteorControler MeteorControler::meteorControler;

	void MeteorControler::Tick()
	{
		mDeltaTime += Time::DeltaTime();
		if (mDeltaTime > 1.0f)
		{
			Meteor* meteor = new Meteor();
			float x = rand() % 1921;
			meteor->SetPos({x, -1});


			Scene* scene = SceneManager::GetPlayScene();
			scene->AddGameObject(meteor);
			Meteors.push_back(meteor);

			mDeltaTime -= 0.5f;
		}
	}
}