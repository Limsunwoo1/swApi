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
		// ������Ʈ tick ȣ���Ѵ�
		Scene::Tick();

		sw::MeteorControler::GetMeteorControler()->Tick();
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		sw::MeteorControler::GetMeteorControler()->Render(hdc);
	}
}