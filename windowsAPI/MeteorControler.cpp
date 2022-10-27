#include "MeteorControler.h"
#include <ctime>
#include "Time.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Meteor.h"

namespace sw
{
	MeteorControler MeteorControler::meteorControler;

	void MeteorControler::Tick()
	{
		for (GameObject* obj : Meteors)
		{
			obj->Tick();
		}

		mDeltaTime += Time::DeltaTime();
		if (mDeltaTime > 1.0f)
		{
			Meteor* meteor = new Meteor();
			float x = rand() % 1921;
			meteor->SetPos({x, -1});

			// Event»ý¼º
			EventInfo* info = new EventInfo();
			info->Type = EventType::AddObejct;
			info->Object = meteor;
			EventManager::GetInstance()->EventPush(info);

			Meteors.push_back(meteor);

			mDeltaTime -= 0.5f;
		}
	}
	void MeteorControler::Render(HDC hdc)
	{
		for (GameObject* obj : Meteors)
		{
			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;

			HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
			Brush Curbrush(hdc, brush);

			HPEN pen = CreatePen(PS_SOLID, 2, RGB(b, g, r));
			Pen CurPen(hdc, pen);

			obj->Render(hdc);
		}
	}

	MeteorControler::MeteorControler()
	{
		srand((unsigned int)time(NULL));
	}
	MeteorControler::~MeteorControler()
	{
		
	}
}