#include "LogoScene.h"
#include "Player.h"

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

	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}