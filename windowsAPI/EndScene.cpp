#include "EndScene.h"
#include "Player.h"
#include "BackGround.h"
#include "MeteorControler.h"

namespace sw
{
	EndScene::EndScene()
	{

	}

	EndScene::~EndScene()
	{
		Scene::Release();
	}

	void EndScene::Initialize()
	{

	}

	void EndScene::Tick()
	{
		// ������Ʈ tick ȣ���Ѵ�
		Scene::Tick();
	}

	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"End Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void EndScene::Enter()
	{
	}
	void EndScene::Exit()
	{
	}
}