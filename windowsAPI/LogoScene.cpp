#include "LogoScene.h"
#include "Player.h"
#include "MeteorControler.h"

namespace sw
{
	LogoScene::LogoScene()
	{

	}

	LogoScene::~LogoScene()
	{

	}

	void LogoScene::Initialize()
	{
		AddGameObject(new Player());
	}

	void LogoScene::Tick()
	{
		// 오브젝트 tick 호출한다
		Scene::Tick();

		sw::MeteorControler::GetMeteorControler()->Tick();
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		sw::MeteorControler::GetMeteorControler()->Render(hdc);
	}
}