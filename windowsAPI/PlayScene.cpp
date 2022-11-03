#include "PlayScene.h"
#include "Player.h"
#include "BackGround.h"
#include "Wood_Monster_1.h"

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

		Wood_Monster_1* ms1 = new Wood_Monster_1();
		Wood_Monster_1* ms2 = new Wood_Monster_1();

		ms2->SetPos(Vector2(700,500));


		AddGameObject(bg,eColliderLayer::BackGround);
		AddGameObject(new Player(),eColliderLayer::Player);

		AddGameObject(ms1, eColliderLayer::Monster);
		AddGameObject(ms2, eColliderLayer::Monster);

		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster_ProjectTile);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster);
	}

	void PlayScene::Tick()
	{
		// 오브젝트 tick 호출한다
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