#include "PlayScene.h"
#include "Player.h"
#include "BackGround.h"
#include "MeteorControler.h"
#include "Input.h"
#include "SceneManager.h"
#include "CollisionManager.h"

namespace sw
{
	PlayScene::PlayScene()
	{

	}

	PlayScene::~PlayScene()
	{
		Scene::Release();
	}

	void PlayScene::Initialize()
	{
		BackGround* bg = new BackGround();
		bg->SetImage(L"Back", L"BackGround.bmp");
		bg->Initialize();


		AddGameObject(bg,eColliderLayer::BackGround);
		AddGameObject(new Player(),eColliderLayer::Player);

		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster_ProjectTile);
	}

	void PlayScene::Tick()
	{
		// ������Ʈ tick ȣ���Ѵ�
		Scene::Tick();
		sw::MeteorControler::GetMeteorControler()->Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::GetInstance()->ChangeScene(eSceneType::End);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//sw::MeteorControler::GetMeteorControler()->Render(hdc);


		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Paly Scene");
		int strLen = (int)wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
}