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
		// ������Ʈ tick ȣ���Ѵ�
		Scene::Tick();

	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}